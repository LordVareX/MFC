// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaCTF.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"
#include "Styling/SlateColor.h"

#include "BattleMobaCharacter.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameState.h"
#include "InputLibrary.h"

void ABattleMobaCTF::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaCTF, FlagTimer);
	DOREPLIFETIME(ABattleMobaCTF, ControllerTeam);
	DOREPLIFETIME(ABattleMobaCTF, OverlappedPlayer);
	DOREPLIFETIME(ABattleMobaCTF, RadiantControl);
	DOREPLIFETIME(ABattleMobaCTF, DireControl);
	DOREPLIFETIME(ABattleMobaCTF, isCompleted);
	DOREPLIFETIME(ABattleMobaCTF, GoldTimer);
	DOREPLIFETIME(ABattleMobaCTF, ActivePlayer);
	DOREPLIFETIME(ABattleMobaCTF, valRadiant);
	DOREPLIFETIME(ABattleMobaCTF, valDire);
	DOREPLIFETIME(ABattleMobaCTF, GiveGoldActors);
	DOREPLIFETIME(ABattleMobaCTF, ActorsInVision);
}

// Sets default values
ABattleMobaCTF::ABattleMobaCTF()
{
	/*TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Radius"));
	SetRootComponent(TriggerSphere);
	TriggerSphere->bVisualizeComponent = true;
	TriggerSphere->SetGenerateOverlapEvents(true);

	TriggerSphere->SetSphereRadius(RadiusSize, true);*/

	OnActorBeginOverlap.AddDynamic(this, &ABattleMobaCTF::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ABattleMobaCTF::OnOverlapEnd);

	FogCol = CreateDefaultSubobject<USphereComponent>(TEXT("FogCol"));
	FogCol->SetupAttachment(RootComponent);
	FogCol->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
	FogCol->SetCollisionProfileName("Custom");

	FogCol->OnComponentBeginOverlap.AddDynamic(this, &ABattleMobaCTF::OnComponentOverlapBegin);
	FogCol->OnComponentEndOverlap.AddDynamic(this, &ABattleMobaCTF::OnComponentOverlapEnd);


	MeshFlag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	MeshFlag->SetupAttachment(RootComponent);
	MeshFlag->SetCollisionProfileName("BlockAll");
	MeshFlag->SetGenerateOverlapEvents(false);


	W_ValControl = CreateDefaultSubobject<UWidgetComponent>(TEXT("W_ValControl"));
	W_ValControl->SetupAttachment(RootComponent);
	W_ValControl->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	W_ValControl->InitWidget();
	W_ValControl->SetIsReplicated(true);

	W_ValControl->SetWidgetSpace(EWidgetSpace::Screen);
	W_ValControl->SetDrawAtDesiredSize(true);
	W_ValControl->SetGenerateOverlapEvents(false);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABattleMobaCTF::BeginPlay()
{
	Super::BeginPlay();

	//remove excess character and rename the owning actor in the Level
	[this](FString temp)
	{
		temp = this->GetName();
		for (int i = temp.Len() - 1; i > 0; i--)
		{
			if (i > 9)
			{
				if (temp[i] == '_')
				{
					temp.RemoveAt(i + 1);
					temp.RemoveAt(i);
					UInputLibrary::RenameObject(temp, this);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("CTFName is: %s"), (*this->GetName())));
				}
			}
		}
	};
	
	/////////////////Get flag names that valid in current Level///////////////////////////////
	inst_Fog = GetWorld()->GetParameterCollectionInstance(Mat_Fog);

	if (inst_Fog->GetScalarParameterValue(FName(*this->GetName()), Rad))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("CTFName is: %s"), (*this->GetName())));
		FogCol->SetSphereRadius(Rad, true);
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//		Run TimerFunction every ControllingSpeed after 1 second the game has started
	//this->GetWorldTimerManager().SetTimer(FlagTimer, this, &ABattleMobaCTF::TimerFunction, ControllingSpeed, true, 1.0f);

	//		Find all actors of class ONCE for GoldTimerFunction
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattleMobaCharacter::StaticClass(), GiveGoldActors);

	//		Run GoldTimerFunction every 1 second after 20 seconds the game has started
	this->GetWorldTimerManager().SetTimer(GoldTimer, this, &ABattleMobaCTF::GoldTimerFunction, 1.0f, true, 50.0f);

	//		Init FlagTimer to run on begin play so it will always run until game finishes
	this->GetWorldTimerManager().SetTimer(FlagTimer, this, &ABattleMobaCTF::TimerFunction, ControllingSpeed, false, 30.0f);
}

