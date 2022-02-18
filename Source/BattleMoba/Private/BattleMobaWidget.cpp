// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaWidget.h"
#include "Engine.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "UObject/ConstructorHelpers.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameState.h"
#include "BattleMobaGameInstance.h"
#include "BattleMobaHUD.h"
#include "BattleMobaPC.h"
#include "TextReaderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Json.h"
#include "JsonUtilities.h"

UBattleMobaWidget::UBattleMobaWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	UTextReaderComponent* TextReader = CreateDefaultSubobject<UTextReaderComponent>(TEXT("TextReaderComp"));

	static ConstructorHelpers::FClassFinder<UUserWidget> GameObj(TEXT("/Game/ThirdPersonCPP/Blueprints/W_DisplayStatistics")); //" / Game / UI / Widgets / UI_Game"
	GameWidgetClass = GameObj.Class;

	ApiUrl = TextReader->ReadFile("Urls/ApiUrl.TXT");

	HttpModule = &FHttpModule::Get();
}

void UBattleMobaWidget::NativeConstruct() {
	Super::NativeConstruct();

	//TimerTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Timer"));
	//TeamNameTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TeamName"));
	//TeammateCountTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TeammateCount")); 
	EventTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Event"));
	EventTextBlock->SetText(FText::FromString(""));
	//GetPlayerKDA();
	//UpdatePlayerKDA();
	//PingTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Ping"));
	//LatestEventTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_LatestEvent"));

	//GetWorld()->GetTimerManager().SetTimer(SetTeammateCountHandle, this, &UBattleMobaWidget::SetTeammateCount, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetLatestEventHandle, this, &UBattleMobaWidget::SetLatestEvent, 1.0f, true, 1.0f);
	//GetWorld()->GetTimerManager().SetTimer(SetAveragePlayerLatencyHandle, this, &UBattleMobaWidget::SetAveragePlayerLatency, 1.0f, true, 1.0f);
	//GetWorld()->GetTimerManager().SetTimer(SetCountdownTimerHandle, this, &UBattleMobaWidget::SetCountdownTimer, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetUpdateKDAHandle, this, &UBattleMobaWidget::UpdatePlayerKDA, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetGetPlayerKDAHandle, this, &UBattleMobaWidget::GetPlayerKDA, 1.0f, true, 1.0f);
}

void UBattleMobaWidget::NativeDestruct() {
	//GetWorld()->GetTimerManager().ClearTimer(SetTeammateCountHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetLatestEventHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetUpdateKDAHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetGetPlayerKDAHandle);
	//GetWorld()->GetTimerManager().ClearTimer(SetAveragePlayerLatencyHandle);
	//GetWorld()->GetTimerManager().ClearTimer(SetCountdownTimerHandle);

	Super::NativeDestruct();
}

//void UBattleMobaWidget::SetTeammateCount() {
//	FString OwningPlayerTeam;
//	APlayerState* OwningPlayerState = GetOwningPlayerState();
//
//	if (OwningPlayerState != nullptr) {
//		ABattleMobaPlayerState* OwningBattleMobaPlayerState = Cast<ABattleMobaPlayerState>(OwningPlayerState);
//		if (OwningBattleMobaPlayerState != nullptr) {
//			OwningPlayerTeam = OwningBattleMobaPlayerState->Team;
//			TeamNameTextBlock->SetText(FText::FromString("Team Name: " + OwningPlayerTeam));
//		}
//	}
//
//	if (OwningPlayerTeam.Len() > 0) {
//		TArray<APlayerState*> PlayerStates = GetWorld()->GetGameState()->PlayerArray;
//
//		int TeammateCount = 0;
//
//		for (APlayerState* PlayerState : PlayerStates) {
//			if (PlayerState != nullptr) {
//				ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(PlayerState);
//				if (BattleMobaPlayerState != nullptr && BattleMobaPlayerState->Team.Equals(OwningPlayerTeam)) {
//					TeammateCount++;
//				}
//			}
//		}
//
//		TeammateCountTextBlock->SetText(FText::FromString("Teammate Count: " + FString::FromInt(TeammateCount)));
//	}
//}

//void UBattleMobaWidget::SetCountdownTimer() {
//
//}

void UBattleMobaWidget::SetLatestEvent() {
	FString LatestEvent;
	FString WinningTeam;
	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (GameState != nullptr) {
		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
		if (BattleMobaGameState != nullptr) {
			LatestEvent = BattleMobaGameState->LatestEvent;
			WinningTeam = BattleMobaGameState->Winner;
		}
	}

	if (LatestEvent.Len() > 0) {
		if (LatestEvent.Equals("GameEnded")) {
			FString OwningPlayerTeam;
			APlayerState* OwningPlayerState = GetOwningPlayerState();

			if (OwningPlayerState != nullptr) {
				ABattleMobaPlayerState* OwningBattleMobaPlayerState = Cast<ABattleMobaPlayerState>(OwningPlayerState);
				if (OwningBattleMobaPlayerState != nullptr) {
					OwningPlayerTeam = OwningBattleMobaPlayerState->Team;
				}
			}

			if (WinningTeam.Len() > 0 && OwningPlayerTeam.Len() > 0) {
				FString GameOverMessage = "You and the " + OwningPlayerTeam;
				if (OwningPlayerTeam.Equals(WinningTeam)) {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " won!"));
				}
				else {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " lost!"));
				}
			}
		}
		else {
			EventTextBlock->SetText(FText::FromString(LatestEvent));
		}
	}
}

