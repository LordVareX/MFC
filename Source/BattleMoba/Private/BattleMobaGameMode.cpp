// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BattleMobaGameMode.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerStart.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "TextReaderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "GameLiftServerSDK.h"

//BattleMoba
#include "BattleMobaCharacter.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameState.h"
#include "BattleMobaHUD.h"
#include "BattleMobaPC.h"
#include "InputLibrary.h"
#include "BattleMobaGameInstance.h"


void ABattleMobaGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaGameMode, Players);
	//DOREPLIFETIME(ABattleMobaGameMode, CharIndex);
}

ABattleMobaGameMode::ABattleMobaGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
	//	SpawnedActor = PlayerPawnBPClass.Class;
	//	DefaultPawnClass = nullptr;
		//HUDClass = ABattleMobaHUD::StaticClass();
		//PlayerStateClass = ABattleMobaPlayerState::StaticClass();
		//GameStateClass = ABattleMobaGameState::StaticClass();
		//PlayerControllerClass = ABattleMobaPC::StaticClass();
	//}



	UTextReaderComponent* TextReader = CreateDefaultSubobject<UTextReaderComponent>(TEXT("TextReaderComp"));
	ApiUrl = TextReader->ReadFile("Urls/ApiUrl.txt");

	HttpModule = &FHttpModule::Get();

	RemainingGameTime = 900.0f;
	LobbyTimer = 30.0f;
	GameSessionActivated = false;

	WaitingForPlayersToJoin = false;
	TimeSpentWaitingForPlayersToJoin = 0;


}

void ABattleMobaGameMode::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(LobbyClockTimer, this, &ABattleMobaGameMode::StartLobbyClock, 1.0f, true);
}
//Chars = CharSelections;

