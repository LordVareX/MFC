// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaPlayerState.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "InputLibrary.h"
#include "BattleMobaCharacter.h"
#include "BattleMobaInterface.h"
#include "BattleMobaGameState.h"
#include "BattleMobaGameMode.h"

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
	DOREPLIFETIME(ABattleMobaPlayerState, RespawnTimeCounter);
	DOREPLIFETIME(ABattleMobaPlayerState, InitRespawnTime);
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
	DOREPLIFETIME(ABattleMobaPlayerState, AtkSpeed);
	DOREPLIFETIME(ABattleMobaPlayerState, MoveSpeed);
	DOREPLIFETIME(ABattleMobaPlayerState, ImmunityDur);
	DOREPLIFETIME(ABattleMobaPlayerState, StunDuration);
	DOREPLIFETIME(ABattleMobaPlayerState, KnockbackVector);


}

void ABattleMobaPlayerState::OnRep_InitTimer()
{

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
		ps->RespawnTimeCounter = (int)ps->InitRespawnTime;
		MulticastTimerCount(ps->RespawnTimeCounter);
	}
	else if (ps->RespawnTimeCounter > 0)
	{
		ps->RespawnTimeCounter -= 1;
		MulticastTimerCount(ps->RespawnTimeCounter);
	}
}

bool ABattleMobaPlayerState::CheckKeyInMap(FString str, bool checkValCount, int maxVal)
{
	return UInputLibrary::CheckKeyInTMap(&Skills, str, checkValCount, maxVal);
}

void ABattleMobaPlayerState::AddToMap(FString str)
{
	Skills = *UInputLibrary::AddToTMap(&Skills, str);
}

void ABattleMobaPlayerState::LookUp_Implementation(const FString& str)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("%s"), *str));
	if (Skills.Contains(str))//if the skill is already unlocked and stored in the Skill TMap
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("TRUE")));
		if (GetPawn()->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
		{
			Cast<IBattleMobaInterface>(GetPawn())->Execute_CheckBool(GetPawn(), Skills.Contains(str));//set exist bool in player character to true
		}							
	}
}

void ABattleMobaPlayerState::ActivatePure(float a, float b, float c, float d, float e, float f, float g)
{
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
					if (GetPawn()->IsLocallyControlled())
					{
						ServerSetRespawnTime(Row->RespawnTime);
					}
					/*RespawnTimeCounter = Row->RespawnTime;
					OnRep_Timer();

					InitRespawnTime = RespawnTimeCounter;
					OnRep_InitTimer();*/

					/*Row->SkillUnlock;*/

					if (GetPawn()->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
					{
						Cast<IBattleMobaInterface>(GetPawn())->ActivatePure(MaxHealth, Defense, MoveSpeed, AtkSpeed, StunDuration, KnockbackVector, ImmunityDur);
					}
				}
			}
		}
		
		//return level
		OutLevel = Level;
	}
}

bool ABattleMobaPlayerState::ClientSetRespawnTime_Validate(float time)
{
	return true;
}

void ABattleMobaPlayerState::ClientSetRespawnTime_Implementation(float time)
{
	RespawnTimeCounter = time;
	OnRep_Timer();

	InitRespawnTime = RespawnTimeCounter;
	OnRep_InitTimer();
}

bool ABattleMobaPlayerState::ServerSetRespawnTime_Validate(float time)
{
	return true;
}

void ABattleMobaPlayerState::ServerSetRespawnTime_Implementation(float time)
{
	ClientSetRespawnTime(time);
}
