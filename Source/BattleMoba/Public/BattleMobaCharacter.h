// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h" 
#include "InputLibrary.h"
#include "GameFramework/Character.h"
#include "BattleMobaAnimInstance.h"
#include "BattleMobaInterface.h"
#include "BattleMobaCharacter.generated.h"

class ABMobaTriggerCapsule;
struct FTimerHandle;
class ABattleMobaCTF;

UCLASS(config = Game)
class ABattleMobaCharacter : public ACharacter, public IBattleMobaInterface
{
	GENERATED_BODY()

		//Replicated Network setup
		void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* BaseArrow;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	//Outline
	//Setting up character mesh for player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Outline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftKickCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LKC6;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightKickCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RKC6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* LKickArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* RKickArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftPunchCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LPC6;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightPunchCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RPC6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* LPunchArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* RPunchArrow;

	////3D UI On Player's head
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* W_DamageOutput;

	private:
		bool IsExist = false;

public:
	ABattleMobaCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LevelUp")
		bool IsUpgradingSkill = false;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY()
		float YawRate = 0.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Status", Meta = (ExposeOnSpawn = "true"))
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Team, BlueprintReadWrite, Category = "Status", Meta = (ExposeOnSpawn = "true"))
		FName TeamName;

	//Setting up character mesh for player
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Status", Meta = (ExposeOnSpawn = "true"))
		USkeletalMesh* CharMesh;

	UFUNCTION()
		void OnRep_Team();

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Status")
		TArray<class ABattleMobaPlayerState*> DamageDealers;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "ControlFlag")
		bool CTFentering;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ControlFlag")
		TArray<AActor*> ActorsToGetGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkillComponents")
		TArray<UBattleMobaSkillComponent*> SkillComponents;


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Input call camera shake */
	void OnCameraShake();

	void OnHRMontageEnd(UAnimMontage* animMontage, bool bInterrupted);
	