//#if WITH_GAMELIFT
//	auto InitSDKOutcome = Aws::GameLift::Server::InitSDK();
//
//	if (InitSDKOutcome.IsSuccess()) {
//		auto OnStartGameSession = [](Aws::GameLift::Server::Model::GameSession GameSessionObj, void* Params)
//		{
//			FStartGameSessionState* State = (FStartGameSessionState*)Params;
//
//			State->Status = Aws::GameLift::Server::ActivateGameSession().IsSuccess();
//
//			FString MatchmakerData = GameSessionObj.GetMatchmakerData();
//
//			TSharedPtr<FJsonObject> JsonObject;
//			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MatchmakerData);
//
//			if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
//				State->MatchmakingConfigurationArn = JsonObject->GetStringField("matchmakingConfigurationArn");
//
//				TArray<TSharedPtr<FJsonValue>> Teams = JsonObject->GetArrayField("teams");
//				for (TSharedPtr<FJsonValue> Team : Teams) {
//					TSharedPtr<FJsonObject> TeamObj = Team->AsObject();
//					FString TeamName = TeamObj->GetStringField("name");
//
//					TArray<TSharedPtr<FJsonValue>> Players = TeamObj->GetArrayField("players");
//
//					for (TSharedPtr<FJsonValue> Player : Players) {
//						TSharedPtr<FJsonObject> PlayerObj = Player->AsObject();
//						FString PlayerId = PlayerObj->GetStringField("playerId");
//
//						TSharedPtr<FJsonObject> Attributes = PlayerObj->GetObjectField("attributes");
//						TSharedPtr<FJsonObject> Skill = Attributes->GetObjectField("skill");
//						FString SkillValue = Skill->GetStringField("valueAttribute");
//						auto SkillAttributeValue = new Aws::GameLift::Server::Model::AttributeValue(FCString::Atod(*SkillValue));
//
//						Aws::GameLift::Server::Model::Player AwsPlayerObj;
//
//						AwsPlayerObj.SetPlayerId(TCHAR_TO_ANSI(*PlayerId));
//						AwsPlayerObj.SetTeam(TCHAR_TO_ANSI(*TeamName));
//						AwsPlayerObj.AddPlayerAttribute("skill", *SkillAttributeValue);
//
//						State->PlayerIdToPlayer.Add(PlayerId, AwsPlayerObj);
//					}
//				}
//			}
//		};
//
//		auto OnUpdateGameSession = [](Aws::GameLift::Server::Model::UpdateGameSession UpdateGameSessionObj, void* Params)
//		{
//			FUpdateGameSessionState* State = (FUpdateGameSessionState*)Params;
//
//			auto Reason = UpdateGameSessionObj.GetUpdateReason();
//
//			if (Reason == Aws::GameLift::Server::Model::UpdateReason::MATCHMAKING_DATA_UPDATED) {
//				State->Reason = EUpdateReason::MATCHMAKING_DATA_UPDATED;
//
//				auto GameSessionObj = UpdateGameSessionObj.GetGameSession();
//				FString MatchmakerData = GameSessionObj.GetMatchmakerData();
//
//				TSharedPtr<FJsonObject> JsonObject;
//				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MatchmakerData);
//
//				if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
//					TArray<TSharedPtr<FJsonValue>> Teams = JsonObject->GetArrayField("teams");
//					for (TSharedPtr<FJsonValue> Team : Teams) {
//						TSharedPtr<FJsonObject> TeamObj = Team->AsObject();
//						FString TeamName = TeamObj->GetStringField("name");
//
//						TArray<TSharedPtr<FJsonValue>> Players = TeamObj->GetArrayField("players");
//
//						for (TSharedPtr<FJsonValue> Player : Players) {
//							TSharedPtr<FJsonObject> PlayerObj = Player->AsObject();
//							FString PlayerId = PlayerObj->GetStringField("playerId");
//
//							TSharedPtr<FJsonObject> Attributes = PlayerObj->GetObjectField("attributes");
//							TSharedPtr<FJsonObject> Skill = Attributes->GetObjectField("skill");
//							FString SkillValue = Skill->GetStringField("valueAttribute");
//							auto SkillAttributeValue = new Aws::GameLift::Server::Model::AttributeValue(FCString::Atod(*SkillValue));
//
//							Aws::GameLift::Server::Model::Player AwsPlayerObj;
//
//							AwsPlayerObj.SetPlayerId(TCHAR_TO_ANSI(*PlayerId));
//							AwsPlayerObj.SetTeam(TCHAR_TO_ANSI(*TeamName));
//							AwsPlayerObj.AddPlayerAttribute("skill", *SkillAttributeValue);
//
//							State->PlayerIdToPlayer.Add(PlayerId, AwsPlayerObj);
//						}
//					}
//				}
//			}
//			else if (Reason == Aws::GameLift::Server::Model::UpdateReason::BACKFILL_CANCELLED) {
//				State->Reason = EUpdateReason::BACKFILL_CANCELLED;
//			}
//			else if (Reason == Aws::GameLift::Server::Model::UpdateReason::BACKFILL_FAILED) {
//				State->Reason = EUpdateReason::BACKFILL_FAILED;
//			}
//			else if (Reason == Aws::GameLift::Server::Model::UpdateReason::BACKFILL_TIMED_OUT) {
//				State->Reason = EUpdateReason::BACKFILL_TIMED_OUT;
//			}
//		};
//
//		auto OnProcessTerminate = [](void* Params)
//		{
//			FProcessTerminateState* State = (FProcessTerminateState*)Params;
//
//			auto GetTerminationTimeOutcome = Aws::GameLift::Server::GetTerminationTime();
//			if (GetTerminationTimeOutcome.IsSuccess()) {
//				State->TerminationTime = GetTerminationTimeOutcome.GetResult();
//			}
//
//			State->Status = true;
//		};
//
//		auto OnHealthCheck = [](void* Params)
//		{
//			FHealthCheckState* State = (FHealthCheckState*)Params;
//			State->Status = true;
//
//			return State->Status;
//		};
//
//		TArray<FString> CommandLineTokens;
//		TArray<FString> CommandLineSwitches;
//		int Port = FURL::UrlConfig.DefaultPort;
//
//		// BattleMobaServer.exe token -port=7777
//		FCommandLine::Parse(FCommandLine::Get(), CommandLineTokens, CommandLineSwitches);
//
//		for (FString Str : CommandLineSwitches) {
//			FString Key;
//			FString Value;
//
//			if (Str.Split("=", &Key, &Value)) {
//				if (Key.Equals("port")) {
//					Port = FCString::Atoi(*Value);
//				}
//				else if (Key.Equals("password")) {
//					ServerPassword = Value;
//				}
//			}
//		}
//
//		const char* LogFile = "aLogFile.txt";
//		const char** LogFiles = &LogFile;
//		auto LogParams = new Aws::GameLift::Server::LogParameters(LogFiles, 1);
//
//		auto Params = new Aws::GameLift::Server::ProcessParameters(
//			OnStartGameSession,
//			&StartGameSessionState,
//			OnUpdateGameSession,
//			&UpdateGameSessionState,
//			OnProcessTerminate,
//			&ProcessTerminateState,
//			OnHealthCheck,
//			&HealthCheckState,
//			Port,
//			*LogParams
//		);
//
//		auto ProcessReadyOutcome = Aws::GameLift::Server::ProcessReady(*Params);
//	}
//#endif
//	GetWorldTimerManager().SetTimer(HandleGameSessionUpdateHandle, this, &ABattleMobaGameMode::HandleGameSessionUpdate, 1.0f, true, 5.0f);
//	GetWorldTimerManager().SetTimer(HandleProcessTerminationHandle, this, &ABattleMobaGameMode::HandleProcessTermination, 1.0f, true, 5.0f);
//	/*if (GameState != nullptr) {
//		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
//		if (BattleMobaGameState != nullptr) {
//			BattleMobaGameState->LatestEvent = "GameEnded";
//			BattleMobaGameState->Winner = "Radiant";
//		}
//	}*/
//
//
//	//sETTING UP GAME STATE
//	GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
//
//	//if (HasAuthority() && (UGameplayStatics::GetCurrentLevelName(this) == MapName))
//	//{
//	//	FTimerHandle handle;
//	//	FTimerDelegate TimerDelegate;
//
//	//	//Possess a pawn
//	//	TimerDelegate.BindLambda([this]()
//	//	{
//	//		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FString::Printf(TEXT("Start Timer")));
//
//
//	////		//Get Initial time
//	////		InitialTimer = UInputLibrary::GetCurrentTimeInMinute()*60.0f;
//	////		//	//Start game time
//	////		//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Start Timer")));
//	////		//	GetWorldTimerManager().SetTimer(CountDownUntilGameOverHandle, this, &ABattleMobaGameMode::CountDownUntilGameOver, 1.0f, true);
//				//GetWorldTimerManager().SetTimer(LobbyClockTimer, this, &ABattleMobaGameMode::StartLobbyClock, 1.0f, true);
//	//	});
//	//	this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 1.0f, false);
//	//}
//}
//
//void ABattleMobaGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) {
//	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
//#if WITH_GAMELIFT
//	if (Options.Len() > 0) {
//		const FString& PlayerSessionId = UGameplayStatics::ParseOption(Options, "PlayerSessionId");
//		const FString& PlayerId = UGameplayStatics::ParseOption(Options, "PlayerId");
//
//		if (PlayerSessionId.Len() > 0 && PlayerId.Len() > 0) {
//			Aws::GameLift::Server::Model::DescribePlayerSessionsRequest DescribePlayerSessionsRequest;
//			DescribePlayerSessionsRequest.SetPlayerSessionId(TCHAR_TO_ANSI(*PlayerSessionId));
//
//			auto DescribePlayerSessionsOutcome = Aws::GameLift::Server::DescribePlayerSessions(DescribePlayerSessionsRequest);
//			if (DescribePlayerSessionsOutcome.IsSuccess()) {
//				auto DescribePlayerSessionsResult = DescribePlayerSessionsOutcome.GetResult();
//				int Count = 1;
//				auto PlayerSessions = DescribePlayerSessionsResult.GetPlayerSessions(Count);
//				if (PlayerSessions != nullptr) {
//					auto PlayerSession = PlayerSessions[0];
//					FString ExpectedPlayerId = PlayerSession.GetPlayerId();
//					auto PlayerStatus = PlayerSession.GetStatus();
//
//					if (ExpectedPlayerId.Equals(PlayerId) && PlayerStatus == Aws::GameLift::Server::Model::PlayerSessionStatus::RESERVED) {
//						auto AcceptPlayerSessionOutcome = Aws::GameLift::Server::AcceptPlayerSession(TCHAR_TO_ANSI(*PlayerSessionId));
//
//						if (!AcceptPlayerSessionOutcome.IsSuccess()) {
//							ErrorMessage = "Unauthorized";
//						}
//					}
//					else {
//						ErrorMessage = "Unauthorized";
//					}
//				}
//				else {
//					ErrorMessage = "Unauthorized";
//				}
//			}
//			else {
//				ErrorMessage = "Unauthorized";
//			}
//		}
//		else {
//			ErrorMessage = "Unauthorized";
//		}
//	}
//	else {
//		ErrorMessage = "Unauthorized";
//	}
//#endif
//}

