// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaPlayerState.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "InputLibrary.h"
#include "BattleMobaCharacter.h"

void ABattleMobaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaPlayerState, Level);
	DOREPLIFETIME(ABattleMobaPlayerState, Honor);
	DOREPLIFETIME(ABattleMobaPlayerState, ExpNeeded);
	DOREPLIFETIME(ABattleMobaPlayerState, Exp);
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
	DOREPLIFETIME(ABattleMobaPlayerState, BaseDamagePercent);
	DOREPLIFETIME(ABattleMobaPlayerState, StyleName);
	DOREPLIFETIME(ABattleMobaPlayerState, FrontHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, BackHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, RightHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, LeftHitMoveset);
	DOREPLIFETIME(ABattleMobaPlayerState, SkillComponent);
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
		this->GetWorldTimerManager().ClearTimer(RespawnHandle);
		ps->RespawnTimeCounter = 30;
		MulticastTimerCount(ps->RespawnTimeCounter);
	}
	else if (ps->RespawnTimeCounter > 0)
	{
		ps->RespawnTimeCounter -= 1;
		MulticastTimerCount(ps->RespawnTimeCounter);
	}
}

void ABattleMobaPlayerState::SetCurrentPlayerLevel()
{
	if (LevelTable != nullptr)
	{
		//Set initial attributes
		FName NextRowName = LevelTable->GetRowNames()[Level];
		FLevelAttributes* Nextrow = LevelTable->FindRow<FLevelAttributes>(NextRowName, FString());
		if (Nextrow)
		{
			ExpNeeded = Nextrow->MinExpPerLevel;
			Level = Nextrow->Level - 1;
		}
	}
}

bool ABattleMobaPlayerState::ServerSetExp_Validate(int EXPoint)
{
	return true;
}

void ABattleMobaPlayerState::ServerSetExp_Implementation(int EXPoint)
{
	ClientSetExp(EXPoint);
}

bool ABattleMobaPlayerState::ClientSetExp_Validate(int EXPoint)
{
	return true;
}

void ABattleMobaPlayerState::ClientSetExp_Implementation(int EXPoint)
{
	AddExp(EXPoint, this->Level);
}

void ABattleMobaPlayerState::AddExp(int EXPoint, int& OutLevel)
{
	//Get last row of datatable
	FName lastRowName = LevelTable->GetRowNames()[LevelTable->GetRowNames().Num()-1];
	FLevelAttributes* lastRow = LevelTable->FindRow<FLevelAttributes>(lastRowName, FString());

	Exp = FMath::Clamp(Exp + EXPoint, 0, lastRow->MinExpPerLevel);

	//if enough exp, level up
	if (Exp >= ExpNeeded)
	{
		//Level++;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("Exp : %d"), EXPoint));

		Level = FMath::Clamp(Level+1, 1, lastRow->Level);
		/*Level++;*/

		//Set the remainder exp from prev level to current exp of current level
		//Exp = Exp - ExpNeeded;

		//Get new row of datatable
		if (LevelTable->GetRowNames().IsValidIndex(Level))
		{
			FName newRowName = LevelTable->GetRowNames()[Level];
			FLevelAttributes* newRow = LevelTable->FindRow<FLevelAttributes>(newRowName, FString());

			if (newRow)
			{
				//to clamp exp value needed for each level
				ExpNeeded = newRow->MinExpPerLevel;
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("ExpNeeded : %d"), ExpNeeded));

				//Adjust base stats
				FName curRowName = LevelTable->GetRowNames()[Level-1];
				FLevelAttributes* Row = LevelTable->FindRow<FLevelAttributes>(curRowName, FString());
				if (Row)
				{
					MaxHealth = UInputLibrary::ChangeValueByPercentage(MaxHealth, Row->HPIncrementPercent, true);
					Defense = UInputLibrary::ChangeValueByPercentage(Defense, Row->DefIncrementPercent, true);
					BaseDamagePercent = Row->DmgIncrementPercent;

					Row->SkillUnlock;

					ABattleMobaCharacter* player = Cast<ABattleMobaCharacter>(GetPawn());
					if (player)
					{
						if (player->IsLocallyControlled())
						{
							player->ServerSetupBaseStats(MaxHealth, Defense);
						}
					}
				}
			}
		}
		
		//return level
		OutLevel = Level;
	}
}