protected:

	//rain checks on action skills to be executed
	bool ActionEnabled = true;

	//Init Swipe mechanics
	bool IsPressed = false;

	//SwipeToRotate
	bool StartRotate = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD", Meta = (ExposeOnSpawn = "true"))
		UUserWidget* MainWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
		bool InitRotateToggle = false;

	FVector2D TouchStart;

	FVector2D TouchEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		float TraceDistance = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
		int OrbsAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float BaseDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		int MinDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		int MaxDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float ActualDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float BuffDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Defence = 110.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float BuffDefence = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float ReducedDefence = 0.0f;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ActionSkill")
		UAnimMontage* CounterMoveset;

	//Assign actionskill data table from bp 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* ActionTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HitReaction")
		UAnimMontage* HitReactionMoveset;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "HitReaction")
		UAnimMontage* FrontHitMoveset;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "HitReaction")
		UAnimMontage* BackHitMoveset;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "HitReaction")
		UAnimMontage* RightHitMoveset;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "HitReaction")
		UAnimMontage* LeftHitMoveset;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		float StunDuration;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		float StunImpulse;

	//TimerHandle for removing damage dealer array
	FTimerHandle DealerTimer;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Status")
		bool IsHit;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		bool IsStunned = false;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "HitReaction")
		bool OnSpecialAttack = false;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		bool IsImmuned = false;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		float ImmunityDur = 0.0f;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ActionSkill")
		FName ActionSkillName = "";

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Anim")
		bool InRagdoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
		bool DoOnce = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Rotate")
		bool Rotate = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Rotate")
		AActor* currentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotate")
		bool test = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		bool WithinVicinity = false;

	UPROPERTY(BlueprintReadOnly, Category = "Rotate")
		TArray<AActor*> FoundActors;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "HitReaction")
		FVector AttackerLocation;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "HitReaction")
		FVector HitLocation;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "HitReaction")
		FName BoneName = "pelvis";

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, BlueprintReadWrite, Category = "Status")
		float Health;

	UFUNCTION()
		void OnRep_Health();

	UPROPERTY(EditDefaultsOnly, Replicated, BlueprintReadWrite, Category = "Status")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Replicated, BlueprintReadWrite, Category = "Status")
		float Defense;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Status")
		float Stamina;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "ActionSkill")
		FName AttackSection = "NormalAttack01";

	UPROPERTY(EditAnywhere, Category = "ActionSkill")
		float comboInterval = 1.0f;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ActionSkill")
		int comboCount = 0;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "ActionSkill")
		bool OnComboDelay = false;

	UPROPERTY(VisibleAnywhere, Category = "ActionSkill")
		int slumberCount = 0;

	//*********************Knockout and Respawn***********************************//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Respawn")
		FTimerHandle RespawnTimer;

	UPROPERTY(VisibleAnywhere, Category = "Anim")
		class UBattleMobaAnimInstance* AnimInsta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HitReaction")
		FName ActiveSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "ControlFlag")
		FName CTFteam = "";

	UPROPERTY(EditAnywhere, Category = "Rotate")
		float RotateRadius = 100.0f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Rotate")
		class AActor* closestActor;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Rotate")
		class AActor* damagedActor;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Rotate")
		class ABattleMobaCharacter* RotateToActor;

	UPROPERTY()
		TArray<class ABattleMobaCTF*> Towers;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		TArray<class UBoxComponent*> ActiveColliders;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "HitReaction")
		TArray<class AActor*> ArrDamagedEnemy;

	TEnumAsByte<ETouchIndex::Type> MoveTouchIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<ETouchIndex::Type> RotTouchIndex;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = "Status")
		class UBattleMobaSkillComponent* SkillComp;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController * NewController) override;

	virtual void BeginPlay() override;
	// End of APawn interface

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	void AddSwipeVectorToMovementInput();

	void AddSwipeVectorToRotationInput();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(Reliable, Server, WithValidation, Category = "Movement")
		void ServerSetBlendspace(ABattleMobaPlayerState* PS);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "Movement")
		void MultiSetBlendspace(ABattleMobaPlayerState* PS);

	UFUNCTION(Reliable, Server, WithValidation, Category = "Movement")
	void ServerSetMaxWalkSpeed(float Val);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FinishSetupBeginPlay();

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = Type))
		void CheckSwipeType(EInputType Type, FVector2D Location, TEnumAsByte<ETouchIndex::Type> TouchIndex);

	UFUNCTION(Reliable, Server, WithValidation, Category = "Transformation")
		void ServerRotateToCameraView(FRotator InRot);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "Transformation")
		void RotateToCameraView(FRotator InRot);

	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void Setup3DWidgetVisibility();

	UFUNCTION(BlueprintCallable, Category = "HUDSetup")
		void SetupWidget();

	UFUNCTION(BlueprintCallable, Category = "HUDSetup")
		void HideHPBar();

	//		Attack line traces from active colliders
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void AttackTrace(bool traceStart, int activeAttack, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound);

	//		Result of hit line traces
	UFUNCTION(Reliable, Server, WithValidation, Category = "HitReaction")
		void HitResult(FHitResult hit, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound);

	//		Attack sphere trace for area of damage
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void SpecialAttackTrace(FVector BoxSize, UParticleSystem* ImpactEffect, FName DamageSocket, FName ParticleSocket, USoundBase* HitSound);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void ServerPlayEffects(UParticleSystem* ImpactEffect, FName ParticleSocket, USoundBase* HitSound);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "HitReaction")
		void PlayEffectsClient(UParticleSystem* ImpactEffect, FName ParticleSocket, USoundBase* HitSound);
	
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void DoDamage(AActor* HitActor);

	UFUNCTION(Reliable, Server, WithValidation, Category = "ReceiveDamage")
		void HitReactionServer(AActor* HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackVector, bool isKnockback);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "ReceiveDamage")
		void HitReactionClient(AActor* HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackVector, bool isKnockback);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void ServerRotateHitActor(AActor* HitActor, AActor* Attacker);

	UFUNCTION(Reliable, NetMulticast, WithValidation, BlueprintCallable, Category = "HitReaction")
		void MulticastRotateHitActor(AActor* HitActor, AActor* Attacker);

	UFUNCTION()
		void ClearDamageDealers();

	//Skill sent to server
	UFUNCTION(Reliable, Server, WithValidation, Category = "ActionSkill")
		void ServerExecuteAction(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack);

	//Skill replicate on all client
	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "ActionSkill")
		void MulticastExecuteAction(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "HitReaction")
		void CheckDamage(UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound);

	UFUNCTION(Reliable, Server, WithValidation, Category = "ActionSkill")
		void ServerLaunchChar(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "ActionSkill")
		void MulticastLaunchChar(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);

	UFUNCTION(Reliable, Server, WithValidation, Category = "ActionSkill")
		void ServerPlayMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "ActionSkill")
		void MulticastPlayMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName);

	//Get skills from input touch combo
	UFUNCTION(BlueprintCallable, Category = "ActionSkill")
		void AttackCombo(FActionSkill SelectedRow);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, Category = "ActionSkill")
		void ServerCounterAttack(ABattleMobaCharacter* hitActor);

	UFUNCTION(Reliable, NetMulticast, WithValidation, Category = "ActionSkill")
		void MulticastCounterAttack(ABattleMobaCharacter* hitActor);

	//*********************Knockout and Respawn***********************************//
	UFUNCTION(Reliable, Client, WithValidation, Category = "Knockout")
		void RespawnCharacter();

	//Resets Movement Mode
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void EnableMovementMode();

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = "BaseStats")//HP, Damage, Defense
		void SetupBaseStats(float HealthMax, float Def);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSetupStats();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
		void SetupStats();

	UFUNCTION(Server, Reliable, WithValidation)
		void ControlFlagServer(ABattleMobaCTF* cf);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void ControlFlagMulticast(ABattleMobaCTF* cf, FName Team);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable, meta = (ExpandEnumAsExecs = Type), Category = "ActionSkill")
		void DetectNearestTarget(EResult Type, FActionSkill SelectedRow);

	UFUNCTION(Reliable, NetMulticast, WithValidation, BlueprintCallable, Category = "ActionSkill")
		void RotateNearestTarget(AActor* Target, EResult Type, FActionSkill SelectedRow);

	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
		void CombatCamShake();

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerEnableMovement(ABattleMobaCharacter* player, bool allowMove);

	UFUNCTION(Reliable, NetMulticast, WithValidation)
		void MulticastEnableMovement(ABattleMobaCharacter* player, bool allowMove);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerToggleStun(ABattleMobaCharacter* player, bool bStun);

	UFUNCTION(Reliable, NetMulticast, WithValidation)
		void MulticastToggleStun(ABattleMobaCharacter* player, bool bStun);

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = "ActionSkill")
		void MulticastSetComboInterval(float val);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerToggleImmunity(ABattleMobaCharacter* player, bool bImmune);

	UFUNCTION(Reliable, NetMulticast, WithValidation)
		void MulticastToggleImmunity(ABattleMobaCharacter* player, bool bImmune);


