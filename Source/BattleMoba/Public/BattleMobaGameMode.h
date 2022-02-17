#pragma once

#include "CoreMinimal.h"
#include "InputLibrary.h"
#include "GameLiftServerSDK.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BattleMobaGameMode.generated.h"

//UENUM()
//enum class EUpdateReason : uint8
//{
//	NO_UPDATE_RECEIVED,
//	BACKFILL_INITIATED,
//	MATCHMAKING_DATA_UPDATED,
//	BACKFILL_FAILED,
//	BACKFILL_TIMED_OUT,
//	BACKFILL_CANCELLED,
//	BACKFILL_COMPLETED
//};
//
//USTRUCT()
//struct FStartGameSessionState
//{
//	GENERATED_BODY();
//
//	UPROPERTY()
//		bool Status;
//
//	UPROPERTY()
//		FString MatchmakingConfigurationArn;
//
//	TMap<FString, Aws::GameLift::Server::Model::Player> PlayerIdToPlayer;
//
//	FStartGameSessionState() {
//		Status = false;
//	}
//};
//
//USTRUCT()
//struct FUpdateGameSessionState
//{
//	GENERATED_BODY();
//
//	UPROPERTY()
//		EUpdateReason Reason;
//
//	TMap<FString, Aws::GameLift::Server::Model::Player> PlayerIdToPlayer;
//
//	FUpdateGameSessionState() {
//		Reason = EUpdateReason::NO_UPDATE_RECEIVED;
//	}
//};
//
//USTRUCT()
//struct FProcessTerminateState
//{
//	GENERATED_BODY();
//
//	UPROPERTY()
//		bool Status;
//
//	long TerminationTime;
//
//	FProcessTerminateState() {
//		Status = false;
//		TerminationTime = 0L;
//	}
//};
//
//USTRUCT()
//struct FHealthCheckState
//{
//	GENERATED_BODY();
//
//	UPROPERTY()
//		bool Status;
//
//	FHealthCheckState() {
//		Status = false;
//	}
//};

class ABattleMobaCharacter;
class ABattleMobaGameState;
class ABattleMobaPlayerState;

UCLASS(minimalapi)
class ABattleMobaGameMode : public AGameModeBase
{
	GENERATED_BODY()

		//Replicated Network setup
		void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
		ABattleMobaGameState* GState;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
		ABattleMobaPlayerState* PState;

	/*Blueprint Reference of ThirdPersonCharacter class*/
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<ABattleMobaCharacter> SpawnedActor;

	//************************Clock***********************//
	UPROPERTY(BlueprintReadWrite, Category = "Clock")
		float InitialTimer = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Clock")
		float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
		float EndTime = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		FString MapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UDataTable* RewardTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item System")
		class UItemData* ItemDatabase;

protected:

	virtual void BeginPlay() override;

	//virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	UFUNCTION()
		void StartClock();

	UFUNCTION()
		void StartLobbyClock();

	UFUNCTION(BlueprintCallable)
		void SpawnBasedOnTeam(FName TeamName, USkeletalMesh* CharMesh);

	TArray<USkeletalMesh*> Chars;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TArray<USkeletalMesh*> CharSelections;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
		int32 CharIndex = 0;

public:

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "ActorSpawning")
		TArray<class ABattleMobaPC*> Players;

	UPROPERTY()
		FTimerHandle CountDownUntilGameOverHandle;

	UPROPERTY()
		FTimerHandle EndGameHandle;

	UPROPERTY()
		FTimerHandle PickAWinningTeamHandle;

	//UPROPERTY()
	//	FTimerHandle HandleProcessTerminationHandle;

	//UPROPERTY()
	//	FTimerHandle HandleGameSessionUpdateHandle;

	//UPROPERTY()
	//	FTimerHandle SuspendBackfillHandle;

	UPROPERTY()
		FTimerHandle ClockTimer;

	UPROPERTY()
		FTimerHandle LobbyClockTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewPlayer")
		APlayerController* newPlayer;