void ABattleMobaGameMode::StartLobbyClock() {
	if (GState != nullptr) {
		if (LobbyTimer > 0.0f) {
			LobbyTimer--;
			GState->LobbyTimer = LobbyTimer;
		}
		else {
			GState->LobbyCheck = true;
			GetWorldTimerManager().ClearTimer(LobbyClockTimer);
			UpdateLobby();
			GetWorldTimerManager().SetTimer(ClockTimer, this, &ABattleMobaGameMode::StartClock, 1.0f, true);
		}
	}
}

void ABattleMobaGameMode::StartClock()
{
	if (GState != nullptr)
	{
		/*if (RemainingGameTime < 890.0f) {
			GState->LobbyCheck = true;
		}*/
		//if (CurrentTime < EndTime)
		//{
		//	//Get current timer value
		//	CurrentTime = (UInputLibrary::GetCurrentTimeInMinute()*60.0f) - InitialTimer;
		//	//GState->LatestEvent = FString::FromInt(CurrentTime) + " seconds until the game is over";
		//	GState->CurrentTime = CurrentTime;
		//}

		if (RemainingGameTime > 0.0f) {
			RemainingGameTime--;
			GState->RemainingGameTime = RemainingGameTime;
		}
		else
		{
			GState->LatestEvent = "GameEnded";
			//Stops the timer and check for winners
			GetWorldTimerManager().ClearTimer(ClockTimer);
			if (GState->TeamKillA > GState->TeamKillB)
			{
				GState->Winner = "Radiant";
			}
			else if (GState->TeamKillB > GState->TeamKillA)
			{
				GState->Winner = "Dire";
			}
#if WITH_GAMELIFT
			if (GameState != nullptr) {
				ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
				if (BattleMobaGameState != nullptr) {
					BattleMobaGameState->LatestEvent = "GameEnded";
					//Stops the timer and check for winners
					GetWorldTimerManager().ClearTimer(ClockTimer);
					if (GState->TeamKillA > GState->TeamKillB)
					{
						GState->Winner = "Radiant";
					}
					else if (GState->TeamKillB > GState->TeamKillA)
					{
						GState->Winner = "Dire";
					}
					TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
					RequestObj->SetStringField("winningTeam", BattleMobaGameState->Winner);


					auto GetGameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
					if (GetGameSessionIdOutcome.IsSuccess()) {
						RequestObj->SetStringField("gameSessionId", GetGameSessionIdOutcome.GetResult());
						BattleMobaGameState->GameSessionID = GetGameSessionIdOutcome.GetResult();

						FString RequestBody;
						TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
						if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
							TSharedRef<IHttpRequest> RecordMatchResultRequest = HttpModule->CreateRequest();
							RecordMatchResultRequest->OnProcessRequestComplete().BindUObject(this, &ABattleMobaGameMode::OnRecordMatchResultResponseReceived);
							RecordMatchResultRequest->SetURL(ApiUrl + "/recordmatchresult");
							RecordMatchResultRequest->SetVerb("POST");
							RecordMatchResultRequest->SetHeader("Authorization", ServerPassword);
							RecordMatchResultRequest->SetHeader("Content-Type", "application/json");
							RecordMatchResultRequest->SetContentAsString(RequestBody);
							RecordMatchResultRequest->ProcessRequest();
						}
						else {
							GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
						}
					}
					else {
						GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
					}
				}
				else {
					GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
				}
			}
			else {
				GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
			}
#endif
		}
	}

}

void ABattleMobaGameMode::EndRecord() {
#if WITH_GAMELIFT
	if (GameState != nullptr) {
		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
		if (BattleMobaGameState != nullptr) {

			TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
			RequestObj->SetStringField("winningTeam", BattleMobaGameState->Winner);


			auto GetGameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
			if (GetGameSessionIdOutcome.IsSuccess()) {
				RequestObj->SetStringField("gameSessionId", GetGameSessionIdOutcome.GetResult());
				BattleMobaGameState->GameSessionID = GetGameSessionIdOutcome.GetResult();

				FString RequestBody;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
				if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
					TSharedRef<IHttpRequest> RecordMatchResultRequest = HttpModule->CreateRequest();
					RecordMatchResultRequest->OnProcessRequestComplete().BindUObject(this, &ABattleMobaGameMode::OnRecordMatchResultResponseReceived);
					RecordMatchResultRequest->SetURL(ApiUrl + "/recordmatchresult");
					RecordMatchResultRequest->SetVerb("POST");
					RecordMatchResultRequest->SetHeader("Authorization", ServerPassword);
					RecordMatchResultRequest->SetHeader("Content-Type", "application/json");
					RecordMatchResultRequest->SetContentAsString(RequestBody);
					RecordMatchResultRequest->ProcessRequest();
				}
				else {
					GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
				}
			}
			else {
				GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
			}
		}
		else {
			GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
		}
	}
	else {
		GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
	}
#endif
}

void ABattleMobaGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	newPlayer = NewPlayer;

	//set mesh array into temp array
	Chars = CharSelections;

	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Player Added : %s"), *newPlayer->GetFName().ToString()));

		//newPlayer = NewPlayer;
		ABattleMobaPC* MobaPC = Cast<ABattleMobaPC>(newPlayer);

		if (MobaPC)
		{
			Players.Add(MobaPC);

			ABattleMobaPlayerState* PS = Cast <ABattleMobaPlayerState>(MobaPC->PlayerState);
			if (PS)
			{
				GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
				if (GState)
				{
					PS->Pi = Players.Num() - 1;
					if ((PS->Pi) < 4)
					{
						GState->TeamA.Add(PS->GetPlayerName());
						SpawnBasedOnTeam("Radiant", CharSelections[CharIndex]);
						//UpdateLobby();
					}
					else
					{
						GState->TeamB.Add(PS->GetPlayerName());
						SpawnBasedOnTeam("Dire", CharSelections[CharIndex]);
						
					}
					//Random unique number for character mesh array
					//if (Chars.Num() > 0)
					//{
					//	CharIndex = FMath::RandRange(0, Chars.Num() - 1);
					//	//PS->CharMesh = Chars[CharIndex];
					//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Player Index : %d"), Players.Num() - 1));
					//	if ((PS->Pi) < 4)
					//	{
					//		GState->TeamA.Add(PS->GetPlayerName());
					//		SpawnBasedOnTeam("Radiant", CharSelections[CharIndex]);
					//	}
					//	else
					//	{
					//		GState->TeamB.Add(PS->GetPlayerName());
					//		SpawnBasedOnTeam("Dire", CharSelections[CharIndex]);
					//	}
					//	Chars.RemoveAtSwap(CharIndex);
					//}
				}
			}
			if (Players.Num() >= 8)
			{
				GetWorldTimerManager().SetTimer(LobbyClockTimer, this, &ABattleMobaGameMode::StartLobbyClock, 1.0f, true);
				UpdateLobby();
			}
		}
	}
}

/*AActor* ABattleMobaGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Player"));
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* currentPlayerStart = *It;
		if (currentPlayerStart->PlayerStartTag != "Taken")
		{
			currentPlayerStart->PlayerStartTag = "Taken";
			return currentPlayerStart;
		}
	}
	return nullptr;
}*/

//void ABattleMobaGameMode::Logout(AController* Exiting) {
//#if WITH_GAMELIFT
//	if (LatestBackfillTicketId.Len() > 0) {
//		auto GameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
//		if (GameSessionIdOutcome.IsSuccess()) {
//			FString GameSessionId = GameSessionIdOutcome.GetResult();
//			FString MatchmakingConfigurationArn = StartGameSessionState.MatchmakingConfigurationArn;
//			StopBackfillRequest(GameSessionId, MatchmakingConfigurationArn, LatestBackfillTicketId);
//		}
//	}
//	if (Exiting != nullptr) {
//		APlayerState* PlayerState = Exiting->PlayerState;
//		if (PlayerState != nullptr) {
//			ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(PlayerState);
//			const FString& PlayerSessionId = BattleMobaPlayerState->PlayerSessionId;
//			if (PlayerSessionId.Len() > 0) {
//				Aws::GameLift::Server::RemovePlayerSession(TCHAR_TO_ANSI(*PlayerSessionId));
//			}
//		}
//	}
//#endif
//	Super::Logout(Exiting);
//}

