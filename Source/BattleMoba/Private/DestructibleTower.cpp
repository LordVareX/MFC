// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleTower.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "BattleMobaGameState.h"
#include "BattleMobaGameMode.h"
#include "BattleMobaCharacter.h"
#include "TextReaderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "InputLibrary.h"

void ADestructibleTower::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADestructibleTower, CurrentHealth);
	DOREPLIFETIME(ADestructibleTower, TeamName);
	DOREPLIFETIME(ADestructibleTower, IsHit);
	DOREPLIFETIME(ADestructibleTower, isDestroyed);
	DOREPLIFETIME(ADestructibleTower, ActorsInVision);
	DOREPLIFETIME(ADestructibleTower, IsOverlapFog);
}

// Sets default values
ADestructibleTower::ADestructibleTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	/*DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	DestructibleComponent->SetupAttachment(RootComponent);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);*/

	TriggerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(RootComponent);

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(RootComponent);
	TowerMesh->SetCollisionProfileName("BlockAll");

	Material1 = CreateDefaultSubobject<UMaterialInterface>("Material1");

	//Fog col init
	FogCol = CreateDefaultSubobject<USphereComponent>(TEXT("FogCol"));
	FogCol->SetupAttachment(RootComponent);
	FogCol->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
	FogCol->SetCollisionProfileName("Custom");

	FogCol->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleTower::OnComponentOverlapBegin);
	FogCol->OnComponentEndOverlap.AddDynamic(this, &ADestructibleTower::OnComponentOverlapEnd);
	

	isDestroyed = false;
	isTriggerEnabled = false;

	MaxHealth = 5000.0f;
	DamageValue = 40.0f;
	ImpulseValue = 50.0f;
	CurrentHealth = MaxHealth;

	W_Health = CreateDefaultSubobject<UWidgetComponent>(TEXT("W_Health"));
	W_Health->SetupAttachment(RootComponent);
	//W_Health->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	W_Health->InitWidget();

	W_Health->SetWidgetSpace(EWidgetSpace::Screen);
	W_Health->SetDrawAtDesiredSize(true);
	W_Health->SetGenerateOverlapEvents(false);


}

void ADestructibleTower::OnRep_UpdateHealth()
{
	if (W_DisplayHealth)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Player %s with %s Widget"), *GetDebugName(this), *W_DisplayHealth->GetFName().ToString()));
		const FName hptext = FName(TEXT("HealthText"));
		UTextBlock* HealthText = (UTextBlock*)(W_DisplayHealth->WidgetTree->FindWidget(hptext));

		const FName hpbar = FName(TEXT("HPBar"));
		UProgressBar* PBar = (UProgressBar*)(W_DisplayHealth->WidgetTree->FindWidget(hpbar));

		if (HealthText)
		{
			FString TheFloatStr = FString::FromInt((int)this->CurrentHealth);

			HealthText->SetText(FText::FromString(TheFloatStr));

			if (PBar)
			{
				PBar->SetPercent(FMath::Clamp(this->CurrentHealth / this->MaxHealth, 0.0f, 1.0f));
			}
		}
	}
}

void ADestructibleTower::OnRep_Destroy()
{
	if (Material1 != nullptr)
	{
		TowerMesh->SetMaterial(0, Material1);
	}

	if (GameState != nullptr && GameMode != nullptr)
	{
		GameState->LatestEvent = "GameEnded";
		/**		Clear timer from Game Mode*/
		GetWorldTimerManager().ClearTimer(GameMode->ClockTimer);
		
		if (this->isDestroyed && this->TeamName == "Radiant")
		{
			GameState->Winner = "Dire";
			GameMode->MatchResult("Dire");
		}

		else if (this->isDestroyed && this->TeamName == "Dire")
		{
			GameState->Winner = "Radiant";
			GameMode->MatchResult("Radiant");
		}
	}
	
	
	//if (DynamicMaterial)
	//{
	//	/*float blend = 0.5f + FMath::Cos(GetWorld()->TimeSeconds) / 2;
	//	DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), blend);*/
	//	//Constant3Vector
	//	DynamicMaterial->SetVectorParameterValue(TEXT("Colour"), FLinearColor::Yellow);
	//	
	//}
	
}

void ADestructibleTower::OnRep_Team()
{
	if (W_DisplayHealth)
	{
		const FName hptext = FName(TEXT("TeamName"));
		UTextBlock* HealthText = (UTextBlock*)(W_DisplayHealth->WidgetTree->FindWidget(hptext));

		if (HealthText)
		{
			HealthText->SetText(FText::FromName(TeamName));
		}
	}
}

// Called when the game starts or when spawned
void ADestructibleTower::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	W_DisplayHealth = Cast<UUserWidget>(W_Health->GetUserWidgetObject());

	GameState = Cast<ABattleMobaGameState>(GetWorld()->GetGameState());

	GameMode = Cast<ABattleMobaGameMode>(GetWorld()->GetAuthGameMode());

	/*if (GameState)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("GameState is %s"), *GameState->GetName()));
	}*/
	
	/*auto Material = TowerMesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	TowerMesh->SetMaterial(0, DynamicMaterial);
	DynamicMaterial->SetVectorParameterValue(TEXT("Colour"), FLinearColor::Red);*/

	/////////////////Get flag names that valid in current Level///////////////////////////////
	inst_Fog = GetWorld()->GetParameterCollectionInstance(Mat_Fog);

	if (inst_Fog->GetScalarParameterValue("Tower0Location", Rad))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Tower Name is: %s"), (*this->GetName())));
		FogCol->SetSphereRadius(Rad, true);
	}
}


float ADestructibleTower::TakeDamage(float value, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{	
	return 0.0f;
}

void ADestructibleTower::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr)
	{
		ServerSetVisibility(this, pChar, .0f, true);
	}
}

void ADestructibleTower::OnComponentOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr)
	{
		ServerSetVisibility(this, pChar, Rad, false);
	}
}

bool ADestructibleTower::ServerSetVisibility_Validate(ADestructibleTower * owningActor, ABattleMobaCharacter * Actor, float MaxDrawDist, bool Entering)
{
	return true;
}

void ADestructibleTower::ServerSetVisibility_Implementation(ADestructibleTower * owningActor, ABattleMobaCharacter * Actor, float MaxDrawDist, bool Entering)
{
	MulticastSetVisibility(owningActor, Actor, MaxDrawDist, Entering);
}

bool ADestructibleTower::MulticastSetVisibility_Validate(ADestructibleTower * owningActor, ABattleMobaCharacter * Actor, float MaxDrawDist, bool Entering)
{
	return true;
}

void ADestructibleTower::MulticastSetVisibility_Implementation(ADestructibleTower * owningActor, ABattleMobaCharacter * Actor, float MaxDrawDist, bool Entering)
{
	ActorsInVision.AddUnique(Actor);
	UInputLibrary::SetActorVisibility(Actor, ActorsInVision, MaxDrawDist, Entering, owningActor);
}


// Called every frame
void ADestructibleTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set size of widget on vision
	UInputLibrary::SetUIVisibility(W_Health, this);

	FogCol->GetOverlappingActors(ActorsInVision, ABattleMobaCharacter::StaticClass());
	if (!ActorsInVision.IsValidIndex(0))
	{
		IsOverlapFog = false;
	}
}


