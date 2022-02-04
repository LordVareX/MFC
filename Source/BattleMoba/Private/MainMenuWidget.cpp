// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "TextReaderComponent.h"
#include "WebBrowser.h"
#include "WebBrowserModule.h"
#include "IWebBrowserSingleton.h"
#include "IWebBrowserCookieManager.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "BattleMobaGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "BattleMobaPlayerState.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	UTextReaderComponent* TextReader = CreateDefaultSubobject<UTextReaderComponent>(TEXT("TextReaderComp"));

	LoginUrl = TextReader->ReadFile("Urls/LoginUrl.TXT");
	ApiUrl = TextReader->ReadFile("Urls/ApiUrl.TXT");
	CallbackUrl = TextReader->ReadFile("Urls/CallbackUrl.TXT");
	RegionCode = TextReader->ReadFile("Urls/RegionCode.TXT");

	HttpModule = &FHttpModule::Get();

	AveragePlayerLatency = 60.0;

	SearchingForGame = false;
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();
	bIsFocusable = true;

	WebBrowser = (UWebBrowser*)GetWidgetFromName(TEXT("WebBrowser_Login"));

	MatchmakingButton = (UButton*)GetWidgetFromName(TEXT("Button_Matchmaking"));
	/*FScriptDelegate MatchmakingDelegate;
	MatchmakingDelegate.BindUFunction(this, "OnMatchmakingButtonClicked");
	MatchmakingButton->OnClicked.Add(MatchmakingDelegate);*/

	WinsTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Wins"));

	LossesTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Losses"));

	PingTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Ping"));

	//MatchmakingEventTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_MatchmakingEvent"));

	UsernameTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Username"));

	ErrorTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Error"));

	KillTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Kill"));

	DeathTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Death"));

	AssistTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Assist"));

	//PNTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_PN"));

	NameCanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel_Name"));

	NameEditableTextBox = (UEditableTextBox*)GetWidgetFromName(TEXT("EditableTextBox_Name"));

	CreateNameButton = (UButton*)GetWidgetFromName(TEXT("Button_CreateName"));
	FScriptDelegate CreateNameDelegate;
	CreateNameDelegate.BindUFunction(this, "OnCreateNameButtonClicked");
	CreateNameButton->OnClicked.Add(CreateNameDelegate);

	GetWorld()->GetTimerManager().SetTimer(SetAveragePlayerLatencyHandle, this, &UMainMenuWidget::SetAveragePlayerLatency, 1.0f, true, 1.0f);

	FString AccessToken;
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			AccessToken = BattleMobaGameInstance->AccessToken;
		}
	}

	if (AccessToken.Len() > 0) {
		TSharedRef<IHttpRequest> GetPlayerDataRequest = HttpModule->CreateRequest();
		GetPlayerDataRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnGetPlayerDataResponseReceived);
		GetPlayerDataRequest->SetURL(ApiUrl + "/getplayerdata");
		GetPlayerDataRequest->SetVerb("GET");
		//GetPlayerDataRequest->SetHeader("Content-Type", "application/json");
		GetPlayerDataRequest->SetHeader("Authorization", AccessToken);
		GetPlayerDataRequest->ProcessRequest();
	}
	else {
		IWebBrowserSingleton* WebBrowserSingleton = IWebBrowserModule::Get().GetSingleton();

		if (WebBrowserSingleton != nullptr) {
			TOptional<FString> DefaultContext;
			TSharedPtr<IWebBrowserCookieManager> CookieManager = WebBrowserSingleton->GetCookieManager(DefaultContext);
			if (CookieManager.IsValid()) {
				CookieManager->DeleteCookies();
			}
		}

		WebBrowser->LoadURL(LoginUrl);

		FScriptDelegate LoginDelegate;
		LoginDelegate.BindUFunction(this, "HandleLoginUrlChange");
		WebBrowser->OnUrlChanged.Add(LoginDelegate);
	}
}

void UMainMenuWidget::NativeDestruct() {
	GetWorld()->GetTimerManager().ClearTimer(PollMatchmakingHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetAveragePlayerLatencyHandle);
	Super::NativeDestruct();
}

