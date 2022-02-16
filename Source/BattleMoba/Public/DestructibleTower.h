// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleTower.generated.h"

UCLASS()
class BATTLEMOBA_API ADestructibleTower : public AActor
{
	GENERATED_BODY()

		//Replicated Network setup
		void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* FogCol;

private:
	float Rad = 0.0f;

	//Get radius of visible area from sphere mask radius
	UMaterialParameterCollectionInstance* inst_Fog;

public:
	// Sets default values for this actor's properties
	ADestructibleTower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Fog")
		bool IsOverlapFog = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
		class USceneComponent* TriggerComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
		class UDestructibleComponent* DestructibleComponent;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* W_Health;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TowerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
		float DamageValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
		float ImpulseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
		class UUserWidget* W_DisplayHealth;

	UPROPERTY(EditAnywhere, Category = Materials)
		class UMaterialInterface* Material1;

	UPROPERTY(BlueprintReadOnly, Category = UI)
		class ABattleMobaGameState* GameState;

	UPROPERTY(BlueprintReadOnly, Category = UI)
		class ABattleMobaGameMode* GameMode;

	//Get overlapping actors from within FogCol
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "FogActors")
		TArray<AActor*> ActorsInVision;

	//Material Parameter Collection asset
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UMaterialParameterCollection* Mat_Fog;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
		bool isTriggerEnabled;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Destroy, BlueprintReadOnly, Category = Destructible)
		bool isDestroyed;

	UFUNCTION()
		void OnRep_Destroy();

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = Destructible)
		bool IsHit;

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Team, BlueprintReadOnly, Category = Destructible, Meta = (ExposeOnSpawn = "true"))
		FName TeamName;

	UFUNCTION()
		void OnRep_Team();

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_UpdateHealth, BlueprintReadOnly, Category = Destructible)
		float CurrentHealth;

	UFUNCTION()
		void OnRep_UpdateHealth();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstanceDynamic* DynamicMaterial;

protected:

	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(float value, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//Fog area overlap begin function
	UFUNCTION()
		void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Fog area overlap end function
	UFUNCTION()
		void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Call out server to set visibility status of overlapping actor/s
	UFUNCTION(Reliable, Server, WithValidation, Category = "VisibleOnFog")
		void ServerSetVisibility(ADestructibleTower* owningActor, class ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "VisibleOnFog")
		void MulticastSetVisibility(ADestructibleTower* owningActor, class ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering);

};