public:

	/*******************Interfaces***********************/
	virtual void Activate_Implementation(); // include a blueprint function
	virtual void ActivatePure(float a, float b) override; //c++ only function

	virtual void CheckBool_Implementation(bool check);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void UpdateHUD();

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void CreateCPHUD();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void RefreshPlayerData();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void ServerSetupBaseStats(float HealthMax, float Def);

	UFUNCTION(Reliable, NetMulticast, WithValidation, BlueprintCallable, Category = "ReceiveDamage")
		void TowerReceiveDamage(ADestructibleTower* Tower, float DamageApply);

	/*******************SAFEZONE*****************************************/

	void SafeZone(ABMobaTriggerCapsule* TriggerZone);

	UFUNCTION(Server, Reliable, WithValidation)
		void SafeZoneServer(ABMobaTriggerCapsule* TriggerZone);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void SafeZoneMulticast(ABMobaTriggerCapsule* TriggerZone);

	/***********************CONTROL FLAG MODE*****************************/
	void ControlFlagMode(ABattleMobaCTF* cf);

	//Get skills from input touch combo
	UFUNCTION(BlueprintCallable, Category = "ActionSkill")
	void GetButtonSkillAction(FKey Currkeys, FString ButtonName, bool& cooldown, float& CooldownVal);

	void CheckInputValidity();
};