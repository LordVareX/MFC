// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEMOBA_API UCharMovementComp : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
		UCharMovementComp(const FObjectInitializer& ObjectInitializer);

	virtual void PhysFalling(float deltaTime, int32 Iterations) override;

};
