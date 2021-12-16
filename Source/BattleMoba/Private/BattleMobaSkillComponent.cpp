// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaSkillComponent.h"
#include "Engine.h"
#include "BattleMobaCharacter.h"

// Sets default values for this component's properties
UBattleMobaSkillComponent::UBattleMobaSkillComponent(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	// ...
}


// Called when the game starts
void UBattleMobaSkillComponent::BeginPlay()
{
	Super::BeginPlay();
 
	// ...
	
}

void UBattleMobaSkillComponent::Execute(ABattleMobaCharacter* OwningChar)
{
	//General executing functions
	if (OwningChar != nullptr)
	{
		ExecuteSkill(OwningChar);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Execute")));
	}
}


// Called every frame
void UBattleMobaSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