public:
	ABattleMobaGameMode();

	//virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	//virtual void Logout(AController* Exiting) override;

	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(Reliable, Server, WithValidation, Category = "ArtifactShop")
		void PopulateShopItem(ABattleMobaPC* pc);

	UFUNCTION(Reliable, Server, WithValidation, Category = "Respawn")
		void RespawnRequested(APlayerController* playerController, FTransform SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Score")
		void PlayerKilled(ABattleMobaPlayerState* victim, ABattleMobaPlayerState* killer, TArray<ABattleMobaPlayerState*> assist);

	////Get row from Rewards datatable
	//FRewards* GetRewardsData(FName& rowName, int rowIndex);

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
		void EndRecord();

	UFUNCTION(BlueprintImplementableEvent, Category = "Players")
		void UpdateLobby();

	UFUNCTION(BlueprintImplementableEvent, Category = "Server")
		void MatchResult(const FString &Winner);

	UFUNCTION(BlueprintCallable, Category = "Server")
		void DynamoDBProcessMatchResults(FString AWSGameSessionId, FString Winner, FString PID1, FString PID2, FString PID3, FString PID4, FString PID5, FString PID6, FString PID7, FString PID8, FString N1, FString N2, FString N3, FString N4, FString N5, FString N6, FString N7, FString N8, FString C1, FString C2, FString C3, FString C4, FString C5, FString C6, FString C7, FString C8, FString Kill1, FString Kill2, FString Kill3, FString Kill4, FString Kill5, FString Kill6, FString Kill7, FString Kill8, FString Death1, FString Death2, FString Death3, FString Death4, FString Death5, FString Death6, FString Death7, FString Death8, FString Assist1, FString Assist2, FString Assist3, FString Assist4, FString Assist5, FString Assist6, FString Assist7, FString Assist8, FString Honor1, FString Honor2, FString Honor3, FString Honor4, FString Honor5, FString Honor6, FString Honor7, FString Honor8, FString Level1, FString Level2, FString Level3, FString Level4, FString Level5, FString Level6, FString Level7, FString Level8);

///////////////////////////////////////////inventory/////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item System")
		FItem FindItem(FName ItemID, bool& IsSuccess);

	FItem FindItem_Implementation(FName ItemID, bool& IsSuccess);
/////////////////////////////////////////////////////////////////////////////////////////////////

private:

	//Initial honor val per kill
	const int HonorKill = 200;

	FHttpModule* HttpModule;

	//UPROPERTY()
	//	FStartGameSessionState StartGameSessionState;

	//UPROPERTY()
	//	FUpdateGameSessionState UpdateGameSessionState;

	//UPROPERTY()
	//	FProcessTerminateState ProcessTerminateState;

	//UPROPERTY()
	//	FHealthCheckState HealthCheckState;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		FString ServerPassword;

	UPROPERTY()
		float RemainingGameTime;

	UPROPERTY()
		float LobbyTimer;

	UPROPERTY()
		bool GameSessionActivated;

	//UPROPERTY()
	//	FString LatestBackfillTicketId;

	UPROPERTY()
		bool WaitingForPlayersToJoin;

	UPROPERTY()
		int TimeSpentWaitingForPlayersToJoin;

	TMap<FString, Aws::GameLift::Server::Model::Player> ExpectedPlayers;

	UFUNCTION()
		void CountDownUntilGameOver();

	UFUNCTION()
		void EndGame();

	UFUNCTION()
		void PickAWinningTeam();

	//UFUNCTION()
	//	void HandleProcessTermination();

	//UFUNCTION()
	//	void HandleGameSessionUpdate();

	//UFUNCTION()
	//	void SuspendBackfill();



	//FString CreateBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, TMap<FString, Aws::GameLift::Server::Model::Player> Players);
	//bool StopBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, FString TicketId);
	void OnRecordMatchResultResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
