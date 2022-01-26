// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaPC.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Camera/PlayerCameraManager.h"

//BattleMoba
#include "InputLibrary.h"
#include "BattleMobaGameMode.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameState.h"
#include "BattleMobaCharacter.h"
#include "ItemInterface.h"

ABattleMobaPC::ABattleMobaPC()
{
	//SetInputMode(FInputModeUIOnly());
}

void ABattleMobaPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaPC, pi);
}

void ABattleMobaPC::BeginPlay()
{
	Super::BeginPlay();
}

void ABattleMobaPC::AddItem(FName ItemID)
{
	if (EquipmentArtifacts.Contains(ItemID))
	{
		FItem item = *EquipmentArtifacts.Find(ItemID);
		item.Quantity += 1;
		
		EquipmentArtifacts.Remove(ItemID);
		EquipmentArtifacts.Add(ItemID, item);

		UE_LOG(LogTemp, Warning, TEXT("[Player:AddItem] picked %s - Quantity: %d "), *ItemID.ToString(), item.Quantity);

		OnRefreshInventory();
		return;
	}
	if (EquipmentArtifacts.Num() == TotalEquipmentSlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Player:AddItem] Equipment Full: %d/%d "), EquipmentArtifacts.Num()/TotalEquipmentSlots);
		return;
	}

	//Find the item in the table on the game mode to get the information
	GM = Cast<ABattleMobaGameMode>(GetWorld()->GetAuthGameMode());
	if (GM != nullptr)
	{
		bool Found = false;
		FItem ItemFound = GM->FindItem(ItemID, Found);

		if (Found)
		{
			FItem NewItem;
			NewItem.ItemID = ItemID;
			NewItem.Name = ItemFound.Name;
			NewItem.Description = ItemFound.Description;
			NewItem.Quantity = 1;
			NewItem.IsActive = ItemFound.IsActive;
			NewItem.ItemIcon = ItemFound.ItemIcon;
			NewItem.ItemEffects = ItemFound.ItemEffects;
			
			EquipmentArtifacts.Add(NewItem.ItemID, NewItem);
		}
	}
	OnRefreshInventory();
}

void ABattleMobaPC::RemoveItem(FName ItemID, bool RemovedFromInventory)
{
	if (EquipmentArtifacts.Contains(ItemID))
	{
		EquipmentArtifacts.Remove(ItemID);
		OnRefreshInventory();
		RemovedFromInventory = true;
		return;
	}
}

bool ABattleMobaPC::HasFreeInventorySlots()
{
	return (EquipmentArtifacts.Num() < TotalEquipmentSlots);
}

FName ABattleMobaPC::GetName()
{
	return FName();
}

void ABattleMobaPC::OnInteract_Implementation()
{

}

bool ABattleMobaPC::SetupPawnAttribute_Validate()
{
	return true;
}

void ABattleMobaPC::SetupPawnAttribute_Implementation()
{
	ABattleMobaCharacter* pawn = Cast<ABattleMobaCharacter>(GetPawn());
	if (pawn)
	{
		/*pawn->MainWidget = MainWidget;*/
		pawn->EnableInput(this);
		pawn->RefreshPlayerData();
	}
}

void ABattleMobaPC::Action()
{
	/*if (Character != nullptr)
	{
		Character->Execute_Item();
	}*/
}

int32 ABattleMobaPC::CheckIndexValidity(int32 index, TArray<ABattleMobaPC*> PlayerList, EFormula SwitchMode)
{
	if (SwitchMode == EFormula::Addition)
	{
		//select the index number forward
		int32 temp = index + 1;
		if (PlayerList.Num() == temp)
		{
			return 0;
		}
		else
			return temp;
	}
	else
	{
		//select the index number backwards
		int32 temp = index - 1;
		if (temp == -1)
		{
			return PlayerList.Num() - 1;
		}
		else
			return temp;
	}


}

bool ABattleMobaPC::ClientSetInputMode_Validate()
{
	return true;
}

void ABattleMobaPC::ClientSetInputMode_Implementation()
{
	if (this->IsLocalPlayerController() && this->GetNetMode() != ENetMode::NM_DedicatedServer)
	{
		//this->bShowMouseCursor = true;
		this->SetInputMode(FInputModeGameAndUI());
	}
}