void UBattleMobaWidget::GetPlayerKDA() {
	GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
	if (GState) {
		if (GState->DataCheck == true) {
			GetWorld()->GetTimerManager().ClearTimer(SetGetPlayerKDAHandle);
			APlayerState* OwningPlayerState = GetOwningPlayerState();
			if (OwningPlayerState != nullptr) {
				ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(OwningPlayerState);
				TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
				ABattleMobaHUD* BattleMobaHUD = Cast<ABattleMobaHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
				PID = BattleMobaPlayerState->AWSPlayerId; //GState->ArrayPlayerID[BattleMobaPlayerState->Pi];
				RequestObj->SetStringField("PID", PID);//BattleMobaHUD->PlayerId);
				UE_LOG(LogTemp, Warning, TEXT("Get PID: %s"), *PID);//*BattleMobaHUD->PlayerId);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("PID: %s"), *PID));

				FString RequestBody;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
				if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
					TSharedRef<IHttpRequest> GetPlayerKDARequest = HttpModule->CreateRequest();
					GetPlayerKDARequest->OnProcessRequestComplete().BindUObject(this, &UBattleMobaWidget::OnGetPlayerKDAResponseReceived);
					GetPlayerKDARequest->SetURL(ApiUrl + "/getplayerkda");
					GetPlayerKDARequest->SetVerb("POST");
					GetPlayerKDARequest->SetHeader("Content-Type", "application/json");
					//StopMatchmakingRequest->SetHeader("Authorization", AccessToken);
					GetPlayerKDARequest->SetContentAsString(RequestBody);
					GetPlayerKDARequest->ProcessRequest();
				}
			}
		}
	}
}

void UBattleMobaWidget::OnGetPlayerKDAResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
		if (GState) {
			APlayerState* OwningPlayerState = GetOwningPlayerState();
			if (OwningPlayerState != nullptr) {
				ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(OwningPlayerState);
				TSharedPtr<FJsonObject> JsonObject;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
				if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
					if (JsonObject->HasField("playerData")) {
						TSharedPtr<FJsonObject> PlayerData = JsonObject->GetObjectField("playerData");
						TSharedPtr<FJsonObject> UsernameObject = PlayerData->GetObjectField("Username");
						TSharedPtr<FJsonObject> WinsObject = PlayerData->GetObjectField("Wins");
						TSharedPtr<FJsonObject> LossesObject = PlayerData->GetObjectField("Losses");
						TSharedPtr<FJsonObject> KillsObject = PlayerData->GetObjectField("TotalKills");
						TSharedPtr<FJsonObject> DeathsObject = PlayerData->GetObjectField("TotalDeaths");
						TSharedPtr<FJsonObject> AssistsObject = PlayerData->GetObjectField("TotalAssists");

						Username = UsernameObject->GetStringField("S");
						Win = WinsObject->GetStringField("N");
						Lose = LossesObject->GetStringField("N");
						Kill = KillsObject->GetStringField("N");
						Death = DeathsObject->GetStringField("N");
						Assist = AssistsObject->GetStringField("N");

						ABattleMobaPC* BattleMobaPC = Cast<ABattleMobaPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
						BattleMobaPC->NameChangeRequest(BattleMobaPlayerState->Username, BattleMobaPlayerState->Pi);
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Username: %s"), *Username));
						GState->UsernameCheck = true;

						BattleMobaPlayerState->Username = Username;
						GState->CurrentWin = FCString::Atoi(*Win);
						GState->CurrentLose = FCString::Atoi(*Lose);
						GState->CurrentKill = FCString::Atoi(*Kill);
						GState->CurrentDeath = FCString::Atoi(*Death);
						GState->CurrentAssist = FCString::Atoi(*Assist);
						iWin = FCString::Atoi(*Win);
						iLose = FCString::Atoi(*Lose);
						iKill = FCString::Atoi(*Kill);
						iDeath = FCString::Atoi(*Death);
						iAssist = FCString::Atoi(*Assist);

						int GetKill = GState->CurrentKill;
						int GetDeath = GState->CurrentDeath;
						int GetAssist = GState->CurrentAssist;
						UE_LOG(LogTemp, Warning, TEXT("Get Kill: %i"), GetKill);
						UE_LOG(LogTemp, Warning, TEXT("Get Death: %i"), GetDeath);
						UE_LOG(LogTemp, Warning, TEXT("Get Assist: %i"), GetAssist);
					}
				}
			}
		}
	}
}