void UMainMenuWidget::HandleLoginUrlChange() {
	FString BrowseUrl = WebBrowser->GetUrl();
	FString Url;
	FString QueryParameters;

	if (BrowseUrl.Split("?", &Url, &QueryParameters)) {
		if (Url.Equals(CallbackUrl)) {
			FString ParameterName;
			FString ParameterValue;

			if (QueryParameters.Split("=", &ParameterName, &ParameterValue)) {
				if (ParameterName.Equals("code")) {
					ParameterValue = ParameterValue.Replace(*FString("#"), *FString(""));

					TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
					RequestObj->SetStringField(ParameterName, ParameterValue);

					FString RequestBody;
					TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);

					if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
						TSharedRef<IHttpRequest> ExchangeCodeForTokensRequest = HttpModule->CreateRequest();
						ExchangeCodeForTokensRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnExchangeCodeForTokensResponseReceived);
						ExchangeCodeForTokensRequest->SetURL(ApiUrl + "/exchangecodefortokens");
						ExchangeCodeForTokensRequest->SetVerb("POST");
						ExchangeCodeForTokensRequest->SetHeader("Content-Type", "application/json");
						ExchangeCodeForTokensRequest->SetContentAsString(RequestBody);
						ExchangeCodeForTokensRequest->ProcessRequest();
					}
				}
			}
		}
	}
}

void UMainMenuWidget::OnExchangeCodeForTokensResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			if (JsonObject->HasField("access_token") && JsonObject->HasField("id_token") && JsonObject->HasField("refresh_token")) {
				UGameInstance* GameInstance = GetGameInstance();
				if (GameInstance != nullptr) {
					UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
					if (BattleMobaGameInstance != nullptr) {
						FString AccessToken = JsonObject->GetStringField("access_token");
						FString IdToken = JsonObject->GetStringField("id_token");
						FString RefreshToken = JsonObject->GetStringField("refresh_token");
						BattleMobaGameInstance->SetCognitoTokens(AccessToken, IdToken, RefreshToken);
						
						TSharedRef<IHttpRequest> GetPlayerDataRequest = HttpModule->CreateRequest();
						GetPlayerDataRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnGetPlayerDataResponseReceived);
						GetPlayerDataRequest->SetURL(ApiUrl + "/getplayerdata");
						GetPlayerDataRequest->SetVerb("GET");
						//GetPlayerDataRequest->SetHeader("Content-Type", "application/json");
						GetPlayerDataRequest->SetHeader("Authorization", AccessToken);
						GetPlayerDataRequest->ProcessRequest();
					}
				}
			}
		}
	}
}

void UMainMenuWidget::OnGetPlayerDataResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			if (JsonObject->HasField("playerData")) {
				TSharedPtr<FJsonObject> PlayerData = JsonObject->GetObjectField("playerData");
				TSharedPtr<FJsonObject> IdObject = PlayerData->GetObjectField("Id");
				TSharedPtr<FJsonObject> WinsObject = PlayerData->GetObjectField("Wins");
				TSharedPtr<FJsonObject> LossesObject = PlayerData->GetObjectField("Losses");
				TSharedPtr<FJsonObject> UsernameObject = PlayerData->GetObjectField("Username");
				TSharedPtr<FJsonObject> KillsObject = PlayerData->GetObjectField("TotalKills");
				TSharedPtr<FJsonObject> DeathsObject = PlayerData->GetObjectField("TotalDeaths");
				TSharedPtr<FJsonObject> AssistsObject = PlayerData->GetObjectField("TotalAssists");

				Id = IdObject->GetStringField("S");
				Wins = WinsObject->GetStringField("N");
				Losses = LossesObject->GetStringField("N");
				Username = UsernameObject->GetStringField("S");
				Kill = KillsObject->GetStringField("N");
				Death = DeathsObject->GetStringField("N");
				Assist = AssistsObject->GetStringField("N");


				IdRef = Id;
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("ID : %s"), *IdRef));

				if (Username == "null") {
					WebBrowser->SetVisibility(ESlateVisibility::Hidden);
					NameCanvasPanel->SetVisibility(ESlateVisibility::Visible);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Username : %s"), *Username));
				}
				else {
					UsernameCheck = true;
					WinsTextBlock->SetText(FText::FromString("Wins: " + Wins));
					LossesTextBlock->SetText(FText::FromString("Losses: " + Losses));
					KillTextBlock->SetText(FText::FromString("Total Kill: " + Kill));
					DeathTextBlock->SetText(FText::FromString("Total Death: " + Death));
					AssistTextBlock->SetText(FText::FromString("Total Assist: " + Assist));
					UsernameTextBlock->SetText(FText::FromString(Username));
					UsernameRef = Username;

					/*APlayerState* OwningPlayerState = GetOwningPlayerState();
					if (OwningPlayerState != nullptr) {
						PNTextBlock->SetText(FText::FromString(OwningPlayerState->GetPlayerName()));
					}*/

					WebBrowser->SetVisibility(ESlateVisibility::Hidden);
					MatchmakingButton->SetVisibility(ESlateVisibility::Visible);
					WinsTextBlock->SetVisibility(ESlateVisibility::Visible);
					LossesTextBlock->SetVisibility(ESlateVisibility::Visible);
					PingTextBlock->SetVisibility(ESlateVisibility::Visible);
					KillTextBlock->SetVisibility(ESlateVisibility::Visible);
					DeathTextBlock->SetVisibility(ESlateVisibility::Visible);
					AssistTextBlock->SetVisibility(ESlateVisibility::Visible);
					//MatchmakingEventTextBlock->SetVisibility(ESlateVisibility::Visible);
					UsernameTextBlock->SetVisibility(ESlateVisibility::Visible);

					UGameInstance* GameInstance = GetGameInstance();
					if (GameInstance != nullptr) {
						UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
						if (BattleMobaGameInstance != nullptr) {
							BattleMobaGameInstance->PlayerId = Id;
							BattleMobaGameInstance->Username = Username;
						}
					}
					//PNTextBlock->SetVisibility(ESlateVisibility::Visible);

					
				}
			}
		}
	}
}