void ABattleMobaGameMode::SpawnBasedOnTeam(FName TeamName, USkeletalMesh* CharMesh)
{
	ABattleMobaPlayerState* PS = Cast <ABattleMobaPlayerState>(newPlayer->PlayerState);
	if (PS)
	{
		if (HasAuthority())
		{
			FName Team;
			PS->TeamName = TeamName;
			Team = TeamName;
			//PS->CharMesh = CharMesh;

			AActor* PStart = FindPlayerStart(newPlayer, FString::FromInt(PS->Pi));

			//destroys existing pawn before spawning a new one
			if (newPlayer->GetPawn() != nullptr)
			{
				newPlayer->GetPawn()->Destroy();
			}

			ABattleMobaCharacter* pawn = GetWorld()->SpawnActorDeferred<ABattleMobaCharacter>(SpawnedActor, PStart->GetActorTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
			if (pawn)
			{
				//pawn->PlayerName = PS->GetPlayerName();
				pawn->TeamName = PS->TeamName;
				PS->Team = Team.ToString();
				pawn->CharMesh = PS->CharMesh;
				PS->SpawnTransform = PStart->GetActorTransform();
				UGameplayStatics::FinishSpawningActor(pawn, FTransform(PStart->GetActorRotation(), PStart->GetActorLocation()));

				newPlayer->Possess(pawn);
				newPlayer->ClientSetRotation(PStart->GetActorRotation());

				/*newPlayer->bShowMouseCursor = true;
				newPlayer->SetInputMode(FInputModeGameAndUI());*/
			}
		}
	}
}

//FString ABattleMobaGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
//{
//	FString InitializedString = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
//
//	UE_LOG(LogTemp, Warning, TEXT("Init"));
//
//	//if (NewPlayerController != nullptr) {
//	//	APlayerState* PlayerState = NewPlayerController->PlayerState;
//	//	if (PlayerState != nullptr) {
//	//		ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(PlayerState);
//	//		if (BattleMobaPlayerState != nullptr) {
//	//			if (FMath::RandRange(0, 1) == 0) {
//	//				BattleMobaPlayerState->Team = "Radiant";
//	//			}
//	//			else {
//	//				BattleMobaPlayerState->Team = "Dire";		
//	//			}
//	//		}
//	//	}
//	//}
//#if WITH_EDITOR
//	newPlayer = NewPlayerController;
//
//	//set mesh array into temp array
//	Chars = CharSelections;
//
//	if (HasAuthority())
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Player Added : %s"), *newPlayer->GetFName().ToString()));
//
//		//newPlayer = NewPlayer;
//		ABattleMobaPC* MobaPC = Cast<ABattleMobaPC>(newPlayer);
//
//		if (MobaPC)
//		{
//			Players.Add(MobaPC);
//
//			ABattleMobaPlayerState* PS = Cast <ABattleMobaPlayerState>(MobaPC->PlayerState);
//			if (PS)
//			{
//				GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
//				if (GState)
//				{
//					PS->Pi = Players.Num() - 1;
//
//					//Random unique number for character mesh array
//					if (Chars.Num() > 0)
//					{
//						CharIndex = FMath::RandRange(0, Chars.Num() - 1);
//						//PS->CharMesh = Chars[CharIndex];
//						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Player Index : %d"), Players.Num() - 1));
//						if ((PS->Pi) < 4)
//						{
//							GState->TeamA.Add(PS->GetPlayerName());
//							SpawnBasedOnTeam("Radiant", CharSelections[CharIndex]);
//						}
//						else
//						{
//							GState->TeamB.Add(PS->GetPlayerName());
//							SpawnBasedOnTeam("Dire", CharSelections[CharIndex]);
//						}
//						Chars.RemoveAtSwap(CharIndex);
//					}
//				}
//			}
//		}
//	}
//#endif
//
//#if WITH_GAMELIFT
//	//const FString& PlayerSessionId = UGameplayStatics::ParseOption(Options, "PlayerSessionId");
//	//const FString& PlayerId = UGameplayStatics::ParseOption(Options, "PlayerId");
//	//Possess a pawn
//	//FTimerHandle handle;
//	//FTimerDelegate TimerDelegate;
//	//TimerDelegate.BindLambda([this, NewPlayerController, UniqueId, Options, Portal]()
//	//{
//	const FString& PlayerSessionId = UGameplayStatics::ParseOption(Options, "PlayerSessionId");
//	const FString& PlayerId = UGameplayStatics::ParseOption(Options, "PlayerId");
//
//	//set mesh array into temp array
//	Chars = CharSelections;
//
//	newPlayer = NewPlayerController;
//	if (HasAuthority())
//	{
//		ABattleMobaPC* MobaPC = Cast<ABattleMobaPC>(newPlayer);
//
//		if (MobaPC != nullptr)
//		{
//			Players.Add(MobaPC);
//			if (newPlayer->GetPawn() != nullptr)
//			{
//				newPlayer->Destroy(newPlayer->GetPawn());
//			}
//			GState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
//			if (GState)
//			{
//				APlayerState* PlayerState = newPlayer->PlayerState;
//				if (PlayerState != nullptr)
//				{
//					ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(PlayerState);
//					if (BattleMobaPlayerState != nullptr)
//					{
//						BattleMobaPlayerState->PlayerSessionId = *PlayerSessionId;
//						BattleMobaPlayerState->MatchmakingPlayerId = *PlayerId;
//						GState->PlayerID = *PlayerId;
//						GState->ArrayPlayerID.Add(PlayerId);
//						if (UpdateGameSessionState.PlayerIdToPlayer.Num() > 0)
//						{
//							if (UpdateGameSessionState.PlayerIdToPlayer.Contains(PlayerId))
//							{
//								auto PlayerObj = UpdateGameSessionState.PlayerIdToPlayer.Find(PlayerId);
//								FString Team = PlayerObj->GetTeam();
//								BattleMobaPlayerState->Team = *Team;
//								BattleMobaPlayerState->TeamName = FName(*Team);
//								UE_LOG(LogTemp, Warning, TEXT("Team %s"), *Team);
//								BattleMobaPlayerState->Pi = Players.Num() - 1;
//								//BattleMobaPlayerState->SetPlayerIndex(BattleMobaPlayerState->Pi);
//
//								//Random unique number for character mesh array
//								if (Chars.Num() > 0)
//								{
//									CharIndex = FMath::RandRange(0, Chars.Num() - 1);
//									//BattleMobaPlayerState->CharMesh = Chars[CharIndex];
//									//Chars.RemoveAtSwap(CharIndex);
//									GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Player Index : %d"), Players.Num() - 1));
//									if ((BattleMobaPlayerState->Pi) < 4)
//									{
//										GState->TeamA.Add(BattleMobaPlayerState->GetPlayerName());
//										SpawnBasedOnTeam("Radiant", CharSelections[CharIndex]);
//									}
//									else
//									{
//										GState->TeamB.Add(BattleMobaPlayerState->GetPlayerName());
//										SpawnBasedOnTeam("Dire", CharSelections[CharIndex]);
//									}
//									Chars.RemoveAtSwap(CharIndex);
//								}
//							}
//						}
//						else if (StartGameSessionState.PlayerIdToPlayer.Num() > 0)
//						{
//							if (StartGameSessionState.PlayerIdToPlayer.Contains(PlayerId))
//							{
//								auto PlayerObj = StartGameSessionState.PlayerIdToPlayer.Find(PlayerId);
//								FString Team = PlayerObj->GetTeam();
//								BattleMobaPlayerState->Team = *Team;
//								BattleMobaPlayerState->TeamName = FName(*Team);
//								BattleMobaPlayerState->Pi = Players.Num() - 1;
//								//BattleMobaPlayerState->SetPlayerIndex(BattleMobaPlayerState->Pi);
//								//Random unique number for character mesh array
//								if (Chars.Num() > 0)
//								{
//									CharIndex = FMath::RandRange(0, Chars.Num() - 1);
//									//BattleMobaPlayerState->CharMesh = Chars[CharIndex];
//
//									GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Player Index : %d"), Players.Num() - 1));
//									if ((BattleMobaPlayerState->Pi) < 4)
//									{
//										SpawnBasedOnTeam("Radiant", CharSelections[CharIndex]);
//									}
//									else
//									{
//										SpawnBasedOnTeam("Dire", CharSelections[CharIndex]);
//									}
//									Chars.RemoveAtSwap(CharIndex);
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	//});
//	//this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 0.01f, false);
//#endif
//	return InitializedString;
//}

void ABattleMobaGameMode::CountDownUntilGameOver() {
	if (GameState != nullptr) {
		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
		if (BattleMobaGameState != nullptr) {
			BattleMobaGameState->LatestEvent = FString::FromInt(RemainingGameTime) + " seconds until the game is over";
		}
	}

	if (RemainingGameTime > 0) {
		RemainingGameTime--;
	}
	else {
		GetWorldTimerManager().ClearTimer(CountDownUntilGameOverHandle);
		GetWorldTimerManager().ClearTimer(ClockTimer);
	}
}

void ABattleMobaGameMode::EndGame() {
	//GetWorldTimerManager().ClearTimer(CountDownUntilGameOverHandle);
	GetWorldTimerManager().ClearTimer(EndGameHandle);
	//GetWorldTimerManager().ClearTimer(PickAWinningTeamHandle);
	//GetWorldTimerManager().ClearTimer(HandleProcessTerminationHandle);
	//GetWorldTimerManager().ClearTimer(HandleGameSessionUpdateHandle);
	//GetWorldTimerManager().ClearTimer(SuspendBackfillHandle);
	GetWorldTimerManager().ClearTimer(ClockTimer);

#if WITH_GAMELIFT
	Aws::GameLift::Server::TerminateGameSession();
	Aws::GameLift::Server::ProcessEnding();
	FGenericPlatformMisc::RequestExit(false);
#endif
}

void ABattleMobaGameMode::PickAWinningTeam() {
	GetWorldTimerManager().ClearTimer(CountDownUntilGameOverHandle);
	GetWorldTimerManager().ClearTimer(ClockTimer);

#if WITH_GAMELIFT
	if (GameState != nullptr) {
		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
		if (BattleMobaGameState != nullptr) {
			BattleMobaGameState->LatestEvent = "GameEnded";

			if (BattleMobaGameState->TeamKillA > BattleMobaGameState->TeamKillB) {
				BattleMobaGameState->WinningTeam = "Radiant";
			}
			else if (BattleMobaGameState->TeamKillB > BattleMobaGameState->TeamKillA) {
				BattleMobaGameState->WinningTeam = "Dire";
			}

			TSharedPtr<FJsonObject> RequestObj = MakeShareable(new FJsonObject);
			RequestObj->SetStringField("winningTeam", BattleMobaGameState->WinningTeam);
			RequestObj->SetNumberField("Kill", BattleMobaGameState->Kill);
			RequestObj->SetNumberField("Death", BattleMobaGameState->Death);
			RequestObj->SetNumberField("Assist", BattleMobaGameState->Assist);


			auto GetGameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
			if (GetGameSessionIdOutcome.IsSuccess()) {
				RequestObj->SetStringField("gameSessionId", GetGameSessionIdOutcome.GetResult());
				BattleMobaGameState->GameSessionID = GetGameSessionIdOutcome.GetResult();

				FString RequestBody;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
				if (FJsonSerializer::Serialize(RequestObj.ToSharedRef(), Writer)) {
					TSharedRef<IHttpRequest> RecordMatchResultRequest = HttpModule->CreateRequest();
					RecordMatchResultRequest->OnProcessRequestComplete().BindUObject(this, &ABattleMobaGameMode::OnRecordMatchResultResponseReceived);
					RecordMatchResultRequest->SetURL(ApiUrl + "/recordmatchresult");
					RecordMatchResultRequest->SetVerb("POST");
					RecordMatchResultRequest->SetHeader("Authorization", ServerPassword);
					RecordMatchResultRequest->SetHeader("Content-Type", "application/json");
					RecordMatchResultRequest->SetContentAsString(RequestBody);
					RecordMatchResultRequest->ProcessRequest();
				}
				else {
					GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
				}
			}
			else {
				GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
			}
		}
		else {
			GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
		}
	}
	else {
		GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
	}
#endif
}

//void ABattleMobaGameMode::HandleProcessTermination() {
//	if (ProcessTerminateState.Status) {
//		//GetWorldTimerManager().ClearTimer(CountDownUntilGameOverHandle);
//		GetWorldTimerManager().ClearTimer(HandleProcessTerminationHandle);
//		GetWorldTimerManager().ClearTimer(HandleGameSessionUpdateHandle);
//		GetWorldTimerManager().ClearTimer(SuspendBackfillHandle);
//		GetWorldTimerManager().ClearTimer(ClockTimer);
//		GetWorldTimerManager().ClearTimer(LobbyClockTimer);
//
//#if WITH_GAMELIFT
//		if (LatestBackfillTicketId.Len() > 0) {
//			auto GameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
//			if (GameSessionIdOutcome.IsSuccess()) {
//				FString GameSessionArn = FString(GameSessionIdOutcome.GetResult());
//				FString MatchmakingConfigurationArn = StartGameSessionState.MatchmakingConfigurationArn;
//				StopBackfillRequest(GameSessionArn, MatchmakingConfigurationArn, LatestBackfillTicketId);
//			}
//		}
//#endif
//
//		FString ProcessInterruptionMessage;
//
//		if (ProcessTerminateState.TerminationTime <= 0L) {
//			ProcessInterruptionMessage = "Server process could shut down at any time";
//		}
//		else {
//			long TimeLeft = (long)(ProcessTerminateState.TerminationTime - FDateTime::Now().ToUnixTimestamp());
//			ProcessInterruptionMessage = FString::Printf(TEXT("Server process scheduled to terminate in %ld seconds"), TimeLeft);
//		}
//
//		if (GameState != nullptr) {
//			ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
//			if (BattleMobaGameState != nullptr) {
//				BattleMobaGameState->LatestEvent = ProcessInterruptionMessage;
//			}
//		}
//
//		GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 10.0f);
//	}
//}
//
//void ABattleMobaGameMode::HandleGameSessionUpdate() {
//#if WITH_GAMELIFT
//	if (!GameSessionActivated) {
//		if (StartGameSessionState.Status) {
//			GameSessionActivated = true;
//
//			ExpectedPlayers = StartGameSessionState.PlayerIdToPlayer;
//
//			WaitingForPlayersToJoin = true;
//
//			//GetWorldTimerManager().SetTimer(PickAWinningTeamHandle, this, &ABattleMobaGameMode::PickAWinningTeam, 1.0f, false, (float)RemainingGameTime);
//			GetWorldTimerManager().SetTimer(SuspendBackfillHandle, this, &ABattleMobaGameMode::SuspendBackfill, 1.0f, false, (float)(RemainingGameTime - 60));
//			GetWorldTimerManager().SetTimer(LobbyClockTimer, this, &ABattleMobaGameMode::StartLobbyClock, 1.0f, true);
//			//GetWorldTimerManager().SetTimer(ClockTimer, this, &ABattleMobaGameMode::StartClock, 1.0f, true, 0.0f);
//		}
//	}
//	else if (WaitingForPlayersToJoin) {
//		if (TimeSpentWaitingForPlayersToJoin < 60) {
//			auto GameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
//			if (GameSessionIdOutcome.IsSuccess()) {
//				FString GameSessionId = FString(GameSessionIdOutcome.GetResult());
//
//				Aws::GameLift::Server::Model::DescribePlayerSessionsRequest DescribePlayerSessionsRequest;
//				DescribePlayerSessionsRequest.SetGameSessionId(TCHAR_TO_ANSI(*GameSessionId));
//				DescribePlayerSessionsRequest.SetPlayerSessionStatusFilter("RESERVED");
//
//				auto DescribePlayerSessionsOutcome = Aws::GameLift::Server::DescribePlayerSessions(DescribePlayerSessionsRequest);
//				if (DescribePlayerSessionsOutcome.IsSuccess()) {
//					auto DescribePlayerSessionsResult = DescribePlayerSessionsOutcome.GetResult();
//					int Count = DescribePlayerSessionsResult.GetPlayerSessionsCount();
//					if (Count == 0) {
//						UpdateGameSessionState.Reason = EUpdateReason::BACKFILL_COMPLETED;
//
//						WaitingForPlayersToJoin = false;
//						TimeSpentWaitingForPlayersToJoin = 0;
//					}
//					else {
//						TimeSpentWaitingForPlayersToJoin++;
//					}
//				}
//				else {
//					TimeSpentWaitingForPlayersToJoin++;
//				}
//			}
//			else {
//				TimeSpentWaitingForPlayersToJoin++;
//			}
//		}
//		else {
//			UpdateGameSessionState.Reason = EUpdateReason::BACKFILL_COMPLETED;
//
//			WaitingForPlayersToJoin = false;
//			TimeSpentWaitingForPlayersToJoin = 0;
//		}
//	}
//	else if (UpdateGameSessionState.Reason == EUpdateReason::MATCHMAKING_DATA_UPDATED) {
//		LatestBackfillTicketId = "";
//		ExpectedPlayers = UpdateGameSessionState.PlayerIdToPlayer;
//
//		WaitingForPlayersToJoin = true;
//	}
//	else if (UpdateGameSessionState.Reason == EUpdateReason::BACKFILL_CANCELLED || UpdateGameSessionState.Reason == EUpdateReason::BACKFILL_COMPLETED
//		|| UpdateGameSessionState.Reason == EUpdateReason::BACKFILL_FAILED || UpdateGameSessionState.Reason == EUpdateReason::BACKFILL_TIMED_OUT) {
//		LatestBackfillTicketId = "";
//
//		TArray<APlayerState*> PlayerStates = GetWorld()->GetGameState()->PlayerArray;
//
//		TMap<FString, Aws::GameLift::Server::Model::Player> ConnectedPlayers;
//		for (APlayerState* PlayerState : PlayerStates) {
//			if (PlayerState != nullptr) {
//				ABattleMobaPlayerState* BattleMobaPlayerState = Cast<ABattleMobaPlayerState>(PlayerState);
//				if (BattleMobaPlayerState != nullptr) {
//					auto PlayerObj = ExpectedPlayers.Find(BattleMobaPlayerState->MatchmakingPlayerId);
//					if (PlayerObj != nullptr) {
//						ConnectedPlayers.Add(BattleMobaPlayerState->MatchmakingPlayerId, *PlayerObj);
//					}
//				}
//			}
//		}
//
//		if (ConnectedPlayers.Num() == 0) {
//			EndGame();
//		}
//		else if (ConnectedPlayers.Num() < 4) {
//			auto GameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
//			if (GameSessionIdOutcome.IsSuccess()) {
//				FString GameSessionId = FString(GameSessionIdOutcome.GetResult());
//				FString MatchmakingConfigurationArn = StartGameSessionState.MatchmakingConfigurationArn;
//				LatestBackfillTicketId = CreateBackfillRequest(GameSessionId, MatchmakingConfigurationArn, ConnectedPlayers);
//				if (LatestBackfillTicketId.Len() > 0) {
//					UpdateGameSessionState.Reason = EUpdateReason::BACKFILL_INITIATED;
//				}
//			}
//		}
//	}
//#endif
//}

//FRewards* ABattleMobaGameMode::GetRewardsData(FName& rowName, int rowIndex)
//{
//	if (RewardTable != nullptr)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Array length : %d"), ((RewardTable->GetRowNames().Num()))));
//
//		if (RewardTable->GetRowNames().IsValidIndex(0) && RewardTable->GetRowNames().IsValidIndex(rowIndex))
//		{
//			rowName = RewardTable->GetRowNames()[rowIndex];
//			FRewards* row = RewardTable->FindRow<FRewards>(rowName, FString());
//			return row;
//		}
//	}
//	return nullptr;
//}

void ABattleMobaGameMode::PlayerKilled(ABattleMobaPlayerState* victim, ABattleMobaPlayerState* killer, TArray<ABattleMobaPlayerState*> assist)
{
	FName rowName = RewardTable->GetRowNames()[victim->Level];
	FRewards* row = RewardTable->FindRow<FRewards>(rowName, FString());
	if (row)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("ROW FOUND")));

		if (assist.IsValidIndex(0))
		{
			for (int32 i = 0; i < assist.Num() - 1; i++)
			{
				if (assist[i] != assist.Last())
				{
					assist[i]->Assist += 1;
					GState->Assist = assist[i]->Assist;

					int exp;
					int honor;

					//Get victim level
					if (UInputLibrary::CalculateRewards(HonorKill, assist.Num(), row, rowName, honor, exp))
					{
						//add honor value
						assist[i]->Honor += honor;
						//Set assist experience point
						assist[i]->ClientSetExp(exp);
					}
				}
			}
		}
		if (killer != victim)
		{
			victim->Death += 1;
			GState->Death += 1;
			killer->Kill += 1;
			GState->Kill += 1;

			int exp;
			int honor;

			//Get victim level
			if (UInputLibrary::CalculateRewards(HonorKill, assist.Num(), row, rowName, honor, exp))
			{
				//add honor value
				killer->Honor += honor;
				//Set kill experience point
				killer->ClientSetExp(row->ExpKills);
			}
			if (killer->TeamName == "Radiant")
			{
				GState->TeamKillA += 1;
			}
			else if (killer->TeamName == "Dire")
			{
				GState->TeamKillB += 1;
			}
		}
	}
}