void ABattleMobaCTF::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set size of widget on vision
	UInputLibrary::SetUIVisibility(W_ValControl, this);
}

void ABattleMobaCTF::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ABattleMobaCharacter* pb = Cast<ABattleMobaCharacter>(OtherActor);
	if (pb != nullptr)
	{
		//		set CTFentering to true to add integer of a team in the sphere
		pb->CTFentering = true;
	}
}

void ABattleMobaCTF::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	ABattleMobaCharacter* pe = Cast<ABattleMobaCharacter>(OtherActor);
	if (pe != nullptr)
	{
		//		set CTFentering to true to deduct integer of a team in the sphere
		pe->CTFentering = false;
	}
}

//For fog visibility
void ABattleMobaCTF::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr)
	{
		ActorsInVision.AddUnique(pChar);
		ServerSetVisibility(this, pChar, ActorsInVision, .0f, true);
	}
}

void ABattleMobaCTF::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr)
	{
		ServerSetVisibility(this, pChar, ActorsInVision, Rad, false);
	}
}

bool ABattleMobaCTF::ServerSetVisibility_Validate(ABattleMobaCTF* owningActor, ABattleMobaCharacter* Actor, const TArray<AActor*>& Actors, float MaxDrawDist, bool Entering)
{
	return true;
}

void ABattleMobaCTF::ServerSetVisibility_Implementation(ABattleMobaCTF* owningActor, ABattleMobaCharacter* Actor, const TArray<AActor*>& Actors, float MaxDrawDist, bool Entering)
{
	MulticastSetVisibility(owningActor, Actor, Actors, MaxDrawDist, Entering);
}

bool ABattleMobaCTF::MulticastSetVisibility_Validate(ABattleMobaCTF* owningActor, ABattleMobaCharacter * Actor, const TArray<AActor*>& Actors, float MaxDrawDist, bool Entering)
{
	return true;
}

void ABattleMobaCTF::MulticastSetVisibility_Implementation(ABattleMobaCTF* owningActor, ABattleMobaCharacter * Actor, const TArray<AActor*>& Actors, float MaxDrawDist, bool Entering)
{
	UInputLibrary::SetActorVisibility(Actor, Actors, MaxDrawDist, Entering, owningActor);
}

void ABattleMobaCTF::OnRep_Val()
{
	UUserWidget* HPWidget = Cast<UUserWidget>(W_ValControl->GetUserWidgetObject());
	if (HPWidget)
	{
		const FName hptext = FName(TEXT("ValText"));
		UTextBlock* HealthText = (UTextBlock*)(HPWidget->WidgetTree->FindWidget(hptext));

		const FName hpbar = FName(TEXT("PBar"));
		UProgressBar* PBar = (UProgressBar*)(HPWidget->WidgetTree->FindWidget(hpbar));

		if (HealthText)
		{
			if (/*this->valDire <= 0 && */this->valRadiant > 0)
			{
				FString TheFloatStr = FString::FromInt((int)this->valRadiant);
				HealthText->SetText(FText::FromString(TheFloatStr));
				PBar->SetPercent(FMath::Clamp(this->valRadiant / 100.0f, 0.0f, 1.0f));
			}

			else if (/*this->valRadiant <= 0 && */this->valDire > 0)
			{
				FString TheFloatStr = FString::FromInt((int)this->valDire);
				HealthText->SetText(FText::FromString(TheFloatStr));
				PBar->SetPercent(FMath::Clamp(this->valDire / 100.0f, 0.0f, 1.0f));
			}
			//else
			//{
			//	FString TheFloatStr = FString::SanitizeFloat(0.0f);
			//	HealthText->SetText(FText::FromString(TheFloatStr));
			//	PBar->SetPercent(FMath::Clamp(0.0f / 100.0f, 0.0f, 1.0f));
			//}


			//HealthBar->SetPercent(FMath::Clamp(this->Health / 100.0f, 0.0f, 1.0f));
		}
	}
}

