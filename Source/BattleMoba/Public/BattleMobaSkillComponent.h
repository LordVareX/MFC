// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleMobaInterface.h"
#include "BattleMobaSkillComponent.generated.h"

class ABattleMobaCharacter;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEMOBA_API UBattleMobaSkillComponent : public UActorComponent, public IBattleMobaInterface
{
	GENERATED_BODY()

protected:
	int SkillLevel = 0;

public:	

	// Sets default values for this component's properties
	UBattleMobaSkillComponent(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Execute")
		void ExecuteSkill(ABattleMobaCharacter* OwningChar);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void ActivatePure(float a, float b, float c, float d, float e, float f, float g) override; //c++ only interface function

	void Execute(ABattleMobaCharacter* OwningChar);
};
