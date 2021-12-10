// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleMobaSkillComponent.generated.h"

class ABattleMobaCharacter;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEMOBA_API UBattleMobaSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UBattleMobaSkillComponent(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Execute")
		void ExecuteSkill();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

	void Execute(ABattleMobaCharacter* OwningChar);
};