bool ABattleMobaPC::SpectateNextPlayer_Validate(const TArray<ABattleMobaPC*>& PlayerList, EFormula SwitchMode)
{
	return true;
}

void ABattleMobaPC::SpectateNextPlayer_Implementation(const TArray<ABattleMobaPC*>& PlayerList, EFormula SwitchMode)
{

	bool x = false;
	int32 count = 0;

	//get playerstate
	ABattleMobaPlayerState* thisps = Cast<ABattleMobaPlayerState>(this->PlayerState);

	for (int32 i = 0; i < PlayerList.Num(); i++)
	{
		if (PlayerList[i]->GetPawn() != nullptr)
		{
			ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(PlayerList[i]->PlayerState);
			if (ps->TeamName == thisps->TeamName)
			{
				count += 1;
				if (count > 0)
				{
					x = true;
					break;
				}
			}
		}
	}

	//Is eligible to spectate??
	if (x == true)
	{
	loop:
		currentPlayer = CheckIndexValidity(currentPlayer, PlayerList, SwitchMode); //check if next spectated player is exist in an array

		if (PlayerList[currentPlayer]->GetPawn() != nullptr) //checks if player does have a pawn
		{
			if (PlayerList[currentPlayer]->GetPawn() != this->GetPawn()) //checks if spectated pawn is not current owning pawn
			{
				ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(PlayerList[currentPlayer]->PlayerState);
				if (ps->TeamName == thisps->TeamName) //spectating only team pawn
				{
					this->SetViewTargetWithBlend(PlayerList[currentPlayer], 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
					CurrSpectator = PlayerList[currentPlayer];//set new spectated player
					CurrSpectator->SpectPI = this->pi;
					return;
				}
				else
					goto loop;
			}
			else
				goto loop;
		}
		else
			goto loop;
	}
}

bool ABattleMobaPC::SetupSpectator_Validate(EFormula SwitchMode)
{
	return true;
}

void ABattleMobaPC::SetupSpectator_Implementation(EFormula SwitchMode)
{
	if (this->GetPawn() == nullptr) // make sure no owning pawn present before spectating
	{
		GM = Cast<ABattleMobaGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			SpectateNextPlayer(GM->Players, SwitchMode);
		}
	}
}

bool ABattleMobaPC::RespawnPawn_Validate(FTransform SpawnTransform)
{
	return true;
}

void ABattleMobaPC::RespawnPawn_Implementation(FTransform SpawnTransform)
{
	GM = Cast<ABattleMobaGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		//Destroy pawn before respawning
		if (this->GetPawn())
		{
			this->GetPawn()->Destroy();
		}

		FTimerHandle handle;
		FTimerDelegate TimerDelegate;

		//set view target
		TimerDelegate.BindLambda([this]()
		{
			//Assigned initial spectator player before swapping to active pawn player to spectate
			currentPlayer = GM->Players.Find(this);
			CurrSpectator = GM->Players[currentPlayer];
			CurrSpectator->SpectPI = this->pi;

			this->SpectateNextPlayer(GM->Players, EFormula::Addition);

			//Setup spectator controller that currently spectating this player to switch to another player
			ABattleMobaPC* newPC = Cast<ABattleMobaPC>(UGameplayStatics::GetPlayerController(GetWorld(), CurrSpectator->SpectPI));
			if (newPC)
			{
				if (newPC->GetPawn() == nullptr)
				{
					newPC->currentPlayer = GM->Players.Find(newPC);
					newPC->CurrSpectator = GM->Players[currentPlayer];
					newPC->CurrSpectator->SpectPI = newPC->pi;

					newPC->SpectateNextPlayer(GM->Players, EFormula::Addition);
				}
			}

		});
		this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 0.02f, false);

		//get current controller playerstate
		ABattleMobaPlayerState* thisstate = Cast<ABattleMobaPlayerState>(this->PlayerState);

		float temp = thisstate->InitRespawnTime - 3.0f;

		//Delay before respawning a new pawn
		FTimerHandle handle1;
		FTimerDelegate TimerDelegate1;

		//Possess a pawn
		TimerDelegate1.BindLambda([this, thisstate]()
		{
			PlayerCameraManager->BlendTimeToGo = 0.0f;
			GM->RespawnRequested(this, thisstate->SpawnTransform);
		});
		this->GetWorldTimerManager().SetTimer(handle1, TimerDelegate1, temp, false);
	}
}