void UMainMenuWidget::SetAveragePlayerLatency() {
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			float TotalPlayerLatency = 0.0f;
			for (float PlayerLatency : BattleMobaGameInstance->PlayerLatencies) {
				TotalPlayerLatency += PlayerLatency;
			}

			if (TotalPlayerLatency > 0) {
				AveragePlayerLatency = TotalPlayerLatency / BattleMobaGameInstance->PlayerLatencies.Num();

				FString PingString = "Ping: " + FString::FromInt(FMath::RoundToInt(AveragePlayerLatency)) + "ms";
				PingTextBlock->SetText(FText::FromString(PingString));
			}
		}
	}
}

void UMainMenuWidget::OnMatchmakingButtonClicked() {
	//MatchmakingButton->SetIsEnabled(false);

	FString AccessToken;
	FString MatchmakingTicketId;
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			AccessToken = BattleMobaGameInstance->AccessToken;
			MatchmakingTicketId = BattleMobaGameInstance->MatchmakingTicketId;
		}
	}

	if (SearchingForGame) {
		GetWorld()->GetTimerManager().ClearTimer(PollMatchmakingHandle);
		SearchingForGame = false;

		if (AccessToken.Len() > 0 && MatchmakingTicketId.Len() > 0) {
			TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
			RequestObj->SetStringField("ticketId", MatchmakingTicketId);

			FString RequestBody;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
			if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
				TSharedRef<IHttpRequest> StopMatchmakingRequest = HttpModule->CreateRequest();
				StopMatchmakingRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnStopMatchmakingResponseReceived);
				StopMatchmakingRequest->SetURL(ApiUrl + "/stopmatchmaking");
				StopMatchmakingRequest->SetVerb("POST");
				StopMatchmakingRequest->SetHeader("Content-Type", "application/json");
				StopMatchmakingRequest->SetHeader("Authorization", AccessToken);
				StopMatchmakingRequest->SetContentAsString(RequestBody);
				StopMatchmakingRequest->ProcessRequest();
			}
			else {
				//UTextBlock* ButtonTextBlock = (UTextBlock*)MatchmakingButton->GetChildAt(0);
				//ButtonTextBlock->SetText(FText::FromString("Join Game"));
				//MatchmakingEventTextBlock->SetText(FText::FromString(""));

				//MatchmakingButton->SetIsEnabled(true);
			}
		}
		else {
			//UTextBlock* ButtonTextBlock = (UTextBlock*)MatchmakingButton->GetChildAt(0);
			//ButtonTextBlock->SetText(FText::FromString("Join Game"));
			//MatchmakingEventTextBlock->SetText(FText::FromString(""));

			//MatchmakingButton->SetIsEnabled(true);
		}
	}
	else {
		if (AccessToken.Len() > 0) {
			TSharedRef<FJsonObject> LatencyMapObj = MakeShareable(new FJsonObject);
			LatencyMapObj->SetNumberField(RegionCode, AveragePlayerLatency);

			TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
			RequestObj->SetObjectField("latencyMap", LatencyMapObj);

			FString RequestBody;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
			if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
				TSharedRef<IHttpRequest> StartMatchmakingRequest = HttpModule->CreateRequest();
				StartMatchmakingRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnStartMatchmakingResponseReceived);
				StartMatchmakingRequest->SetURL(ApiUrl + "/startmatchmaking");
				StartMatchmakingRequest->SetVerb("POST");
				StartMatchmakingRequest->SetHeader("Content-Type", "application/json");
				StartMatchmakingRequest->SetHeader("Authorization", AccessToken);
				StartMatchmakingRequest->SetContentAsString(RequestBody);
				StartMatchmakingRequest->ProcessRequest();
			}
			else {
				//MatchmakingButton->SetIsEnabled(true);
			}
		}
		else {
			//MatchmakingButton->SetIsEnabled(true);
		}
	}
}

