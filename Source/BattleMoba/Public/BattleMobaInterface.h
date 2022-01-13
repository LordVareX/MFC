#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleMobaInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UBattleMobaInterface : public UInterface
{
	GENERATED_BODY()
};

class IBattleMobaInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
		void OnActivate();

	UFUNCTION()
		virtual void ActivatePure(float a, float b) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
		void LookUp(const FString& str);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
		void CheckBool(bool check);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
		void CheckStringWithFloat(const FString& str, const float& Float, bool check);
};

