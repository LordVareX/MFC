// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "InputLibrary.h"
#include "ItemInterface.h"
#include "BattleMobaPC.generated.h"

class ABattleMobaGameMode;
/**
 *
 */
UCLASS()
class BATTLEMOBA_API ABattleMobaPC : public APlayerController, public IItemInterface
{
	GENERATED_BODY()

		ABattleMobaPC();

	//Replicated Network setup
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	//Equipment artifacts on UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifacts")
		TMap<FName, FItem> EquipmentArtifacts;

	//Max slots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifacts")
		int32 TotalEquipmentSlots = 4;

public:

	virtual void BeginPlay() override;

///////////////////////////////Artifacts Interaction//////////////////////////////////// 

	void AddItem(FName ItemID);

	void RemoveItem(FName ItemID, bool RemovedFromInventory);

	bool HasFreeInventorySlots();

	//interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
		void OnInteract();

	//Actual implementation of the Interact event
	void OnInteract_Implementation();
	virtual FName GetName() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void OnRefreshInventory();

//////////////////////////////////////////////////////////////////////////////////////

	UPROPERTY()
		ABattleMobaGameMode* GM;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spectator")
		int32 currentPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spectator")
		ABattleMobaPC* CurrSpectator;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "ID")
		int32 pi;

	//RequestRespawn
	UFUNCTION(Reliable, Server, WithValidation, Category = "Respawn")
		void RespawnPawn(FTransform SpawnTransform);

	UFUNCTION(BlueprintImplementableEvent, Category = "Players")
		void NameChangeRequest(const FString &PlayerName, int32 PIndex);

	UFUNCTION(Reliable, Client, WithValidation, Category = "Respawn")
		void SetupPawnAttribute();

	//Widget holder
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD", Meta = (ExposeOnSpawn = "true"))
		UUserWidget* MainWidget = nullptr;

protected:

	UFUNCTION()
		void Action();

	//spectator pi
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "SpectID")
		int32 SpectPI;

	UFUNCTION(BlueprintPure, Category = "Increment")
		static int32 CheckIndexValidity(int32 index, TArray<ABattleMobaPC*> PlayerList, EFormula SwitchMode);

	UFUNCTION(BlueprintCallable, Reliable, Client, WithValidation, Category = "InputMode")
		void ClientSetInputMode();

	//RequestSpectator
	UFUNCTION(BlueprintCallable, Reliable, Server, WithValidation, Category = "Spectator")
		void SetupSpectator(EFormula SwitchMode);

	//SpectatorMode
	UFUNCTION(Reliable, Server, WithValidation, Category = "Spectator")
		void SpectateNextPlayer(const TArray<ABattleMobaPC*>& PlayerList, EFormula SwitchMode);
};