void UMainMenuWidget::OnStartMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			if (JsonObject->HasField("ticketId")) {
				FString MatchmakingTicketId = JsonObject->GetStringField("ticketId");

				UGameInstance* GameInstance = GetGameInstance();
				if (GameInstance != nullptr) {
					UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
					if (BattleMobaGameInstance != nullptr) {
						BattleMobaGameInstance->MatchmakingTicketId = MatchmakingTicketId;

						GetWorld()->GetTimerManager().SetTimer(PollMatchmakingHandle, this, &UMainMenuWidget::PollMatchmaking, 1.0f, true, 1.0f);
						SearchingForGame = true;

						/*UTextBlock* ButtonTextBlock = (UTextBlock*)MatchmakingButton->GetChildAt(0);
						ButtonTextBlock->SetText(FText::FromString("Cancel Matchmaking"));
						//MatchmakingEventTextBlock->SetText(FText::FromString("Currently looking for a match"));*/
					}
				}
			}
		}
	}
	//MatchmakingButton->SetIsEnabled(true);
}

void UMainMenuWidget::OnStopMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			BattleMobaGameInstance->MatchmakingTicketId = "";
		}
	}

	//UTextBlock* ButtonTextBlock = (UTextBlock*)MatchmakingButton->GetChildAt(0);
	//ButtonTextBlock->SetText(FText::FromString("Join Game"));
	//MatchmakingEventTextBlock->SetText(FText::FromString(""));

	//MatchmakingButton->SetIsEnabled(true);
}

void UMainMenuWidget::PollMatchmaking() {
	FString AccessToken;
	FString MatchmakingTicketId;

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			AccessToken = BattleMobaGameInstance->AccessToken;
			MatchmakingTicketId = BattleMobaGameInstance->MatchmakingTicketId;
		}
	}

	if (AccessToken.Len() > 0 && MatchmakingTicketId.Len() > 0 && SearchingForGame) {
		TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
		RequestObj->SetStringField("ticketId", MatchmakingTicketId);

		FString RequestBody;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
		if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
			TSharedRef<IHttpRequest> PollMatchmakingRequest = HttpModule->CreateRequest();
			PollMatchmakingRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnPollMatchmakingResponseReceived);
			PollMatchmakingRequest->SetURL(ApiUrl + "/pollmatchmaking");
			PollMatchmakingRequest->SetVerb("POST");
			PollMatchmakingRequest->SetHeader("Content-Type", "application/json");
			PollMatchmakingRequest->SetHeader("Authorization", AccessToken);
			PollMatchmakingRequest->SetContentAsString(RequestBody);
			PollMatchmakingRequest->ProcessRequest();
		}
	}
}

void UMainMenuWidget::OnPollMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful && SearchingForGame) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			if (JsonObject->HasField("ticket")) {
				TSharedPtr<FJsonObject> Ticket = JsonObject->GetObjectField("ticket");
				FString TicketType = Ticket->GetObjectField("Type")->GetStringField("S");

				if (TicketType.Len() > 0) {
					GetWorld()->GetTimerManager().ClearTimer(PollMatchmakingHandle);
					SearchingForGame = false;

					UGameInstance* GameInstance = GetGameInstance();
					if (GameInstance != nullptr) {
						UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
						if (BattleMobaGameInstance != nullptr) {
							BattleMobaGameInstance->MatchmakingTicketId = "";
						}
					}

					if (TicketType.Equals("MatchmakingSucceeded")) {
						//MatchmakingButton->SetIsEnabled(false);
						//MatchmakingEventTextBlock->SetText(FText::FromString("Successfully found a match. Now connecting to the server..."));

						TSharedPtr<FJsonObject> GameSessionInfo = Ticket->GetObjectField("GameSessionInfo")->GetObjectField("M");
						FString IpAddress = GameSessionInfo->GetObjectField("IpAddress")->GetStringField("S");
						FString Port = GameSessionInfo->GetObjectField("Port")->GetStringField("N");

						TArray<TSharedPtr<FJsonValue>> Players = Ticket->GetObjectField("Players")->GetArrayField("L");
						TSharedPtr<FJsonObject> Player = Players[0]->AsObject()->GetObjectField("M");
						FString PlayerSessionId = Player->GetObjectField("PlayerSessionId")->GetStringField("S");
						FString PlayerId = Player->GetObjectField("PlayerId")->GetStringField("S");

						FString LevelName = IpAddress + ":" + Port;
						const FString& Options = "?PlayerSessionId=" + PlayerSessionId + "?PlayerId=" + PlayerId + "?Name=Todak" + UsernameRef;
						//UE_LOG(LogTemp, Warning, TEXT("options: %s"), *Options);

						UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), false, Options);
					}
					else {
						//UTextBlock* ButtonTextBlock = (UTextBlock*)MatchmakingButton->GetChildAt(0);
						//ButtonTextBlock->SetText(FText::FromString("Join Game"));
						//MatchmakingEventTextBlock->SetText(FText::FromString(TicketType + ". Please try again"));
					}
				}
			}
		}
	}
}