bool ABattleMobaGameMode::RespawnRequested_Validate(APlayerController* playerController, FTransform SpawnTransform)
{
	return true;
}

void ABattleMobaGameMode::RespawnRequested_Implementation(APlayerController* playerController, FTransform SpawnTransform)
{
	if (playerController != nullptr)
	{
		if (HasAuthority())
		{
			//destroys existing pawn before spawning a new one
			if (playerController->GetPawn() != nullptr)
			{
				playerController->GetPawn()->Destroy();
			}
			ABattleMobaPlayerState* PS = Cast<ABattleMobaPlayerState>(playerController->PlayerState);
			{
				ABattleMobaPC* pc = Cast<ABattleMobaPC>(playerController);
				//Spawn actor
				if (SpawnedActor && pc)
				{
					//Spawn actor from SpawnedActor subclass
					ABattleMobaCharacter* pawn = GetWorld()->SpawnActorDeferred<ABattleMobaCharacter>(SpawnedActor, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
					if (pawn)
					{
						//Assign team and player name before finish spawning
						pawn->PlayerName = PS->Username;
						pawn->TeamName = PS->TeamName;
						pawn->CharMesh = PS->CharMesh;

						UGameplayStatics::FinishSpawningActor(pawn, FTransform(SpawnTransform.Rotator(), SpawnTransform.GetLocation()));
					}

					//possess and set new rotation for newly spawned pawn
					playerController->Possess(pawn);
					playerController->ClientSetRotation(pawn->GetActorRotation());
					pc->SetupPawnAttribute();
					/*playerController->bShowMouseCursor = false;
					playerController->GetPawn()->EnableInput(playerController);*/
				}
			}
		}
	}
}

void ABattleMobaGameMode::OnRecordMatchResultResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (GameState != nullptr) {
		ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(GameState);
		if (BattleMobaGameState != nullptr) {
			BattleMobaGameState->UpdateKDACheck = true;
			GetWorldTimerManager().SetTimer(EndGameHandle, this, &ABattleMobaGameMode::EndGame, 1.0f, false, 5.0f);
		}
	}
}

