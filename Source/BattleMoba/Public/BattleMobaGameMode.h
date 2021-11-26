#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerSDK.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BattleMobaGameMode.generated.h"

UENUM()
enum class EUpdateReason : uint8
{
	NO_UPDATE_RECEIVED,
	BACKFILL_INITIATED,
	MATCHMAKING_DATA_UPDATED,
	BACKFILL_FAILED,
	BACKFILL_TIMED_OUT,
	BACKFILL_CANCELLED,
	BACKFILL_COMPLETED
};

USTRUCT()
struct FStartGameSessionState
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	UPROPERTY()
		FString MatchmakingConfigurationArn;

	TMap<FString, Aws::GameLift::Server::Model::Player> PlayerIdToPlayer;

	FStartGameSessionState() {
		Status = false;
	}
};

USTRUCT()
struct FUpdateGameSessionState
{
	GENERATED_BODY();

	UPROPERTY()
		EUpdateReason Reason;

	TMap<FString, Aws::GameLift::Server::Model::Player> PlayerIdToPlayer;

	FUpdateGameSessionState() {
		Reason = EUpdateReason::NO_UPDATE_RECEIVED;
	}
};

USTRUCT()
struct FProcessTerminateState
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	long TerminationTime;

	FProcessTerminateState() {
		Status = false;
		TerminationTime = 0L;
	}
};

USTRUCT()
struct FHealthCheckState
{
	GENERATED_BODY();

	UPROPERTY()
		bool Status;

	FHealthCheckState() {
		Status = false;
	}
};

class ABattleMobaCharacter;
class ABattleMobaGameState;

UCLASS(minimalapi)
class ABattleMobaGameMode : public AGameModeBase
{
	GENERATED_BODY()

		//Replicated Network setup
		void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
		ABattleMobaGameState* GState;

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



protected:

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

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

	UPROPERTY()
		FTimerHandle HandleProcessTerminationHandle;

	UPROPERTY()
		FTimerHandle HandleGameSessionUpdateHandle;

	UPROPERTY()
		FTimerHandle SuspendBackfillHandle;

	UPROPERTY()
		FTimerHandle ClockTimer;

	UPROPERTY()
		FTimerHandle LobbyClockTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewPlayer")
		APlayerController* newPlayer;

public:
	ABattleMobaGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void Logout(AController* Exiting) override;

	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(Reliable, Server, WithValidation, Category = "Respawn")
		void RespawnRequested(APlayerController* playerController, FTransform SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Score")
		void PlayerKilled(ABattleMobaPlayerState* victim, ABattleMobaPlayerState* killer, TArray<ABattleMobaPlayerState*> assist);

	UFUNCTION(BlueprintCallable, Category = "Score")
		void StartRespawnTimer(ABattleMobaPlayerState* ps);

	void RespawnTimerCount(FTimerHandle* RespawnHandle, ABattleMobaPlayerState* ps);


	//virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
		void EndRecord();

private:
	FHttpModule* HttpModule;

	UPROPERTY()
		FStartGameSessionState StartGameSessionState;

	UPROPERTY()
		FUpdateGameSessionState UpdateGameSessionState;

	UPROPERTY()
		FProcessTerminateState ProcessTerminateState;

	UPROPERTY()
		FHealthCheckState HealthCheckState;

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

	UPROPERTY()
		FString LatestBackfillTicketId;

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

	UFUNCTION()
		void HandleProcessTermination();

	UFUNCTION()
		void HandleGameSessionUpdate();

	UFUNCTION()
		void SuspendBackfill();



	FString CreateBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, TMap<FString, Aws::GameLift::Server::Model::Player> Players);
	bool StopBackfillRequest(FString GameSessionArn, FString MatchmakingConfigurationArn, FString TicketId);
	void OnRecordMatchResultResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
