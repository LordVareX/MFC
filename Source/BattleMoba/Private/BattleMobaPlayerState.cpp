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
	DOREPLIFETIME(ABattleMobaPlayerState, AWSPlayerSessionId);
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
	DOREPLIFETIME(ABattleMobaPlayerState, StyleName);
	DOREPLIFETIME(ABattleMobaPlayerState, FrontHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, BackHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, RightHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, LeftHitMoveset);
}

void ABattleMobaPlayerState::OnRep_Timer()
{
	this->DisplayRespawnTime(RespawnTimeCounter);
}

bool ABattleMobaPlayerState::MulticastTimerCount_Validate(int32 val)
{
	return true;
}

void ABattleMobaPlayerState::MulticastTimerCount_Implementation(int32 val)
{
	RespawnTimeCounter = val;
	OnRep_Timer();
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

bool ABattleMobaPlayerState::StartRespawnTimer_Validate(ABattleMobaPlayerState* ps)
{
	return true;
}

void ABattleMobaPlayerState::StartRespawnTimer_Implementation(ABattleMobaPlayerState* ps)
{
	FTimerDelegate FunctionsName;

	//FunctionsName = FTimerDelegate::CreateUObject(this, &ATodakBattleArenaCharacter::UpdateHealthStatusBar, EBarType::PrimaryProgressBar);
	FunctionsName = FTimerDelegate::CreateUObject(this, &ABattleMobaPlayerState::RespawnTimerCount, ps);

	UE_LOG(LogTemp, Warning, TEXT("RespawnTimer started!"));
	GetWorld()->GetTimerManager().SetTimer(RespawnHandle, FunctionsName, 1.0f, true);
}

bool ABattleMobaPlayerState::RespawnTimerCount_Validate(ABattleMobaPlayerState* ps)
{
	return true;
}

void ABattleMobaPlayerState::RespawnTimerCount_Implementation(ABattleMobaPlayerState* ps)
{
	if (ps->RespawnTimeCounter <= 0)
	{
		//this->GetWorldTimerManager().ClearTimer(RespawnHandle);
		MulticastTimerCount(ps->RespawnTimeCounter);
		ps->RespawnTimeCounter = 30;
	}
	{
		if (ps->RespawnTimeCounter > 0)
		{
			ps->RespawnTimeCounter -= 1;
			MulticastTimerCount(ps->RespawnTimeCounter);
		}
	}
}