void UBattleMobaWidget::UpdatePlayerKDA() {
	GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
	if (GState) {
		if (GState->UpdateKDACheck == true) {
			GetWorld()->GetTimerManager().ClearTimer(SetUpdateKDAHandle);
			UE_LOG(LogTemp, Warning, TEXT("KDA update on progress"));
			APlayerState* OwningPlayerState = GetOwningPlayerState();
			if (OwningPlayerState != nullptr) {
				ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(OwningPlayerState);
				ABattleMobaHUD* BattleMobaHUD = Cast<ABattleMobaHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
				//FString PID = BattleMobaHUD->PlayerId;
				FString PlayerTeam = BattleMobaPlayerState->TeamName.ToString();
				int NewKill = BattleMobaPlayerState->Kill;
				int NewDeath = BattleMobaPlayerState->Death;
				int NewAssist = BattleMobaPlayerState->Assist;
				int TotalKill = iKill + NewKill;
				int TotalDeath = iDeath + NewDeath;
				int TotalAssist = iAssist + NewAssist;
				FString SKill = FString::FromInt(TotalKill);
				FString SDeath = FString::FromInt(TotalDeath);
				FString SAssist = FString::FromInt(TotalAssist);
				int NewWin, NewLose;
				
				if (PlayerTeam == GState->Winner) {
					NewWin = iWin + 1;
					FString SWin = FString::FromInt(NewWin);
					FString SLose = FString::FromInt(0);
					TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
					RequestObj->SetStringField("PID", PID);
					RequestObj->SetStringField("Win", SWin);
					RequestObj->SetStringField("Lose", SLose);
					RequestObj->SetStringField("Kill", SKill);
					RequestObj->SetStringField("Death", SDeath);
					RequestObj->SetStringField("Assist", SAssist);

					FString RequestBody;
					TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
					if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
						TSharedRef<IHttpRequest> UpdatePlayerKDARequest = HttpModule->CreateRequest();
						UpdatePlayerKDARequest->OnProcessRequestComplete().BindUObject(this, &UBattleMobaWidget::OnGetUpdateKDAResponseReceived);
						UpdatePlayerKDARequest->SetURL(ApiUrl + "/updatekda");
						UpdatePlayerKDARequest->SetVerb("POST");
						UpdatePlayerKDARequest->SetHeader("Content-Type", "application/json");
						//StopMatchmakingRequest->SetHeader("Authorization", AccessToken);
						UpdatePlayerKDARequest->SetContentAsString(RequestBody);
						UpdatePlayerKDARequest->ProcessRequest();
					}
				}
				else {
					NewLose = iLose + 1;
					FString SWin = FString::FromInt(0);
					FString SLose = FString::FromInt(NewLose);
					TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
					RequestObj->SetStringField("PID", PID);
					RequestObj->SetStringField("Win", SWin);
					RequestObj->SetStringField("Lose", SLose);
					RequestObj->SetStringField("Kill", SKill);
					RequestObj->SetStringField("Death", SDeath);
					RequestObj->SetStringField("Assist", SAssist);

					FString RequestBody;
					TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
					if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
						TSharedRef<IHttpRequest> UpdatePlayerKDARequest = HttpModule->CreateRequest();
						UpdatePlayerKDARequest->OnProcessRequestComplete().BindUObject(this, &UBattleMobaWidget::OnGetUpdateKDAResponseReceived);
						UpdatePlayerKDARequest->SetURL(ApiUrl + "/updatekda");
						UpdatePlayerKDARequest->SetVerb("POST");
						UpdatePlayerKDARequest->SetHeader("Content-Type", "application/json");
						//StopMatchmakingRequest->SetHeader("Authorization", AccessToken);
						UpdatePlayerKDARequest->SetContentAsString(RequestBody);
						UpdatePlayerKDARequest->ProcessRequest();
					}
				}
			}
		}
		/*else {
			UpdatePlayerKDA();
		}*/
	}
	
}

void UBattleMobaWidget::OnGetUpdateKDAResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("KDA updated"));
		if (GameWidgetClass != nullptr) {
			UUserWidget* GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
			if (GameWidget != nullptr) {
				GameWidget->AddToViewport();
			}
		}
	}
}
//void UBattleMobaWidget::SetAveragePlayerLatency() {
//	UGameInstance* GameInstance = GetGameInstance();
//	if (GameInstance != nullptr) {
//		UBattleMobaGameInstance* BattleMobaGameInstance = Cast<UBattleMobaGameInstance>(GameInstance);
//		if (BattleMobaGameInstance != nullptr) {
//			float TotalPlayerLatency = 0.0f;
//			for (float PlayerLatency : BattleMobaGameInstance->PlayerLatencies) {
//				TotalPlayerLatency += PlayerLatency;
//			}
//
//			float AveragePlayerLatency = 60.0f;
//
//			if (TotalPlayerLatency > 0) {
//				AveragePlayerLatency = TotalPlayerLatency / BattleMobaGameInstance->PlayerLatencies.Num();
//
//				FString PingString = "Ping: " + FString::FromInt(FMath::RoundToInt(AveragePlayerLatency)) + "ms";
//				PingTextBlock->SetText(FText::FromString(PingString));
//			}
//		}
//	}
//}
