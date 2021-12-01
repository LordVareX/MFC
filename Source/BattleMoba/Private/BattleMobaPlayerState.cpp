// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaPlayerState.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

void ABattleMobaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaPlayerState, Pi);
	DOREPLIFETIME(ABattleMobaPlayerState, CurrentStyle);
	DOREPLIFETIME(ABattleMobaPlayerState, Kill);
	DOREPLIFETIME(ABattleMobaPlayerState, Death);
	DOREPLIFETIME(ABattleMobaPlayerState, Assist);
	DOREPLIFETIME(ABattleMobaPlayerState, Username);
	DOREPLIFETIME(ABattleMobaPlayerState, AWSPlayerId);
	DOREPLIFETIME(ABattleMobaPlayerState, TeamName);
	DOREPLIFETIME(ABattleMobaPlayerState, Team);
	DOREPLIFETIME(ABattleMobaPlayerState, CharMesh);
	DOREPLIFETIME(ABattleMobaPlayerState, bTeamB);
	DOREPLIFETIME(ABattleMobaPlayerState, TeamRef);
	DOREPLIFETIME(ABattleMobaPlayerState, ChiOrbs);
	DOREPLIFETIME(ABattleMobaPlayerState, RespawnTimeCounter);
	DOREPLIFETIME(ABattleMobaPlayerState, RespawnHandle);
	DOREPLIFETIME(ABattleMobaPlayerState, MaxHealth);
	DOREPLIFETIME(ABattleMobaPlayerState, Defense);
}

bool ABattleMobaPlayerState::SetPlayerIndex_Validate(int32 PlayerIndex)
{
	return true;
}

void ABattleMobaPlayerState::SetPlayerIndex_Implementation(int32 PlayerIndex)
{
	this->Pi = PlayerIndex;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("PlayerIndex : %f"), this->Pi));
}