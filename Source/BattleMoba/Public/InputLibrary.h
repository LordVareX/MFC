// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputLibrary.generated.h"

class UWidgetComponent;
class UBattleMobaSkillComponent;

//For logging purposes
#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

//Input Touch Type
UENUM(BlueprintType)
enum class EInputType : uint8
{
	Pressed,
	Released,
	Hold
};

//Style Type
UENUM(BlueprintType)
enum class EStyle : uint8
{
	Boxing,
	Silat,
	Shaolin
};

UENUM(BlueprintType)
enum class EFormula : uint8
{
	Addition,
	Subtraction
};

UENUM(BlueprintType)
enum class EResult : uint8
{
	Cooldown,
	Translate,
	Section
};

USTRUCT(BlueprintType)
struct FLevelAttributes :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		int Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exp")
		int MaxExpPerLevel = 0;
};

USTRUCT(BlueprintType)
struct FRewards :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyLevel")
		int EnemyLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exp")
		int ExpKills = 0;
};

USTRUCT(BlueprintType)
struct FActionSkill : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
		bool isOnCD = false;

	//If cooldown mechanic is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
		bool IsUsingCD = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown", meta = (EditCondition = "IsUsingCD"))
		float CDDuration = 0.0f;

	//If translation mechanic is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Translate Player")
		bool UseTranslate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Translate Player", meta = (EditCondition = "UseTranslate"))
		float TranslateDist;

	//If cooldown mechanic is applied
	//If combo mechanic is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UseSection")
		bool UseSection = false;

	//How many sections are used in this montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section", meta = (EditCondition = "UseSection"))
		int Section = 0;

	//Get key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FKey keys;

	//Get button name for mobile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FString ButtonName;

	//Anim to be played on key pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		UAnimMontage* SkillMoveset;

	//Damage to be dealt from the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		int MinDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		int MaxDamage = 0;

	//Knockback vector on stun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffect")
		float StunImpulse = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffect")
		float StunTime = 0.0f;

	//Anim to be played on special attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		UAnimMontage* HitMoveset;

	//For array comparison
	bool operator ==(const FActionSkill &other) const
	{
		if (keys == other.keys)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Key %s is %s and %s type is %s and DetectInputOnPressed is %s"), *KeyInput.ToString(), (KeyInput == other.KeyInput)? TEXT("True"): TEXT("False"), *GETENUMSTRING("EInputType", InputType), (InputType == other.InputType) ? TEXT("True") : TEXT("False"), (DetectInputOnPressed == other.DetectInputOnPressed) ? TEXT("True") : TEXT("False"));
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Key input is %s and Input type is %s and DetectInputOnPressed is %s"), (KeyInput == other.KeyInput) ? TEXT("True") : TEXT("False"), (InputType == other.InputType) ? TEXT("True") : TEXT("False"), (DetectInputOnPressed == other.DetectInputOnPressed) ? TEXT("True") : TEXT("False")));

			return true;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Key %s is %s and %s type is %s"), *KeyInput.ToString(), (KeyInput == other.KeyInput) ? TEXT("True") : TEXT("False"), *GETENUMSTRING("EInputType", InputType), (InputType == other.InputType) ? TEXT("True") : TEXT("False"));
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Key input is %s and Input type is %s"), (KeyInput == other.KeyInput) ? TEXT("True") : TEXT("False"), (InputType == other.InputType) ? TEXT("True") : TEXT("False")));
			return false;
		}
	}
};

USTRUCT(BlueprintType)      // Define custom struct and expose to blueprints
struct FActor_Dist          // This will be the name of the new struct in BPs 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Distance")    // allow this property to be edited in BPs
		float distance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Distance")    // allow this property to be edited in BPs
		AActor* actor = NULL;

};

UCLASS()
class BATTLEMOBA_API UInputLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//
	//	UFUNCTION(BlueprintPure, Category = "Rotation")
	//	static FRotator LookRotation(FVector lookAt, FVector upDirection);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		static void RenameObject(FString name, UObject* object);

	UFUNCTION(BlueprintCallable, Category = "DateAndTime")
		static FDateTime GetCurrentDateAndTime();

	UFUNCTION(BlueprintCallable, Category = "DateAndTime")
		static float GetCurrentTimeInMinute();

	UFUNCTION(BlueprintCallable, Category = "DateAndTime")
		static FTimespan GetCurrentTime();

	UFUNCTION(BlueprintPure, Category = "DateAndTime")
		static FString DisplayMinutesSecondsFormat(float Seconds);

	UFUNCTION(BlueprintCallable, Category = "Sorting Functions")    // Sort actors by distance from target actor    
		static void  Distance_Sort(UPARAM() TArray <AActor*> Array_To_Sort, UPARAM()AActor* From_Actor, bool Descending, TArray <FActor_Dist> &Sorted_Array);

	UFUNCTION(BlueprintCallable, Category = "Displays") //Hide 3D widget behind building etc
		static void SetUIVisibility(UWidgetComponent* widget, AActor* FromActor);

	UFUNCTION(BlueprintPure, Category = "Math|Gesture Utils")
		static void AbsoluteValueOfTwoVectors(FVector2D StartValue, FVector2D EndValue, float & x, float & y, float & AbsX, float & AbsY);

	//Check if current point is on the left side of the screen
	static bool PointOnLeftHalfOfScreen(FVector2D Point);

	//Detect linear swipe
	static bool DetectLinearSwipe(FVector2D Line1Start, FVector2D Line1End, EInputType& Branches, bool Dos);

	//Adds a UActorComponent Subclass, and adds it to the Outer Actor.
	UFUNCTION(BlueprintPure, Category = "ActorComponent")
		static UBattleMobaSkillComponent* AddComponentByClass(TSubclassOf<UBattleMobaSkillComponent> Class, AActor* Outer);

	//Calculate player rewards
		static bool CalculateRewards(int OriginalHonor, int PlayersCount, FRewards* row, FName RowName, int& HonorVal, int& ExpOut);
};