void UMainMenuWidget::OnCreateNameButtonClicked() {

	FText Name = NameEditableTextBox->GetText();
	UsernameRef = Name.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Name : %s"), *UsernameRef));

	TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
	RequestObj->SetStringField("IdRef", IdRef);
	RequestObj->SetStringField("UsernameRef", UsernameRef);

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
		if (BattleMobaGameInstance != nullptr) {
			BattleMobaGameInstance->PlayerId = IdRef;
			BattleMobaGameInstance->Username = UsernameRef;
		}
	}

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
		TSharedRef<IHttpRequest> StopMatchmakingRequest = HttpModule->CreateRequest();
		StopMatchmakingRequest->OnProcessRequestComplete().BindUObject(this, &UMainMenuWidget::OnCreateNameButtonClickedResponseReceived);
		StopMatchmakingRequest->SetURL(ApiUrl + "/updateingamename");
		StopMatchmakingRequest->SetVerb("POST");
		StopMatchmakingRequest->SetHeader("Content-Type", "application/json");
		StopMatchmakingRequest->SetContentAsString(RequestBody);
		StopMatchmakingRequest->ProcessRequest();
	}
}

void UMainMenuWidget::OnCreateNameButtonClickedResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			if (JsonObject->HasField("Error")) {
				FString Error = JsonObject->GetStringField("Error");
				if (Error == "Username taken!") {
					ErrorTextBlock->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else if (JsonObject->HasField("Success")) {
				FString Success = JsonObject->GetStringField("Success");
				if (Success == "Available") {
					NameCanvasPanel->SetVisibility(ESlateVisibility::Hidden);

					UsernameCheck = true;
					WinsTextBlock->SetText(FText::FromString("Wins: " + Wins));
					LossesTextBlock->SetText(FText::FromString("Losses: " + Losses));
					KillTextBlock->SetText(FText::FromString("Total Kill: " + Kill));
					DeathTextBlock->SetText(FText::FromString("Total Death: " + Death));
					AssistTextBlock->SetText(FText::FromString("Total Assist: " + Assist));
					UsernameTextBlock->SetText(FText::FromString(UsernameRef));
					//UsernameRef = Username;
					/*APlayerState* OwningPlayerState = GetOwningPlayerState();
					if (OwningPlayerState != nullptr) {
						PNTextBlock->SetText(FText::FromString(OwningPlayerState->GetPlayerName()));
					}*/

					WebBrowser->SetVisibility(ESlateVisibility::Hidden);
					MatchmakingButton->SetVisibility(ESlateVisibility::Visible);
					WinsTextBlock->SetVisibility(ESlateVisibility::Visible);
					LossesTextBlock->SetVisibility(ESlateVisibility::Visible);
					PingTextBlock->SetVisibility(ESlateVisibility::Visible);
					KillTextBlock->SetVisibility(ESlateVisibility::Visible);
					DeathTextBlock->SetVisibility(ESlateVisibility::Visible);
					AssistTextBlock->SetVisibility(ESlateVisibility::Visible);
					//MatchmakingEventTextBlock->SetVisibility(ESlateVisibility::Visible);
					UsernameTextBlock->SetVisibility(ESlateVisibility::Visible);

					/*UGameInstance* GameInstance = GetGameInstance();
					if (GameInstance != nullptr) {
						UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
						if (BattleMobaGameInstance != nullptr) {
							BattleMobaGameInstance->PlayerId = Id;
							BattleMobaGameInstance->Username = Username;
						}
					}*/
					//PNTextBlock->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}