void ABattleMobaCTF::TimerFunction()
{
	//check overlapping actor in CTF sphere for every controlling speed
	this->GetOverlappingActors(this->OverlappedPlayer, ABattleMobaCharacter::StaticClass());
	int arrLength = this->OverlappedPlayer.Num();

	RadiantControl = 0;
	DireControl = 0;

	for (uint8 i = 0; i < arrLength; ++i)
	{
		ActivePlayer = Cast<ABattleMobaCharacter>(this->OverlappedPlayer[i]);

		if (ActivePlayer)
		{
			if (ActivePlayer->CTFentering == true)
			{
				if (ActivePlayer->TeamName == "Radiant" && this->RadiantControl >= 0)
				{
					this->RadiantControl = this->RadiantControl + 1;
				}

				else if (ActivePlayer->TeamName == "Dire" && this->DireControl >= 0)
				{
					this->DireControl = this->DireControl + 1;
				}
				ActivePlayer->ControlFlagMode(this);
			}

			else if (ActivePlayer->CTFentering == false)
			{
				if (ActivePlayer->TeamName == "Radiant" && this->RadiantControl >= 1)
				{
					this->RadiantControl = this->RadiantControl - 1;
				}

				else if (ActivePlayer->TeamName == "Dire" && this->DireControl >= 1)
				{
					this->DireControl = this->DireControl - 1;
				}
				ActivePlayer->ControlFlagMode(this);
			}
		}
	}
	this->GetWorldTimerManager().SetTimer(FlagTimer, this, &ABattleMobaCTF::TimerFunction, ControllingSpeed, false, ControllingSpeed);
}

void ABattleMobaCTF::GoldTimerFunction()
{
	if (isCompleted)
	{
		/*if (this->GetWorldTimerManager().IsTimerActive(FlagTimer))
		{
			this->GetWorldTimerManager().ClearTimer(FlagTimer);
		}*/

		int arrLength = this->GiveGoldActors.Num();

		//		for every player of the controller team will gain honor/exp or both for every second when the Control Flag progress reaches 100
		for (uint8 i = 0; i < arrLength; ++i)
		{
			ABattleMobaCharacter* player = Cast<ABattleMobaCharacter>(GiveGoldActors[i]);
			if (player != nullptr && player->IsActorBeingDestroyed() == false)
			{
				ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(player->GetPlayerState());
				if (ps->TeamName == ControllerTeam)
				{
					CheckFlagType(this, ps, player);
					//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("PointName %s"), ((*PointName.ToString()))));
				}
			}
		}
	}
}

void ABattleMobaCTF::CheckFlagType(ABattleMobaCTF* currFlag, class ABattleMobaPlayerState* currPs, class ABattleMobaCharacter* currPlayer)
{
	if (currFlag->FlagType == EFlagType::Base || currFlag->FlagType == EFlagType::Major)
	{
		currPs->Honor += currFlag->HonorVal;
		if (currFlag->FlagType == EFlagType::Major)
		{
			if (currPlayer->IsLocallyControlled())
			{
				currPs->ServerSetExp(currFlag->ExpVal);
			}
		}
	}
	else if (currFlag->FlagType == EFlagType::Minor)
	{
		if (currFlag->FlagPerks == EPerksType::Honor)
		{
			currPs->Honor += currFlag->HonorVal;
		}
		else if (currFlag->FlagPerks == EPerksType::Experience)
		{
			if (currPlayer->IsLocallyControlled())
			{
				currPs->ServerSetExp(currFlag->ExpVal);
			}
		}
	}
}