//void ABattleMobaGameMode::SuspendBackfill() {
//	GetWorldTimerManager().ClearTimer(HandleGameSessionUpdateHandle);
//#if WITH_GAMELIFT
//	if (LatestBackfillTicketId.Len() > 0) {
//		auto GameSessionIdOutcome = Aws::GameLift::Server::GetGameSessionId();
//		if (GameSessionIdOutcome.IsSuccess()) {
//			FString GameSessionId = GameSessionIdOutcome.GetResult();
//			FString MatchmakingConfigurationArn = StartGameSessionState.MatchmakingConfigurationArn;
//			if (!StopBackfillRequest(GameSessionId, MatchmakingConfigurationArn, LatestBackfillTicketId)) {
//				GetWorldTimerManager().SetTimer(SuspendBackfillHandle, this, &ABattleMobaGameMode::SuspendBackfill, 1.0f, false, 1.0f);
//			}
//		}
//		else {
//			GetWorldTimerManager().SetTimer(SuspendBackfillHandle, this, &ABattleMobaGameMode::SuspendBackfill, 1.0f, false, 1.0f);
//		}
//	}
//#endif
//}
//
//FString ABattleMobaGameMode::CreateBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, TMap<FString, Aws::GameLift::Server::Model::Player> Playerss) {
//#if WITH_GAMELIFT
//	Aws::GameLift::Server::Model::StartMatchBackfillRequest StartMatchBackfillRequest;
//	StartMatchBackfillRequest.SetGameSessionArn(TCHAR_TO_ANSI(*GameSessionArn));
//	StartMatchBackfillRequest.SetMatchmakingConfigurationArn(TCHAR_TO_ANSI(*MatchmakingConfigurationArn));
//
//	for (auto& Elem : Playerss) {
//		auto PlayerObj = Elem.Value;
//		StartMatchBackfillRequest.AddPlayer(PlayerObj);
//	}
//
//	auto StartMatchBackfillOutcome = Aws::GameLift::Server::StartMatchBackfill(StartMatchBackfillRequest);
//	if (StartMatchBackfillOutcome.IsSuccess()) {
//		return StartMatchBackfillOutcome.GetResult().GetTicketId();
//	}
//	else {
//		return "";
//	}
//#endif
//	return "";
//}
//
//bool ABattleMobaGameMode::StopBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, FString TicketId) {
//#if WITH_GAMELIFT
//	Aws::GameLift::Server::Model::StopMatchBackfillRequest StopMatchBackfillRequest;
//	StopMatchBackfillRequest.SetGameSessionArn(TCHAR_TO_ANSI(*GameSessionArn));
//	StopMatchBackfillRequest.SetMatchmakingConfigurationArn(TCHAR_TO_ANSI(*MatchmakingConfigurationArn));
//	StopMatchBackfillRequest.SetTicketId(TCHAR_TO_ANSI(*TicketId));
//
//	auto StopMatchBackfillOutcome = Aws::GameLift::Server::StopMatchBackfill(StopMatchBackfillRequest);
//
//	return StopMatchBackfillOutcome.IsSuccess();
//#endif
//	return false;
//}