// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BattleMobaCharacter.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Styling/SlateColor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkinnedMeshComponent.h"
#include "Math/Rotator.h"
#include "Animation/AnimSingleNodeInstance.h"

//////////////////////////////////////////////////////////////////////////
// ABattleMobaCharacter
#include "InputLibrary.h"
#include "BattleMobaAnimInstance.h"
#include "BattleMobaPC.h"
#include "DestructibleTower.h"
#include "BattleMobaGameState.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameMode.h"
#include "BMobaTriggerCapsule.h"
#include "BattleMobaCTF.h"
#include "BattleMobaSkillComponent.h"


void ABattleMobaCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleMobaCharacter, TeamName);
	DOREPLIFETIME(ABattleMobaCharacter, PlayerName);
	DOREPLIFETIME(ABattleMobaCharacter, Health);
	DOREPLIFETIME(ABattleMobaCharacter, Stamina);
	DOREPLIFETIME(ABattleMobaCharacter, IsHit);
	DOREPLIFETIME(ABattleMobaCharacter, BoneName);
	DOREPLIFETIME(ABattleMobaCharacter, HitLocation);
	DOREPLIFETIME(ABattleMobaCharacter, AttackSection);
	DOREPLIFETIME(ABattleMobaCharacter, DamageDealers);
	DOREPLIFETIME(ABattleMobaCharacter, Rotate);
	DOREPLIFETIME(ABattleMobaCharacter, AttackerLocation);
	DOREPLIFETIME(ABattleMobaCharacter, CharMesh);
	DOREPLIFETIME(ABattleMobaCharacter, currentTarget);
	DOREPLIFETIME(ABattleMobaCharacter, CounterMoveset);
	DOREPLIFETIME(ABattleMobaCharacter, CTFteam);
	DOREPLIFETIME(ABattleMobaCharacter, CTFentering);
	DOREPLIFETIME(ABattleMobaCharacter, ActorsToGetGold);
	DOREPLIFETIME(ABattleMobaCharacter, closestActor);
	DOREPLIFETIME(ABattleMobaCharacter, RotateToActor);
	DOREPLIFETIME(ABattleMobaCharacter, IsStunned);
	DOREPLIFETIME(ABattleMobaCharacter, OnSpecialAttack);
	DOREPLIFETIME(ABattleMobaCharacter, ActiveColliders);
	DOREPLIFETIME(ABattleMobaCharacter, ArrDamagedEnemy);
	DOREPLIFETIME(ABattleMobaCharacter, comboCount);
	DOREPLIFETIME(ABattleMobaCharacter, MaxHealth);
	DOREPLIFETIME(ABattleMobaCharacter, Defense);
	DOREPLIFETIME(ABattleMobaCharacter, StunDuration);
	DOREPLIFETIME(ABattleMobaCharacter, StunImpulse);
	DOREPLIFETIME(ABattleMobaCharacter, FrontHitMoveset);
	DOREPLIFETIME(ABattleMobaCharacter, BackHitMoveset);
	DOREPLIFETIME(ABattleMobaCharacter, RightHitMoveset);
	DOREPLIFETIME(ABattleMobaCharacter, LeftHitMoveset);
	DOREPLIFETIME(ABattleMobaCharacter, SkillComp);
	DOREPLIFETIME(ABattleMobaCharacter, ActorsInVision);
	DOREPLIFETIME(ABattleMobaCharacter, IsCurrentlyVisible);
	DOREPLIFETIME(ABattleMobaCharacter, damagedActor);
	DOREPLIFETIME(ABattleMobaCharacter, IsImmuned);
	DOREPLIFETIME(ABattleMobaCharacter, ImmunityDur);
	DOREPLIFETIME(ABattleMobaCharacter, ActionSkillName);
	DOREPLIFETIME(ABattleMobaCharacter, AtkSpeed);
	DOREPLIFETIME(ABattleMobaCharacter, MoveSpeed);
	DOREPLIFETIME(ABattleMobaCharacter, KnockbackVector);
}

ABattleMobaCharacter::ABattleMobaCharacter()
{
	// Create a outline
	Outline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	Outline->SetupAttachment(RootComponent);
	Outline->SetRelativeLocation(FVector(0.00f, 0.000000f, -98.000000f));
	Outline->SetVisibility(false);

	//FogCollider
	FogCol = CreateDefaultSubobject<USphereComponent>(TEXT("FogCol"));
	FogCol->SetupAttachment(RootComponent);
	FogCol->SetRelativeLocation(FVector(0.0f, 0.0f, -200.0f));
	FogCol->SetCollisionProfileName("Custom");

	FogCol->OnComponentBeginOverlap.AddDynamic(this, &ABattleMobaCharacter::OnComponentOverlapBegin);
	FogCol->OnComponentEndOverlap.AddDynamic(this, &ABattleMobaCharacter::OnComponentOverlapEnd);

	//this->GetMesh()->SetVisibility(false);
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	BaseArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BaseArrow"));
	BaseArrow->SetupAttachment(RootComponent);
	BaseArrow->SetRelativeLocation(FVector(0.00f, 0.000000f, 0.000000f));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	LeftKickCol = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftKickCol"));
	LeftKickCol->SetupAttachment(GetMesh(), "calf_twist_01_l");
	LeftKickCol->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));
	LeftKickCol->SetRelativeRotation(FRotator(0.0f, 180.0f, 90.0f));
	LeftKickCol->SetBoxExtent(FVector(20.0f, 5.0f, 5.0f));
	LeftKickCol->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC1 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC1"));
	LKC1->SetupAttachment(LeftKickCol);
	LKC1->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	LKC1->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC2 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC2"));
	LKC2->SetupAttachment(LeftKickCol);
	LKC2->SetRelativeLocation(FVector(-8.0f, 0.0f, 0.0f));
	LKC2->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC3 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC3"));
	LKC3->SetupAttachment(LeftKickCol);
	LKC3->SetRelativeLocation(FVector(-1.0f, 0.0f, 0.0f));
	LKC3->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC4 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC4"));
	LKC4->SetupAttachment(LeftKickCol);
	LKC4->SetRelativeLocation(FVector(5.0f, 0.0f, 0.0f));
	LKC4->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC5 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC5"));
	LKC5->SetupAttachment(LeftKickCol);
	LKC5->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	LKC5->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC5->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKC6 = CreateDefaultSubobject<UBoxComponent>(TEXT("LKC6"));
	LKC6->SetupAttachment(LeftKickCol);
	LKC6->SetRelativeLocation(FVector(16.0f, 0.0f, 0.0f));
	LKC6->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LKC6->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RightKickCol = CreateDefaultSubobject<UBoxComponent>(TEXT("RightKickCol"));
	RightKickCol->SetupAttachment(GetMesh(), "calf_twist_01_r");
	RightKickCol->SetRelativeLocation(FVector(5.0f, 0.0f, 0.0f));
	RightKickCol->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	RightKickCol->SetBoxExtent(FVector(20.0f, 5.0f, 5.0f));
	RightKickCol->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC1 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC1"));
	RKC1->SetupAttachment(RightKickCol);
	RKC1->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	RKC1->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC2 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC2"));
	RKC2->SetupAttachment(RightKickCol);
	RKC2->SetRelativeLocation(FVector(-8.0f, 0.0f, 0.0f));
	RKC2->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC3 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC3"));
	RKC3->SetupAttachment(RightKickCol);
	RKC3->SetRelativeLocation(FVector(-1.0f, 0.0f, 0.0f));
	RKC3->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC4 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC4"));
	RKC4->SetupAttachment(RightKickCol);
	RKC4->SetRelativeLocation(FVector(5.0f, 0.0f, 0.0f));
	RKC4->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC5 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC5"));
	RKC5->SetupAttachment(RightKickCol);
	RKC5->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	RKC5->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC5->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RKC6 = CreateDefaultSubobject<UBoxComponent>(TEXT("RKC6"));
	RKC6->SetupAttachment(RightKickCol);
	RKC6->SetRelativeLocation(FVector(16.0f, 0.0f, 0.0f));
	RKC6->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RKC6->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LKickArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LKickArrow"));
	LKickArrow->SetupAttachment(LeftKickCol);
	LKickArrow->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	RKickArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RKickArrow"));
	RKickArrow->SetupAttachment(RightKickCol);
	RKickArrow->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	LeftPunchCol = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftPunchCol"));
	LeftPunchCol->SetupAttachment(GetMesh(), "hand_l");
	LeftPunchCol->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	LeftPunchCol->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	LeftPunchCol->SetBoxExtent(FVector(20.0f, 5.0f, 5.0f));
	LeftPunchCol->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC1 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC1"));
	LPC1->SetupAttachment(LeftPunchCol);
	LPC1->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	LPC1->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC2 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC2"));
	LPC2->SetupAttachment(LeftPunchCol);
	LPC2->SetRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
	LPC2->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC3 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC3"));
	LPC3->SetupAttachment(LeftPunchCol);
	LPC3->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));
	LPC3->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC4 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC4"));
	LPC4->SetupAttachment(LeftPunchCol);
	LPC4->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	LPC4->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC5 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC5"));
	LPC5->SetupAttachment(LeftPunchCol);
	LPC5->SetRelativeLocation(FVector(5.0f, 0.0f, 0.0f));
	LPC5->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC5->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPC6 = CreateDefaultSubobject<UBoxComponent>(TEXT("LPC6"));
	LPC6->SetupAttachment(LeftPunchCol);
	LPC6->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	LPC6->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	LPC6->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RightPunchCol = CreateDefaultSubobject<UBoxComponent>(TEXT("RightPunchCol"));
	RightPunchCol->SetupAttachment(GetMesh(), "hand_r");
	RightPunchCol->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RightPunchCol->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
	RightPunchCol->SetBoxExtent(FVector(20.0f, 5.0f, 5.0f));
	RightPunchCol->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC1 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC1"));
	RPC1->SetupAttachment(RightPunchCol);
	RPC1->SetRelativeLocation(FVector(-15.0f, 0.0f, 0.0f));
	RPC1->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC2 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC2"));
	RPC2->SetupAttachment(RightPunchCol);
	RPC2->SetRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
	RPC2->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC3 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC3"));
	RPC3->SetupAttachment(RightPunchCol);
	RPC3->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));
	RPC3->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC4 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC4"));
	RPC4->SetupAttachment(RightPunchCol);
	RPC4->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RPC4->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC5 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC5"));
	RPC5->SetupAttachment(RightPunchCol);
	RPC5->SetRelativeLocation(FVector(5.0f, 0.0f, 0.0f));
	RPC5->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC5->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RPC6 = CreateDefaultSubobject<UBoxComponent>(TEXT("RPC6"));
	RPC6->SetupAttachment(RightPunchCol);
	RPC6->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	RPC6->SetBoxExtent(FVector(3.0f, 5.0f, 5.0f));
	RPC6->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	LPunchArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LPunchArrow"));
	LPunchArrow->SetupAttachment(GetMesh(), "lowerarm_l");

	RPunchArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RPunchArrow"));
	RPunchArrow->SetupAttachment(GetMesh(), "lowerarm_r");
	RPunchArrow->SetRelativeRotation(FRotator(0, -180, 0));

	//WidgetComponent
	W_DamageOutput = CreateDefaultSubobject<UWidgetComponent>(TEXT("W_DamageOutput"));
	W_DamageOutput->SetupAttachment(RootComponent);
	W_DamageOutput->SetRelativeLocation(FVector(0.000000f, 0.0f, 100.0f));
	W_DamageOutput->InitWidget();
	W_DamageOutput->SetIsReplicated(true);

	W_DamageOutput->SetWidgetSpace(EWidgetSpace::Screen);
	W_DamageOutput->SetDrawSize(FVector2D(500.0f, 500.0f));
	W_DamageOutput->SetDrawAtDesiredSize(true);
	W_DamageOutput->SetVisibility(false);
	W_DamageOutput->SetGenerateOverlapEvents(false);

	TraceDistance = 20.0f;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FindCounterMoveset(TEXT("AnimMontage'/Game/Anims/Slt/Montage/Slt_AS_Counter.Slt_AS_Counter'"));

	if (FindCounterMoveset.Object)
	{
		this->CounterMoveset = FindCounterMoveset.Object;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABattleMobaCharacter::OnRep_Health()
{
	UUserWidget* HPWidget = Cast<UUserWidget>(W_DamageOutput->GetUserWidgetObject());
	if (HPWidget)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Player %s with %s Widget"), *GetDebugName(this), *HPWidget->GetFName().ToString()));
		const FName hptext = FName(TEXT("HealthText"));
		UTextBlock* HealthText = (UTextBlock*)(HPWidget->WidgetTree->FindWidget(hptext));

		const FName hpbar = FName(TEXT("HPBar"));
		UProgressBar* HealthBar = (UProgressBar*)(HPWidget->WidgetTree->FindWidget(hpbar));

		if (HealthText)
		{
			FString TheFloatStr = FString::SanitizeFloat(this->Health);

			HealthText->SetText(FText::FromString(TheFloatStr));
			HealthBar->SetPercent(FMath::Clamp(this->Health / this->MaxHealth, 0.0f, 1.0f));
		}
	}
	//this->Health = UGestureInputsFunctions::UpdateProgressBarComponent(this->WidgetHUD, "HPBar", "Health", "HP", "Pain Meter", this->Health, this->MaxHealth);

	/*if (this->IsLocallyControlled())
	{
		this->Health = UGestureInputsFunctions::UpdateProgressBarComponent(this->WidgetHUD, "HPBar", "Health", "HP", "Pain Meter", this->Health, this->MaxHealth);
	}*/
	/*if (!this->IsLocallyControlled())
	{
		float Health1 = UGestureInputsFunctions::UpdateProgressBarComponent(this->WidgetHUD, "HPBarMain_1", "Health_1", "HP", "Pain Meter", this->Health, this->MaxHealth);
	}*/
}

void ABattleMobaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABattleMobaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABattleMobaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABattleMobaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABattleMobaCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABattleMobaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABattleMobaCharacter::TouchStopped);

	//	Camera Shake test input
	PlayerInputComponent->BindAction("TestCam", IE_Released, this, &ABattleMobaCharacter::OnCameraShake);
}

void ABattleMobaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//GetMesh()->bOnlyAllowAutonomousTickPose = false;
}

void ABattleMobaCharacter::BeginPlay()
{
	Super::BeginPlay();

	inst_Fog = GetWorld()->GetParameterCollectionInstance(Mat_Fog);
	inst_Fog->GetScalarParameterValue("Radius", Rad);
	FogCol->SetSphereRadius(Rad, true);

	RefreshPlayerData();
}

float ABattleMobaCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (this->GetLocalRole() == ROLE_Authority)
	{
		if (DamageCauser != this)
		{
			ABattleMobaCharacter* damageChar = Cast<ABattleMobaCharacter>(DamageCauser);
			ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(damageChar->GetPlayerState());
			if (this->DamageDealers.Contains(ps))
			{
				this->DamageDealers.RemoveSingle(ps);
			}
			this->DamageDealers.Emplace(ps);

			if (damageChar->OnSpecialAttack == true)
			{
				FVector DirectionDiff = UKismetMathLibrary::GetDirectionUnitVector(damageChar->GetActorLocation(), this->GetActorLocation());
				FVector MakeVector = FVector(DirectionDiff.X, DirectionDiff.Y, DirectionDiff.Z + 0.2);
				FVector StunVector = MakeVector * damageChar->StunImpulse;

				MulticastRotateHitActor(this, damageChar);
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("Attacker StunImpulse: %f"), damageChar->StunImpulse));

				if (IsValid(ps))
				{
					if (ps->CurrentStyle == 0)
					{
						if (damageChar->ActionSkillName == "Ultimate")
						{
							if (this->IsLocallyControlled() == true)
							{
								GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Enemy Char is Stun until Attacker finishes their ultimate.")));

								FTimerHandle TimerHandle;
								FTimerDelegate TimerDel;

								ServerToggleStun(this, true);
								
								TimerDel.BindLambda([this]()
								{
									ServerToggleStun(this, false);
									
								});

								float montageLength = damageChar->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage()->GetPlayLength();
								this->GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, montageLength, false);
							}
						}
					}
				}
				HitReactionClient(this, Damage, this->HitReactionMoveset, "NormalHit01", damageChar->StunDuration, StunVector, true);
			}

			else if (damageChar->OnSpecialAttack == false)
			{
				/**		Calculate directional hit detection*/
				FRotator RotDifference = UKismetMathLibrary::NormalizedDeltaRotator(this->GetViewRotation(), UKismetMathLibrary::FindLookAtRotation(this->GetPawnViewLocation(), damageChar->GetActorLocation()));
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Rotation Delta: %s"), (*RotDifference.ToString())));

				/**		Get random index from array of section names*/
				FName arr[3] = { "NormalHit01", "NormalHit02", "NormalHit03" };
				int RandInt = rand() % 3;
				FName HitSection = arr[RandInt];
				//FName HitSection = "NormalHit01";

				// right
				if (UKismetMathLibrary::InRange_FloatFloat(RotDifference.Yaw, -135.0f, -45.0f, true, true))
				{
					HitReactionClient(this, Damage, this->RightHitMoveset, HitSection, 0.0f, FVector(0, 0, 0), false);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Hit from RIGHT")));
				}

				// front
				else if (UKismetMathLibrary::InRange_FloatFloat(RotDifference.Yaw, -45.0f, 45.0f, true, true))
				{
					HitReactionClient(this, Damage, this->FrontHitMoveset, HitSection, 0.0f, FVector(0, 0, 0), false);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Hit from FRONT")));
				}

				//	left
				else if (UKismetMathLibrary::InRange_FloatFloat(RotDifference.Yaw, 45.0f, 135.0f, true, true))
				{
					HitReactionClient(this, Damage, this->LeftHitMoveset, HitSection, 0.0f, FVector(0, 0, 0), false);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Hit from LEFT")));
				}

				//	back
				else
				{
					HitReactionClient(this, Damage, this->BackHitMoveset, HitSection, 0.0f, FVector(0, 0, 0), false);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Hit from BACK")));
				}

			}
		}
	}
	return 0.0f;
}

bool ABattleMobaCharacter::ServerSetBlendspace_Validate(ABattleMobaPlayerState* PS)
{
	return true;
}

void ABattleMobaCharacter::ServerSetBlendspace_Implementation(ABattleMobaPlayerState* PS)
{
	MultiSetBlendspace(PS);
}

bool ABattleMobaCharacter::MultiSetBlendspace_Validate(ABattleMobaPlayerState* PS)
{
	return true;
}

void ABattleMobaCharacter::MultiSetBlendspace_Implementation(ABattleMobaPlayerState* PS)
{
	if (PS)
	{
		UBattleMobaAnimInstance* animinstance = Cast<UBattleMobaAnimInstance>(this->GetMesh()->GetAnimInstance());
		if (animinstance)
		{
			//Get int to enum
			animinstance->AnimStyle = static_cast<EStyle>(PS->CurrentStyle);
		}
	}
}

bool ABattleMobaCharacter::ServerSetMaxWalkSpeed_Validate(float Val)
{
	return true;
}

void ABattleMobaCharacter::ServerSetMaxWalkSpeed_Implementation(float Val)
{
	GetCharacterMovement()->MaxWalkSpeed = Val;
}

void ABattleMobaCharacter::OnConstruction(const FTransform & Transform)
{
}

void ABattleMobaCharacter::RefreshPlayerData()
{
	if (IsLocallyControlled())
	{
		ServerSetupStats();
	}

	ABattleMobaPlayerState* PS = Cast<ABattleMobaPlayerState>(GetPlayerState());
	if (PS)
	{
		if (IsLocallyControlled())
		{
			ServerSetBlendspace(PS);
		}
	}

	/*this->GetMesh()->SetSkeletalMesh(CharMesh, false);
	AnimInsta = Cast<UBattleMobaAnimInstance>(this->GetMesh()->GetAnimInstance());*/
	

	FTimerHandle handle;
	FTimerDelegate TimerDelegate;

	//set the row boolean to false after finish cooldown timer
	TimerDelegate.BindLambda([this]()
	{
		this->GetMesh()->SetVisibility(true);

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Rotate: %s"), Rotate ? TEXT("true") : TEXT("false")));

		/*APlayerController* pc = Cast<APlayerController>(this->GetController());
		if (pc)
		{
			if (pc->IsLocalPlayerController() && pc->GetNetMode() != ENetMode::NM_DedicatedServer)
			{

				pc->bShowMouseCursor = false;
				pc->SetInputMode(FInputModeGameOnly());
			}
		}*/

	});
	this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 1.0f, false);

	for (TActorIterator<ABattleMobaCTF> It(GetWorld()); It; ++It)
	{
		Towers.Add(*It);
	}

	CreateCPHUD();

	FinishSetupBeginPlay();

	if (IsLocallyControlled() == true)
	{
		// Iterate over all actors, can also supply a different base class if needed
		for(TActorIterator<ABattleMobaCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Follow iterator object to my actual actor pointer
			ABattleMobaCharacter* MyActor = *ActorItr;
			if (MyActor->TeamName != this->TeamName)
			{
				MyActor->GetMesh()->SetCullDistance(1000.f);
				MyActor->Outline->SetCullDistance(1000.f);
			}
		}
	}
}

void ABattleMobaCharacter::CheckSwipeType(EInputType Type, FVector2D Location, TEnumAsByte<ETouchIndex::Type> TouchIndex)
{
	if (UGameplayStatics::GetPlatformName() == "IOS" || UGameplayStatics::GetPlatformName() == "Android")
	{
		//Check for touch pressed
		if (Type == EInputType::Pressed)
		{
			if (TouchIndex == ETouchIndex::Touch1)
			{
				////if current Location is on the left side of screen, set swipe mechanic to move the player, else set to rotate the camera
				//if (UInputLibrary::PointOnLeftHalfOfScreen(Location))
				//{
				//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Move")));

				//	TouchStart = Location;
				//	MoveTouchIndex = TouchIndex;
				//	IsPressed = true;
				//}
				/*else*/ if (!UInputLibrary::PointOnLeftHalfOfScreen(Location))
				{
				InitRotateToggle = true;
				}
			}
			else if (TouchIndex == ETouchIndex::Touch2)
			{
				//if current Location is on the left side of screen, set swipe mechanic to move the player, else set to rotate the camera
				//if (UInputLibrary::PointOnLeftHalfOfScreen(Location))
				//{
				//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Move")));

				//	TouchStart = Location;
				//	MoveTouchIndex = TouchIndex;
				//	IsPressed = true;
				//}
				/*else */if (!UInputLibrary::PointOnLeftHalfOfScreen(Location))
				{
					InitRotateToggle = true;
				}
			}
		}
		//If the pressed touch is swiping
		else if (Type == EInputType::Hold)
		{
		if (TouchIndex == ETouchIndex::Touch1)
		{
			//if current Location is on the left side of screen, set swipe mechanic to move the player, else set to rotate the camera
			//if (UInputLibrary::PointOnLeftHalfOfScreen(Location))
			//{
			//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Move")));

			//	TouchEnd = Location;
			//	MoveTouchIndex = TouchIndex;
			//}
			/*else */if (!UInputLibrary::PointOnLeftHalfOfScreen(Location))
			{
				RotTouchIndex = TouchIndex;
			}
		}
		if (TouchIndex == ETouchIndex::Touch2)
		{
			//if current Location is on the left side of screen, set swipe mechanic to move the player, else set to rotate the camera
			//if (UInputLibrary::PointOnLeftHalfOfScreen(Location))
			//{
			//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Move")));

			//	TouchEnd = Location;
			//	MoveTouchIndex = TouchIndex;
			//}
			/*else */if (!UInputLibrary::PointOnLeftHalfOfScreen(Location))
			{
				RotTouchIndex = TouchIndex;
			}
		}
		}
		//if the current touch index is being released
		else if (Type == EInputType::Released)
		{
		if (TouchIndex == ETouchIndex::Touch1)
		{
			if (MoveTouchIndex == TouchIndex)
			{
				IsPressed = false;
			}
		}
		if (TouchIndex == ETouchIndex::Touch2)
		{
			if (MoveTouchIndex == TouchIndex)
			{
				IsPressed = false;
			}
		}

		}
	}

}

void ABattleMobaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WithinVicinity)
	{
		UInputLibrary::SetUIVisibility(W_DamageOutput, this);
	}

	////////////////Mobile Input/////////////////////////////
	if (this->GetNetMode() != ENetMode::NM_DedicatedServer)
	{
		//Detect Movement Input
		if (IsPressed)
		{
			AddSwipeVectorToMovementInput();
		}
		if (InitRotateToggle)
		{
			AddSwipeVectorToRotationInput();
		}
	}
	////////////////////////////////////////////////////////
	//if (currentTarget != nullptr && Rotate == true)
	//{
	//	if (HasAuthority())
	//	{
	//		if (this->IsLocallyControlled())
	//		{
	//			FRotator RotatorVal = UKismetMathLibrary::FindLookAtRotation(this->GetCapsuleComponent()->GetComponentLocation(), currentTarget->GetActorLocation());
	//			FRotator FinalVal = FRotator(this->GetCapsuleComponent()->GetComponentRotation().Pitch, RotatorVal.Yaw, this->GetCapsuleComponent()->GetComponentRotation().Roll);
	//			FMath::RInterpTo(this->GetCapsuleComponent()->GetComponentRotation(), FinalVal, DeltaTime, 40.0f);
	//			this->SetActorRotation(FinalVal);
	//			RotateToCameraView(FinalVal);
	//			//this->SetActorRotation(FRotator(this->GetActorRotation().Pitch, this->GetControlRotation().Yaw, this->GetActorRotation().Roll));
	//			//
	//			//Set rotate to false
	//			/*FTimerHandle handle;
	//			FTimerDelegate TimerDelegate;
	//			TimerDelegate.BindLambda([this]()
	//			{
	//				Rotate = false;
	//				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Rotate: %s"), Rotate ? TEXT("true") : TEXT("false")));
	//			});
	//			this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 1.0f, false);*/
	//		}
	//	}
	//	else
	//	{
	//		if (this->GetController() != nullptr)
	//		{
	//			/*ServerRotateToCameraView(FRotator(this->GetActorRotation().Pitch, this->GetControlRotation().Yaw, this->GetActorRotation().Roll));
	//			this->SetActorRotation(FRotator(this->GetActorRotation().Pitch, this->GetControlRotation().Yaw, this->GetActorRotation().Roll));*/
	//			FRotator RotatorVal = UKismetMathLibrary::FindLookAtRotation(this->GetCapsuleComponent()->GetComponentLocation(), currentTarget->GetActorLocation());
	//			FRotator FinalVal = FRotator(this->GetCapsuleComponent()->GetComponentRotation().Pitch, RotatorVal.Yaw, this->GetCapsuleComponent()->GetComponentRotation().Roll);
	//			FMath::RInterpTo(this->GetCapsuleComponent()->GetComponentRotation(), FinalVal, DeltaTime, 40.0f);
	//			ServerRotateToCameraView(FinalVal);
	//			this->SetActorRotation(FinalVal);

	//			//Set rotate to false
	//			/*FTimerHandle handle;
	//			FTimerDelegate TimerDelegate;
	//			TimerDelegate.BindLambda([this]()
	//			{
	//				Rotate = false;
	//				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Rotate: %s"), Rotate ? TEXT("true") : TEXT("false")));
	//			});
	//			this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 1.0f, false);
	//			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Rotate: %s"), Rotate ? TEXT("true") : TEXT("false")));*/
	//		}
	//	}
	//}

}

void ABattleMobaCharacter::AddSwipeVectorToMovementInput()
{
	//Get world direction of swapping
	FVector2D Total = TouchStart - TouchEnd;

	//Get world position
	FVector WorldDirection = FVector(-Total.Y, Total.X, this->GetActorLocation().Z);

	//Get Controller rotator so that teh direction will always align with the rotator
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//rotate a vector from YawRotation
	const FVector Direction = YawRotation.RotateVector(WorldDirection);

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Enable move")));

	//Move character based on world direction
	AddMovementInput(Direction, -1.0f);
}

void ABattleMobaCharacter::AddSwipeVectorToRotationInput()
{
	bool temp;
	FVector2D newVect;
	UGameplayStatics::GetPlayerController(this, 0)->GetInputTouchState(RotTouchIndex, newVect.X, newVect.Y, temp);

	if (temp)
	{
		if (!StartRotate)
		{
			StartRotate = true;
			BaseTurnRate = newVect.X; //Set new x velocity
			BaseLookUpRate = newVect.Y;//Set new y velocity
		}
		else
		{
			//Rotate camera based on velocity of the swipe
			AddControllerYawInput((newVect.X - BaseTurnRate) / 5.0f);
			AddControllerPitchInput((newVect.Y - BaseLookUpRate) / 5.0f);

			BaseTurnRate = newVect.X;//Set new x velocity
			BaseLookUpRate = newVect.Y;//Set new y velocity
		}
	}
	else
	{
		StartRotate = false;
		InitRotateToggle = false;//if current touchindex is released
	}
}

bool ABattleMobaCharacter::ServerRotateToCameraView_Validate(FRotator InRot)
{
	return true;
}

void ABattleMobaCharacter::ServerRotateToCameraView_Implementation(FRotator InRot)
{
	RotateToCameraView(InRot);
}

bool ABattleMobaCharacter::RotateToCameraView_Validate(FRotator InRot)
{
	return true;
}

void ABattleMobaCharacter::RotateToCameraView_Implementation(FRotator InRot)
{
	//Multicast rotation
	FMath::RInterpTo(this->GetCapsuleComponent()->GetComponentRotation(), InRot, GetWorld()->GetDeltaSeconds(), 10.0f);
	this->SetActorRotation(InRot);

	//setting up for cooldown properties
	//FTimerHandle handle;
	//FTimerDelegate TimerDelegate;

	////set the row boolean to false after finish cooldown timer
	//TimerDelegate.BindLambda([this]()
	//{
	//	Rotate = false;
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Rotate: %s"), Rotate ? TEXT("true") : TEXT("false")));
	//});
	//this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 1.0f, false);
}

void ABattleMobaCharacter::SetupWidget()
{
	//OnRep_Team();
	SetupStats();

	/*UUserWidget* HPWidget = Cast<UUserWidget>(W_DamageOutput->GetUserWidgetObject());
	if (HPWidget)
	{
		const FName hptext = FName(TEXT("HealthText"));
		UTextBlock* HealthText = (UTextBlock*)(HPWidget->WidgetTree->FindWidget(hptext));

		if (HealthText)
		{
			FString TheFloatStr = FString::SanitizeFloat(this->Health);

			HealthText->SetText(FText::FromString(TheFloatStr));
			if (TeamName == "Radiant")
			{
				HealthText->SetColorAndOpacity(FLinearColor(0.0, 1.0, 0.0, 1.0));
			}
			else
				HealthText->SetColorAndOpacity(FLinearColor(1.0, 0.0, 0.0, 1.0));
		}
	}*/

	//Setup3DWidgetVisibility();
}

void ABattleMobaCharacter::HideHPBar()
{

	if (WithinVicinity == true) 
	{
		//UInputLibrary::SetUIVisibility(W_DamageOutput, this);
	}
}

bool ABattleMobaCharacter::HitReactionServer_Validate(AActor * HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackImpulse, bool isKnockback)
{
	return true;
}

void ABattleMobaCharacter::HitReactionServer_Implementation(AActor* HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackImpulse, bool isKnockback)
{
	if (this->GetLocalRole() == ROLE_Authority)
	{
		if (HitActor == this)
		{
			HitReactionClient(HitActor, DamageReceived, HitMoveset, MontageSection, StunTime, KnockbackImpulse, isKnockback);
		}
	}
}

bool ABattleMobaCharacter::HitReactionClient_Validate(AActor* HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackImpulse, bool isKnockback)
{
	return true;
}

void ABattleMobaCharacter::HitReactionClient_Implementation(AActor* HitActor, float DamageReceived, UAnimMontage* HitMoveset, FName MontageSection, float StunTime, FVector KnockbackImpulse, bool isKnockback)
{
	if (HitActor == this)
	{
		if (this->Health >= 0)
		{
			float Temp = this->Health - DamageReceived;

			/**		Knockout and respawn*/
			if (Temp <= 0.0f)
			{
				//Set Team Kills
				//ABattleMobaGameState* gs = Cast <ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
				//if (gs)
				//{
				//	if (gs->TeamA.Contains(this->GetPlayerState()->GetPlayerName()))
				//	{
				//		gs->TeamKillB += 1;
				//		//gs->OnRep_TeamKillCountB();
				//	}
				//	else if (gs->TeamB.Contains(this->GetPlayerState()->GetPlayerName()))
				//	{
				//		gs->TeamKillA += 1;
				//		//gs->OnRep_TeamKillCountA();
				//	}
				//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Team A : %d, Team B : %d"), gs->TeamKillA, gs->TeamKillB));
				//}
				Temp = 0.0f;

				//disable action
				this->ActionEnabled = false;
				this->WithinVicinity = false;

				//ps->Death += 1;

				FTimerHandle handle;
				FTimerDelegate TimerDelegate;

				ABattleMobaGameMode* gm = Cast<ABattleMobaGameMode>(GetWorld()->GetAuthGameMode());

				//Set player's death count
				ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(this->GetPlayerState());

				//set the row boolean to false after finish cooldown timer
				TimerDelegate.BindLambda([this, gm, ps]()
				{
					if (gm)
					{
						gm->PlayerKilled(ps, this->DamageDealers.Last(), DamageDealers); //Set current team scores and kills
					}
				});

				//start cooldown the skill
				this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 0.02f, false);

				this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
				this->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
				this->GetMesh()->SetSimulatePhysics(true);
				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				this->GetCharacterMovement()->DisableMovement();

				//ps->StartRespawnTimer(ps);

				if (GetLocalRole() == ROLE_Authority)
				{
					//Start Respawn Timer Count
					ps->StartRespawnTimer(ps);

					/*int tempTimer = ps->RespawnTimeCounter - 3;

					FTimerDelegate ListenerDelegate = FTimerDelegate::CreateUObject(this, &ABattleMobaCharacter::RespawnCharacter, tempTimer);
					this->GetWorld()->GetTimerManager().SetTimer(this->RespawnTimer, ListenerDelegate, 3.0f, false);*/

					this->GetWorld()->GetTimerManager().SetTimer(this->RespawnTimer, this, &ABattleMobaCharacter::RespawnCharacter, 3.0f, false);
				}
			}

			//		Hit reaction for players who have hp > 0
			else
			{
				FTimerHandle delay;
				FTimerDelegate delayDel;

				//		when attacker is on Special Attack skills
				if (isKnockback)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Knock back? %s"), isKnockback ? TEXT("true") : TEXT("false")));
					//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Stun Time: %f"), StunTime));

					FOnMontageEnded MontageEndedDelegate;

					//		stun enemy, does not allow movement and input skill
					if (GetMesh()->SkeletalMesh != nullptr)
					{
						if (this->AnimInsta)
						{
							this->AnimInsta->CanMove = false;
						}
					}
					//		play hit reaction of special attack
					this->GetMesh()->GetAnimInstance()->Montage_Play(HitMoveset, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
					this->GetMesh()->GetAnimInstance()->Montage_JumpToSection(MontageSection);

					//		trigger knockback on enemy
					this->LaunchCharacter(KnockbackImpulse, false, false);

					/*int32 sectionIndex = GetCurrentMontage()->GetSectionIndex(MontageSection);
					float sectionLength = GetCurrentMontage()->GetSectionLength(sectionIndex);*/

					delayDel.BindLambda([this, HitMoveset]()
					{
						this->GetMesh()->GetAnimInstance()->Montage_JumpToSection("GetUp");
						FName activeSection = this->AnimInsta->Montage_GetCurrentSection(HitMoveset);
						//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("Current section is %s"), *activeSection.ToString()));
					});

					this->GetWorldTimerManager().SetTimer(delay, delayDel, StunTime, false);

					//		when montage finished playing, trigger function OnHRMontageEnd - enable movement
					MontageEndedDelegate.BindUObject(this, &ABattleMobaCharacter::OnHRMontageEnd);
					this->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, HitMoveset);

				}

				//		simple directional hit reaction
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Directional Hit Reaction")));
					FOnMontageEnded MontageEndedDelegate;

					//		disable movement and input skill
					if (GetMesh()->SkeletalMesh != nullptr)
					{
						if (this->AnimInsta)
						{
							this->AnimInsta->CanMove = false;
						}
					}

					//		cancel stun timer, stop montage.. leave nullptr to stop any active montage
					if (this->GetWorldTimerManager().IsTimerActive(delay) == true)
					{
						this->GetWorldTimerManager().ClearTimer(delay);
						this->GetMesh()->GetAnimInstance()->Montage_Stop(0.1f, nullptr);
					}

					//		play hit reaction of directional hit reaction
					this->GetMesh()->GetAnimInstance()->Montage_Play(HitMoveset, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
					this->GetMesh()->GetAnimInstance()->Montage_JumpToSection(MontageSection);

					//		when montage finished playing, trigger function OnHRMontageEnd - enable movement
					MontageEndedDelegate.BindUObject(this, &ABattleMobaCharacter::OnHRMontageEnd);
					this->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, HitMoveset);

				}


				/**		Play hit reaction animation on hit*/
				//UAnimMontage* CurrentMontage = this->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage();
				//this->GetMesh()->GetAnimInstance()->Montage_Stop(0.001f, CurrentMontage);
				//PlayAnimMontage(HitMoveset, 1.0f, MontageSection);


			}

			this->Health = Temp;
			this->IsHit = false;

			OnRep_Health();

			//run clear damage dealers array
			if (this->GetWorldTimerManager().IsTimerActive(this->DealerTimer))
			{
				this->GetWorldTimerManager().ClearTimer(this->DealerTimer);

			}
			this->GetWorldTimerManager().SetTimer(this->DealerTimer, this, &ABattleMobaCharacter::ClearDamageDealers, 5.0f, true);

		}
	}
	UpdateHUD();
}

void ABattleMobaCharacter::OnHRMontageEnd(UAnimMontage * animMontage, bool bInterrupted)
{
	if (this->IsLocallyControlled())
	{
		ServerEnableMovement(this, true);
	}
}

void ABattleMobaCharacter::OnComponentOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr && pChar != this && pChar->TeamName != this->TeamName)
	{
		if (this->IsLocallyControlled())
		{
			ServerSetVisibility(this, pChar, .0f, true);
		}
	}
}

void ABattleMobaCharacter::OnComponentOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ABattleMobaCharacter* pChar = Cast<ABattleMobaCharacter>(OtherActor);
	if (pChar != nullptr && pChar != this && pChar->TeamName != this->TeamName)
	{
		if (this->IsLocallyControlled())
		{
			ServerSetVisibility(this, pChar, Rad, false);
		}
	}
}

bool ABattleMobaCharacter::ServerSetVisibility_Validate(ABattleMobaCharacter* owningActor, ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering)
{
	return true;
}

void ABattleMobaCharacter::ServerSetVisibility_Implementation(ABattleMobaCharacter* owningActor, ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering)
{
	MulticastSetVisibility(owningActor, Actor, MaxDrawDist, Entering);
}

bool ABattleMobaCharacter::MulticastSetVisibility_Validate(ABattleMobaCharacter* owningActor, ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering)
{
	return true;
}

void ABattleMobaCharacter::MulticastSetVisibility_Implementation(ABattleMobaCharacter* owningActor, ABattleMobaCharacter* Actor, float MaxDrawDist, bool Entering)
{
	ActorsInVision.AddUnique(Actor);
	UInputLibrary::SetActorVisibility(Actor, ActorsInVision, MaxDrawDist, Entering, owningActor);
}

bool ABattleMobaCharacter::ServerRotateHitActor_Validate(AActor * HitActor, AActor * Attacker)
{
	return true;
}

void ABattleMobaCharacter::ServerRotateHitActor_Implementation(AActor * HitActor, AActor * Attacker)
{
	if (this->GetLocalRole() == ROLE_Authority)
	{
		if (HitActor == this)
		{
			MulticastRotateHitActor(HitActor, Attacker);
		}
	}

}

bool ABattleMobaCharacter::MulticastRotateHitActor_Validate(AActor * HitActor, AActor * Attacker)
{
	return true;
}

void ABattleMobaCharacter::MulticastRotateHitActor_Implementation(AActor * HitActor, AActor * Attacker)
{
	/**		Force player to face Attacker*/
	FRotator hitCharRot = UKismetMathLibrary::FindLookAtRotation(HitActor->GetActorLocation(), Attacker->GetActorLocation());
	FRotator NewRot = FMath::RInterpTo(HitActor->GetActorRotation(), hitCharRot, HitActor->GetWorld()->GetDeltaSeconds(), 200.0f);
	FRotator FinalRot = FRotator(HitActor->GetActorRotation().Pitch, NewRot.Yaw, HitActor->GetActorRotation().Roll);
	HitActor->SetActorRotation(FinalRot);
}

void ABattleMobaCharacter::ClearDamageDealers()
{
	if (this->DamageDealers.IsValidIndex(0))
	{
		this->DamageDealers.RemoveAtSwap(0);
	}
	else
		this->GetWorldTimerManager().ClearTimer(this->DealerTimer);
}

bool ABattleMobaCharacter::ServerLaunchChar_Validate(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	return true;
}

void ABattleMobaCharacter::ServerLaunchChar_Implementation(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	MulticastLaunchChar(LaunchVelocity, bXYOverride, bZOverride);
}

bool ABattleMobaCharacter::MulticastLaunchChar_Validate(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	return true;
}

void ABattleMobaCharacter::MulticastLaunchChar_Implementation(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	this->LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

bool ABattleMobaCharacter::ServerPlayMontage_Validate(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	return true;
}

void ABattleMobaCharacter::ServerPlayMontage_Implementation(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	MulticastPlayMontage(AnimMontage, InPlayRate, StartSectionName);
}

bool ABattleMobaCharacter::MulticastPlayMontage_Validate(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	return true;
}

void ABattleMobaCharacter::MulticastPlayMontage_Implementation(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	FOnMontageEnded MontageEndDel;

	this->GetMesh()->GetAnimInstance()->Montage_Play(AnimMontage, InPlayRate, EMontagePlayReturnType::MontageLength, 0.0f, true);
	this->GetMesh()->GetAnimInstance()->Montage_JumpToSection(StartSectionName);

	MontageEndDel.BindUObject(this, &ABattleMobaCharacter::OnHRMontageEnd);
	this->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndDel, AnimMontage);
}

void ABattleMobaCharacter::CheckInputValidity()
{

}

void ABattleMobaCharacter::GetButtonSkillAction(FKey Currkeys, FString ButtonName, bool& cooldown, float& CooldownVal)
{
	if (this->GetMesh()->SkeletalMesh != nullptr)
	{
		if (this->AnimInsta != nullptr && this->IsStunned == false)
		{
			//		only allows cooldown triggers when action/movement is enabled
			if (this->AnimInsta->CanMove == true)
			{
				if (Health > 0.0f)
				{
					if (IsUpgradingSkill)
					{
						if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
						{
							//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through interface!")));
							if (UGameplayStatics::GetPlatformName() == "IOS" || UGameplayStatics::GetPlatformName() == "Android")
							{
								Cast<IBattleMobaInterface>(MainWidget)->Execute_LookUp(MainWidget, ButtonName);
							}
							else
								Cast<IBattleMobaInterface>(MainWidget)->Execute_LookUp(MainWidget, Currkeys.ToString());
						}
					}
					else
					{
						if (ActionEnabled == true)
						{
							if (ActionTable != nullptr)
							{
								//Used in error reporting
								FString Context;
								for (auto& name : ActionTable->GetRowNames())
								{
									FActionSkill* row = ActionTable->FindRow<FActionSkill>(name, Context);

									if (row)
									{
										if (row->keys == Currkeys || row->ButtonName == ButtonName)
										{
											//Look up through Skills TMap to check for unlocked spells
											if (GetPlayerState()->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
											{
												//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through lookup interface!")));
												Cast<IBattleMobaInterface>(GetPlayerState())->Execute_LookUp(GetPlayerState(), row->ButtonName);

												//If the spell is already unlocked
												if (IsExist)
												{
													//		Those skills which use CD except dash
													if (row->IsUsingCD && !row->UseTranslate)
													{
														//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("row->isOnCD: %s"), row->isOnCD ? TEXT("true") : TEXT("false")));

														//if the skill is on cooldown, stop playing the animation, else play the skill animation
														if (row->isOnCD == true)
														{
															GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Current %s skill is on cooldown!!"), ((*name.ToString()))));
															cooldown = row->isOnCD;
															//row->isOnCD = false;
															break;
														}
														else if (row->isOnCD == false)
														{
															cooldown = row->isOnCD;
															row->isOnCD = true;
															//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Current key is %s"), ((*row->keys.ToString()))));
															if (row->SkillMoveset != nullptr)
															{
																if (this->IsLocallyControlled())
																{
																	/*DetectNearestTarget(EResult::Cooldown, *row);
																	AttackSection = "NormalAttack01";*/
																	//play the animation that visible to all clients
																	//ServerExecuteAction(*row, CurrentSection, AttackSection, true);
																	FTimerHandle handle;
																	FTimerDelegate TimerDelegate;

																	//set the row boolean to false after finish cooldown timer
																	TimerDelegate.BindLambda([row, this]()
																	{
																		UE_LOG(LogTemp, Warning, TEXT("DELAY BEFORE SETTING UP COOLDOWN TO FALSE"));
																		row->isOnCD = false;

																		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString::Printf(TEXT("row->isOnCD: %s"), row->isOnCD ? TEXT("true") : TEXT("false")));
																	});

																	//start cooldown the skill
																	this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, row->CDDuration, false);
																	CooldownVal = row->CDDuration;
																	//break;

																	//setting up for cooldown properties

																	DetectNearestTarget(EResult::Cooldown, *row);
																	AttackSection = "NormalAttack01";
																}


															}
															//Calls widget for display purposes
															if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
															{
																//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through lookup interface!")));
																Cast<IBattleMobaInterface>(MainWidget)->Execute_CheckStringWithFloat(MainWidget, row->ButtonName, CooldownVal, cooldown);
															}
															break;
														}
													}

													//		Dash
													else if (row->IsUsingCD && row->UseTranslate)
													{
														if (row->isOnCD == true)
														{
															//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Current %s skill is on cooldown!!"), ((*name.ToString()))));
															cooldown = row->isOnCD;
															break;
														}
														else if (row->isOnCD == false)
														{
															cooldown = row->isOnCD;
															row->isOnCD = true;
															//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Current key is %s"), ((*row->keys.ToString()))));
															if (row->SkillMoveset != nullptr)
															{
																if (this->IsLocallyControlled())
																{
																	AttackSection = "NormalAttack01";

																	//play the animation that visible to all clients
																	ServerExecuteAction(*row, AttackSection, false);

																	//setting up for cooldown properties
																	FTimerHandle handle;
																	FTimerDelegate TimerDelegate;

																	//set the row boolean to false after finish cooldown timer
																	TimerDelegate.BindLambda([row, this]()
																	{
																		UE_LOG(LogTemp, Warning, TEXT("DELAY BEFORE SETTING UP COOLDOWN TO FALSE"));
																		row->isOnCD = false;

																		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("row->isOnCD: %s"), row->isOnCD ? TEXT("true") : TEXT("false")));
																	});

																	//start cooldown the skill
																	this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, row->CDDuration, false);
																	CooldownVal = row->CDDuration;

																	//Calls widget for display purposes
																	if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
																	{
																		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through lookup interface!")));
																		Cast<IBattleMobaInterface>(MainWidget)->Execute_CheckStringWithFloat(MainWidget, row->ButtonName, CooldownVal, cooldown);
																	}
																	break;
																}
															}
															break;
														}
													}

													/**   current skill has combo */
													else if (row->UseSection)
													{
														//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Current key is %s"), ((*row->keys.ToString()))));
														if (row->SkillMoveset != nullptr)
														{
															if (this->IsLocallyControlled())
															{
																DetectNearestTarget(EResult::Section, *row);
															}
															/*AttackCombo(*row);*/
															break;

														}
													}
												}
											}
										}
									}
								}
								IsExist = false;
							}
						}
					}
				}
			}
		}
	}
	
}

void ABattleMobaCharacter::AttackCombo(FActionSkill SelectedRow)
{
	if (this->OnComboDelay == false)
	{
		this->comboCount = this->comboCount + 1;

		//		Check selected row has many sections in it to determine max combo count
		if (this->comboCount > SelectedRow.Section)
		{
			this->comboCount = 1;
		}

		FString NextSection = UKismetStringLibrary::Concat_StrStr(TEXT("NormalAttack0"), FString::FromInt(comboCount));
		AttackSection = FName(*NextSection);

		if (this->IsLocallyControlled())
		{
			ServerExecuteAction(SelectedRow, AttackSection, false);
		}
	}
}

bool ABattleMobaCharacter::ServerCounterAttack_Validate(ABattleMobaCharacter* hitActor)
{
	return true;
}

void ABattleMobaCharacter::ServerCounterAttack_Implementation(ABattleMobaCharacter* hitActor)
{
	MulticastCounterAttack(hitActor);
}

bool ABattleMobaCharacter::MulticastCounterAttack_Validate(ABattleMobaCharacter* hitActor)
{
	return true;
}

void ABattleMobaCharacter::MulticastCounterAttack_Implementation(ABattleMobaCharacter* hitActor)
{
	FName CounterCurrentSection = hitActor->AnimInsta->Montage_GetCurrentSection(hitActor->CounterMoveset);

	/**		If current montage section is CheckInput. go to next available section*/
	if (UKismetStringLibrary::Contains(CounterCurrentSection.ToString(), TEXT("CheckInput"), false, false))
	{
		FTimerHandle Delay;
		FString NextSection = "CounterAttack01";
		hitActor->AttackSection = FName(*NextSection);

		hitActor->PlayAnimMontage(hitActor->CounterMoveset, 1.0f, hitActor->AttackSection);

		//setting up for translate properties
		FTimerHandle handle;
		FTimerDelegate TimerDelegate;

		//launch player forward after 0.5s
		TimerDelegate.BindLambda([this, hitActor]()
		{
			UE_LOG(LogTemp, Warning, TEXT("DELAY BEFORE TRANSLATE CHARACTER FORWARD"));

			FVector dashVector = FVector(hitActor->GetCapsuleComponent()->GetForwardVector().X*1000.0f, hitActor->GetCapsuleComponent()->GetForwardVector().Y*1000.0f, hitActor->GetCapsuleComponent()->GetForwardVector().Z);


			if (hitActor->IsLocallyControlled())
			{
				hitActor->ServerLaunchChar(dashVector, true, true);
			}
		});
		/**		cooldown to execute lines inside TimerDelegate*/
		hitActor->GetWorldTimerManager().SetTimer(handle, TimerDelegate, 0.5f, false);

	}
}

bool ABattleMobaCharacter::RespawnCharacter_Validate()
{
	return true;
}

void ABattleMobaCharacter::RespawnCharacter_Implementation()
{
	ABattleMobaPC* PC = Cast<ABattleMobaPC>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		//Set current input to interact with UI in spectator mode
		if (PC->IsLocalPlayerController() && PC->GetNetMode() != ENetMode::NM_DedicatedServer)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeGameAndUI());
		}
		ABattleMobaPlayerState* PS = Cast<ABattleMobaPlayerState>(PC->PlayerState);
		if (PS)
		{
			PC->RespawnPawn(PS->SpawnTransform);
			PC->UnPossess();
		}
	}
}

void ABattleMobaCharacter::EnableMovementMode()
{
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		if (this->AnimInsta)
		{
			this->AnimInsta->CanMove = true;
		}
	}
}

bool ABattleMobaCharacter::ServerSetupBaseStats_Validate(float HealthMax, float Def, float MvSpeed, float AttSpeed, float StunDur, float knockBack, float ImmDur)
{
	return true;
}

void ABattleMobaCharacter::ServerSetupBaseStats_Implementation(float HealthMax, float Def, float MvSpeed, float AttSpeed, float StunDur, float knockBack, float ImmDur)
{
	SetupBaseStats(HealthMax, Def, MvSpeed, AttSpeed, StunDur, knockBack, ImmDur);
}

bool ABattleMobaCharacter::SetupBaseStats_Validate(float HealthMax, float Def, float MvSpeed, float AttSpeed, float StunDur, float knockBack, float ImmDur)
{
	return true;
}

void ABattleMobaCharacter::SetupBaseStats_Implementation(float HealthMax, float Def, float MvSpeed, float AttSpeed, float StunDur, float knockBack, float ImmDur)
{
	float hpPercent = UInputLibrary::CalculatePercentageFromValue(Health, MaxHealth, 100.0f);
	Health = UInputLibrary::CalculateValueFromPercentage(hpPercent, HealthMax, 100.0f);
	MaxHealth = HealthMax;
	Defence = Def;
	AtkSpeed = AttSpeed;
	StunDuration = StunDur;
	KnockbackVector = knockBack;
	ImmunityDur = ImmDur;
}

bool ABattleMobaCharacter::ServerSetupStats_Validate()
{
	return true;
}

void ABattleMobaCharacter::ServerSetupStats_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("SERVERSETUPSTATS")));
	SetupStats();
}

bool ABattleMobaCharacter::DetectNearestTarget_Validate(EResult Type, FActionSkill SelectedRow)
{
	return true;
}

void ABattleMobaCharacter::DetectNearestTarget_Implementation(EResult Type, FActionSkill SelectedRow)
{
	if (this->GetMesh()->SkeletalMesh != nullptr)
	{
		if (this->AnimInsta != nullptr && this->IsStunned == false)
		{
			//		check canMove again to detect nearest target and allow actionskill
			if (this->AnimInsta->CanMove == true)
			{
				//		create tarray for hit results
				TArray<FHitResult> hitResults;

				//		start and end locations
				FVector Start = this->GetActorLocation();
				FVector End = FVector(this->GetActorLocation().X + 0.1f, this->GetActorLocation().Y + 0.1f, this->GetActorLocation().Z + 0.1f);

				//		create a collision sphere with radius of RotateRadius
				FCollisionShape SphereCol = FCollisionShape::MakeSphere(RotateRadius);

				FCollisionQueryParams TraceParams;
				TraceParams.AddIgnoredActor(this);

				float Distance1;
				float Distance2;

				//TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
				//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));

				//		check if something got hit in the sweep
				bool isHit = GetWorld()->SweepMultiByChannel(hitResults, Start, End, FQuat::Identity, ECC_PhysicsBody, SphereCol, TraceParams);

				//		draw a purple collision sphere for 0.5 seconds
				DrawDebugSphere(GetWorld(), GetActorLocation(), SphereCol.GetSphereRadius(), 8, FColor::Purple, false, 0.5);

				//bool isHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, RotateRadius, ObjectTypes, true, IgnoreActors, EDrawDebugTrace::ForDuration, hitResults, true);
				if (isHit)
				{
					for (auto& Hit : hitResults)
					{
						ABattleMobaCharacter* pc = Cast<ABattleMobaCharacter>(Hit.Actor);
						ADestructibleTower* tower = Cast<ADestructibleTower>(Hit.Actor);

						if (pc != nullptr)
						{
							if (pc->Health > 0 && pc->TeamName != this->TeamName)
							{

								//		check current closestActor is still the closest or change to new one
								if (IsValid(closestActor))
								{
									Distance1 = closestActor->GetDistanceTo(this);
									Distance2 = Hit.Actor->GetDistanceTo(this);

									if (Distance1 >= Distance2)
									{
										closestActor = pc;
									}
								}

								//		if no closestActor exists, set one
								else
								{
									closestActor = pc;
									//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Closest Actor: %s"), *closestActor->GetName()));
								}
							}
						}

						else if (tower != nullptr && pc == nullptr)
						{
							if (tower->CurrentHealth > 0  && tower->TeamName != this->TeamName)
							{
								//		prioritise player, only then set closest actor to tower
								if (IsValid(closestActor) == false)
								{
									closestActor = tower;
									//closestActor = Cast<AActor>(Hit.Actor);
								}

							}
						}
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Hit.Actor->GetName()));
					}

					ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(this->GetPlayerState());

					//		checks if Boxing for Slumber Fist
					if (ps->CurrentStyle == 0)
					{
						if (this->OnComboDelay == false)
						{
							//		checks if the closest Actor is the same as last one
							if (closestActor == damagedActor)
							{
								slumberCount += 1;
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Slumber Count: %lld"), slumberCount));

								//		decrease the attack interval from increment percentage
								
								if (slumberCount == 1)
								{
									float newAtkSpeed = UInputLibrary::ChangeValueByPercentage(AtkSpeed, 5.0f, false);
									MulticastSetAtkSpeed(this, newAtkSpeed);
									
								}

								else if (slumberCount == 2)
								{
									float newAtkSpeed = UInputLibrary::ChangeValueByPercentage(AtkSpeed, 10.0f, false);
									MulticastSetAtkSpeed(this, newAtkSpeed);
									
								}

								else
								{
									float newAtkSpeed = UInputLibrary::ChangeValueByPercentage(AtkSpeed, 15.0f, false);
									slumberCount = 0;
									MulticastSetAtkSpeed(this, newAtkSpeed);
									
								}
								
							}

							else
							{
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("This is a different closestActor")));
								MulticastSetAtkSpeed(this, AtkSpeed);
								
							}

							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Combo Interval: %f"), this->AtkSpeed));
						}
					}
					RotateNearestTarget(closestActor, Type, SelectedRow);
				}
			}
		}
	}
	
}

bool ABattleMobaCharacter::RotateNearestTarget_Validate(AActor* Target, EResult Type, FActionSkill SelectedRow)
{
	return true;
}

void ABattleMobaCharacter::RotateNearestTarget_Implementation(AActor* Target, EResult Type, FActionSkill SelectedRow)
{
	if (IsValid(Target))
	{
		FLatentActionInfo LatentInfo = FLatentActionInfo();
		LatentInfo.CallbackTarget = this;

		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(this->GetCapsuleComponent()->GetComponentLocation(), Target->GetActorLocation());
		FRotator RotateTo = FRotator(this->GetCapsuleComponent()->GetComponentRotation().Pitch, LookRotation.Yaw, this->GetCapsuleComponent()->GetComponentRotation().Roll);
		//FMath::RInterpTo(this->GetCapsuleComponent()->GetComponentRotation(), RotateTo, this->GetWorld()->GetDeltaSeconds(), 100.0f);

		//Check for Character to move the component target, else just rotate
		//ABattleMobaCharacter* characterActor = Cast<ABattleMobaCharacter>(Target);

		//If the distance between two character is outside range
		if (this->GetDistanceTo(Target) > (RotateRadius / 1.5) && Target != nullptr)
		{
			//Get Vector from player minus target
			FVector FromOriginToTarget = this->GetCapsuleComponent()->GetComponentLocation() - Target->GetActorLocation();

			//To avoid overlapping actors
			//Multiply by Radius and divided by distance
			FromOriginToTarget *= (RotateRadius / 1.5) / this->GetDistanceTo(Target);

			//Set enemyChar if the target is a BattleMobaCharacter
			ABattleMobaCharacter* enemyChar = Cast<ABattleMobaCharacter>(Target);

			if (Type == EResult::Cooldown)
			{
				UBattleMobaAnimInstance* inst = Cast<UBattleMobaAnimInstance>(this->GetMesh()->GetAnimInstance());

				inst->bMoving = true;
				inst->Speed = FromOriginToTarget.Size();

				if (IsValid(enemyChar))
				{
					//rotate and move the component towards target if enemyChar
					UKismetSystemLibrary::MoveComponentTo(this->GetCapsuleComponent(), Target->GetActorLocation() + FromOriginToTarget, RotateTo, true, true, inst->Speed / (Target->GetActorLocation() + FromOriginToTarget).Size(), true, EMoveComponentAction::Type::Move, LatentInfo);
				}

				else
				{
					//rotate the component towards target if not enemyCar
					UKismetSystemLibrary::MoveComponentTo(this->GetCapsuleComponent(), this->GetCapsuleComponent()->GetComponentLocation(), RotateTo, true, true, 0.1f, true, EMoveComponentAction::Type::Move, LatentInfo);
				}
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Speed: %f"), inst->Speed));
				

				//setting up delay properties
				FTimerHandle handle;
				FTimerDelegate TimerDelegate;

				TimerDelegate.BindLambda([this, inst, Type, SelectedRow]()
				{
					//execute action skill
					if (this->IsLocallyControlled())
					{
						ServerExecuteAction(SelectedRow, AttackSection, true);
					}
					inst->bMoving = false;
				});
				/*Start delay to reset speed*/
				this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, inst->Speed / (Target->GetActorLocation() + FromOriginToTarget).Size(), false);
			}
			else if (Type == EResult::Section && this->OnComboDelay == false)
			{
				UBattleMobaAnimInstance* inst = Cast<UBattleMobaAnimInstance>(this->GetMesh()->GetAnimInstance());

				inst->bMoving = true;
				inst->Speed = FromOriginToTarget.Size();

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Speed: %f"), inst->Speed));
				if (IsValid(enemyChar))
				{
					//rotate and move the component towards target if enemyChar
					UKismetSystemLibrary::MoveComponentTo(this->GetCapsuleComponent(), Target->GetActorLocation() + FromOriginToTarget, RotateTo, true, true, inst->Speed / (Target->GetActorLocation() + FromOriginToTarget).Size(), true, EMoveComponentAction::Type::Move, LatentInfo);
				}

				else
				{
					//rotate the component towards target if not enemyCar
					UKismetSystemLibrary::MoveComponentTo(this->GetCapsuleComponent(), this->GetCapsuleComponent()->GetComponentLocation(), RotateTo, true, true, 0.1f, true, EMoveComponentAction::Type::Move, LatentInfo);
				}

				//setting up delay properties
				FTimerHandle handle;
				FTimerDelegate TimerDelegate;

				TimerDelegate.BindLambda([this, inst, Type, SelectedRow]()
				{
					//inst->Speed = 0.0f;

					//execute action skill
					if (this->IsLocallyControlled())
					{
						AttackCombo(SelectedRow);
					}
					inst->bMoving = false;
				});
				/*Start delay to reset speed*/
				this->GetWorldTimerManager().SetTimer(handle, TimerDelegate, inst->Speed / (Target->GetActorLocation() + FromOriginToTarget).Size(), false);
			}
		}
		else
		{
			//rotate the component towards target
			UKismetSystemLibrary::MoveComponentTo(this->GetCapsuleComponent(), this->GetCapsuleComponent()->GetComponentLocation(), RotateTo, true, true, 0.1f, true, EMoveComponentAction::Type::Move, LatentInfo);

			//execute action skill
			if (this->IsLocallyControlled())
			{
				if (Type == EResult::Cooldown)
				{
					ServerExecuteAction(SelectedRow, AttackSection, true);
				}
				else if (Type == EResult::Section)
				{
					AttackCombo(SelectedRow);
				}
			}
		}
		//closestActor = nullptr;
	}
	else
	{
		//Execute when closestactor is invalid
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("TARGET IS INVALID")));

		//execute action skill
		if (this->IsLocallyControlled())
		{
			if (Type == EResult::Cooldown)
			{
				ServerExecuteAction(SelectedRow, AttackSection, true);
			}
			else if (Type == EResult::Section)
			{
				AttackCombo(SelectedRow);
			}
		}
	}
}


void ABattleMobaCharacter::SafeZone(ABMobaTriggerCapsule* TriggerZone)
{
	UUserWidget* HPWidget = Cast<UUserWidget>(TriggerZone->W_Val->GetUserWidgetObject());
	if (HPWidget)
	{
		const FName hpbar = FName(TEXT("PBar"));
		UProgressBar* PBar = (UProgressBar*)(HPWidget->WidgetTree->FindWidget(hpbar));

		const FName hptext = FName(TEXT("ValText"));
		UTextBlock* HealthText = (UTextBlock*)(HPWidget->WidgetTree->FindWidget(hptext));

		if (PBar)
		{
			//FSlateBrush newBrush;
			if (this->IsLocallyControlled())
			{
				//Change to progressbar color to blue
				if (PBar->Percent <= 0.0f)
				{
					PBar->SetFillColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f));
					if (HealthText)
					{
						HealthText->SetColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f));
					}
				}
				SafeZoneServer(TriggerZone);
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Current Team is %s"), ((*Team.ToString()))));
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Team is %s"), ((*this->TeamName.ToString()))));
				if (PBar->Percent <= 0.0f)
				{
					if (this->TeamName == TriggerZone->TeamName)
					{
						//Change progressbar color to red
						PBar->SetFillColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f));
						if (HealthText)
						{
							HealthText->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f));
						}
					}
					else
					{
						//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Team is %s"), ((*this->TeamName.ToString()))));
						//Change progressbar color to red
						PBar->SetFillColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f));
						if (HealthText)
						{
							HealthText->SetColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f));
						}
						//newBrush.TintColor = FLinearColor(1.0f, 0.0f, 0.0f);
					}
				}
			}
			//PBar->WidgetStyle.SetBackgroundImage(newBrush);
		}
	}
	//if (IsLocallyControlled())
	//{
	//	//Run server safezone
	//	SafeZoneServer(TriggerZone);
	//}
}

bool ABattleMobaCharacter::SafeZoneServer_Validate(ABMobaTriggerCapsule* TriggerZone)
{
	return true;
}

void ABattleMobaCharacter::SafeZoneServer_Implementation(ABMobaTriggerCapsule* TriggerZone)
{
	//Check if no server timer is running, start the timer, else stop the timer
	if (GetWorld()->GetTimerManager().IsTimerActive(TriggerZone->FlagTimer) == false)
	{
		FTimerDelegate FunctionsNames = FTimerDelegate::CreateUObject(this, &ABattleMobaCharacter::SafeZoneMulticast, TriggerZone);
		GetWorld()->GetTimerManager().SetTimer(TriggerZone->FlagTimer, FunctionsNames, 1.0f, true);
		return;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TriggerZone->FlagTimer);
		//SafeZoneMulticast(TriggerZone);
	}
}

bool ABattleMobaCharacter::SafeZoneMulticast_Validate(ABMobaTriggerCapsule* TriggerZone)
{
	return true;
}

void ABattleMobaCharacter::SafeZoneMulticast_Implementation(ABMobaTriggerCapsule* TriggerZone)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("SAFE ZONE??????????")));

	TriggerZone->val = TriggerZone->val + 1;
	TriggerZone->OnRep_Val();
}

void ABattleMobaCharacter::ControlFlagMode(ABattleMobaCTF* cf)
{
	if (cf->isCompleted == false)
	{
		ABattleMobaGameState* thisGS = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
		if (thisGS)
		{
			thisGS->SetTowerWidgetColors(cf);
		}
	}

	if (this->IsLocallyControlled())
	{
		//Run server Control Flag
		ControlFlagServer(cf);
	}
}

bool ABattleMobaCharacter::ControlFlagServer_Validate(ABattleMobaCTF * cf)
{
	return true;
}

void ABattleMobaCharacter::ControlFlagServer_Implementation(ABattleMobaCTF* cf)
{
	if (cf->RadiantControl > 0 && cf->DireControl == 0)
	{
		CTFteam = "Radiant";
		cf->ControllingSpeed = cf->ConstantSpeed - (cf->SpeedMultiplier * float(cf->RadiantControl));
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Capture Speed RADIANT: %f"), cf->ControllingSpeed));
	}

	else if (cf->DireControl > 0 && cf->RadiantControl == 0)
	{
		CTFteam = "Dire";
		cf->ControllingSpeed = cf->ConstantSpeed - (cf->SpeedMultiplier * float(cf->DireControl));
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Capture Speed DIRE: %f"), cf->ControllingSpeed));
	}

	else
	{
		CTFteam = "";
	}

	ControlFlagMulticast(cf, CTFteam);
	//cf->RadiantControl = 0;
	//cf->DireControl = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Current CTF Team is %s"), ((*CTFteam.ToString()))));
}

bool ABattleMobaCharacter::ControlFlagMulticast_Validate(ABattleMobaCTF* cf, FName Team)
{
	return true;
}

void ABattleMobaCharacter::ControlFlagMulticast_Implementation(ABattleMobaCTF* cf, FName Team)
{
	if (Team == "Radiant")
	{
		//	Decrease the valDire if exists first before increasing valRadiant
		if (cf->valDire <= 0.0f)
		{
			cf->valDire = 0.0f;

			if (cf->valRadiant < 100.0f)
			{
				cf->valRadiant = cf->valRadiant + 1;
				cf->isCompleted = false;
			}

			else
			{
				cf->valRadiant = 100.0f;
				cf->ControllerTeam = "Radiant";
				if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through interface!")));
					Cast<IBattleMobaInterface>(MainWidget)->Execute_LookUpObject(MainWidget, cf);
				}
				cf->isCompleted = true;
			}
		}

		else
		{
			cf->valDire = cf->valDire - 1;
			cf->isCompleted = false;
		}

		cf->OnRep_Val();
	}

	else if (Team == "Dire")
	{
		if (cf->valRadiant <= 0.0f)
		{
			cf->valRadiant = 0.0f;

			if (cf->valDire < 100.0f)
			{
				cf->valDire = cf->valDire + 1;
				cf->isCompleted = false;
			}

			else
			{
				cf->valDire = 100.0f;
				cf->ControllerTeam = "Dire";
				if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("Pass through interface!")));
					Cast<IBattleMobaInterface>(MainWidget)->Execute_LookUpObject(MainWidget, cf);
				}
				cf->isCompleted = true;
			}
		}

		else
		{
			cf->valRadiant = cf->valRadiant - 1;
			cf->isCompleted = false;
		}

		cf->OnRep_Val();
	}
}

bool ABattleMobaCharacter::SetupStats_Validate()
{
	return true;
}

void ABattleMobaCharacter::SetupStats_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, FString::Printf(TEXT("SETUPSTATS")));
	ABattleMobaPlayerState* PS = Cast<ABattleMobaPlayerState>(GetPlayerState());
	if (PS)
	{
		ABattleMobaPC* pc = Cast<ABattleMobaPC>(UGameplayStatics::GetPlayerController(this, 0));
		if (pc->MainWidget)
		{
			MainWidget = pc->MainWidget;
		}
		SetupBaseStats(PS->MaxHealth, PS->Defense, PS->MoveSpeed, PS->AtkSpeed, PS->StunDuration, PS->KnockbackVector, PS->ImmunityDur);
		CharMesh = PS->CharMesh;
		ActionTable = PS->ActionTable;
		Health = MaxHealth;
		FrontHitMoveset = PS->FrontHitMoveset;
		BackHitMoveset = PS->BackHitMoveset;
		LeftHitMoveset = PS->LeftHitMoveset;
		RightHitMoveset = PS->RightHitMoveset;
		SkillComp = PS->SkillComponent;


		this->GetMesh()->SetSkeletalMesh(CharMesh, false);
		AnimInsta = Cast<UBattleMobaAnimInstance>(this->GetMesh()->GetAnimInstance());

		//Remove previous skill component
		/*for (int32 i = 0; i < this->GetInstanceComponents().Num(); i++)
		{
			UBattleMobaSkillComponent* SkillComponent = Cast<UBattleMobaSkillComponent>(this->GetInstanceComponents()[i]);
			if (SkillComponent)
			{
				SkillComponent->DestroyComponent();
			}
		}*/

		if (ActionTable)
		{
			FString Context;
			for (auto& name : ActionTable->GetRowNames())
			{
				FActionSkill* row = ActionTable->FindRow<FActionSkill>(name, Context);

				if (row)
				{
					row->isOnCD = false;

					//Add skill component
					/*row->SkillComp = UInputLibrary::AddComponentByClass(row->SkillComponent, this);*/
				}
			}
		}
	}
}

bool ABattleMobaCharacter::MulticastExecuteAction_Validate(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack)
{
	return true;
}

void ABattleMobaCharacter::MulticastExecuteAction_Implementation(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack)
{
	ABattleMobaPlayerState* ps = Cast<ABattleMobaPlayerState>(this->GetPlayerState());

	this->AnimInsta->CanMove = false;
	this->OnSpecialAttack = bSpecialAttack;

	if (IsValid(ps))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("ps exists")));

		//		player is executing Special attacks or Ultimate skill
		if (bSpecialAttack == true)
		{
			ActionSkillName = SelectedRow.SkillName;
			//		Boxing
			if (ps->CurrentStyle == 0)
			{
				ABattleMobaCharacter* enemyChar = Cast<ABattleMobaCharacter>(closestActor);

				if (this->IsLocallyControlled())
				{
					//	hook enemy player then gives a barrage of punch combos
					//	enemy player is stunned (play animation stunned) until finish punching
					//	call AttackTrace once in montage
					ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);


				}
			}
			
			//		Silat
			else if (ps->CurrentStyle == 1)
			{
				if (this->IsLocallyControlled())
				{
					ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
				}
			}

			//		Shao Lin Kungfu
			else if (ps->CurrentStyle == 2)
			{
				if (SelectedRow.SkillName == "ulti")
				{
					FTimerHandle TimerHandle;
					FTimerDelegate TimerDel;

					//	player execute skill
					//	becomes immune for a duration
					//	damage increase, attack speed increase and slow down enemy
					if (this->IsLocallyControlled())
					{
						ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
						ServerToggleImmunity(this, true);
					}

					TimerDel.BindLambda([this, SelectedRow]()
					{
						if (this->IsLocallyControlled())
						{
							ServerToggleImmunity(this, false);
						}
					});

					this->GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 3.0f, false);
				}

				else if (SelectedRow.SkillName == "sa01")
				{
					if (IsLocallyControlled())
					{
						ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
					}
				}
				else if (SelectedRow.SkillName == "sa02")
				{
					FTimerHandle TimerHandler1;
					FTimerDelegate TimerDel1;

					FTimerHandle TimerHandler2;
					FTimerDelegate TimerDel2;

					//		get the vector to stay in air
					FVector flyingInAir = FVector(this->GetCapsuleComponent()->GetForwardVector().X * 10000.0f, this->GetCapsuleComponent()->GetForwardVector().Y * 10000.0f, this->GetCapsuleComponent()->GetForwardVector().Z * 10000.0f);

					//		player stays in air before kicking
					if (this->IsLocallyControlled())
					{
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("IN AIR PART OF FLYING KICK")));
						ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
						//ServerLaunchChar(flyingInAir, false, true);
					}

					//		if there is enemy targeted, fly kick to it
					if (IsValid(closestActor))
					{
						FVector thisLoc = this->GetActorLocation();
						FVector closestActorLoc = closestActor->GetActorLocation();

						FVector differenceVector = thisLoc - closestActorLoc;
						float distanceToKick = closestActor->GetDistanceTo(this);

						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("Distance To Kick: %f"), distanceToKick));
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("Distance To Kick: %s"), *differenceVector.ToString()));
						//FVector leapKick = FVector(this->GetCapsuleComponent()->GetForwardVector().X * UKismetMathLibrary::Abs(differenceVector.X), this->GetCapsuleComponent()->GetForwardVector().Y * UKismetMathLibrary::Abs(differenceVector.Y), this->GetCapsuleComponent()->GetForwardVector().Z);
						FVector leapKick = FVector(this->GetCapsuleComponent()->GetForwardVector().X * distanceToKick, this->GetCapsuleComponent()->GetForwardVector().Y * distanceToKick, this->GetCapsuleComponent()->GetForwardVector().Z);
						TimerDel1.BindLambda([this, SelectedRow, leapKick]()
						{
							if (this->IsLocallyControlled())
							{
								//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("FLYING KICK ON TARGET")));
								ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, "LeapKicking");
								ServerLaunchChar(leapKick, true, true);
							}
						});

						TimerDel2.BindLambda([this, SelectedRow]()
						{
							if (this->IsLocallyControlled())
							{
								ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, "FinishOut");
							}
						});

						this->GetWorldTimerManager().SetTimer(TimerHandler1, TimerDel1, 0.3f, false);
						this->GetWorldTimerManager().SetTimer(TimerHandler2, TimerDel2, 0.6f, false);
					}

					//		else just jump
					else
					{
						TimerDel1.BindLambda([this, SelectedRow]()
						{
							if (this->IsLocallyControlled())
							{
								//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("FLYING KICK CANCELS OUT AS THERE IS NO TARGET")));
								ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, "FinishOut");
							}
						});
						
						this->GetWorldTimerManager().SetTimer(TimerHandler1, TimerDel1, 0.5f, false);
					}

				}

			}

		}

		else
		{
			//		player is executing Dash
			if (SelectedRow.UseTranslate)
			{
				FTimerHandle dashTimer;
				FTimerDelegate dashTimerDel;

				/*int32 sectionIndex = SelectedRow.SkillMoveset->GetSectionIndex(MontageSection);
				float sectionLength = SelectedRow.SkillMoveset->GetSectionLength(sectionIndex);*/

				//FOnMontageEnded MontageEndDel;

				FVector dashVector = FVector(this->GetCapsuleComponent()->GetForwardVector().X*SelectedRow.TranslateDist, this->GetCapsuleComponent()->GetForwardVector().Y*SelectedRow.TranslateDist, this->GetCapsuleComponent()->GetForwardVector().Z);

				if (this->IsLocallyControlled())
				{
					ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
					ServerLaunchChar(dashVector, false, false);

				}

				dashTimerDel.BindLambda([this, SelectedRow, dashVector]()
				{
					if (this->IsLocallyControlled())
					{

						ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, "GetUp");
					}
				});

				this->GetWorldTimerManager().SetTimer(dashTimer, dashTimerDel, 0.2f, false);

			}
			//		player is executing Normal Attack 1
			else if (SelectedRow.UseSection)
			{
				FTimerHandle delay;
				FTimerDelegate timerDel;

				this->OnComboDelay = true;

				if (this->IsLocallyControlled())
				{
					ServerPlayMontage(SelectedRow.SkillMoveset, 1.0f, MontageSection);
				}

				int32 sectionIndex = SelectedRow.SkillMoveset->GetSectionIndex(MontageSection);
				float sectionLength = SelectedRow.SkillMoveset->GetSectionLength(sectionIndex);

				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("section Length: %f"), sectionLength));

				timerDel.BindLambda([this]()
				{
					this->OnComboDelay = false;

				});

				this->GetWorldTimerManager().SetTimer(delay, timerDel, sectionLength + AtkSpeed, false);


			}
		}
			

		this->MinDamage = SelectedRow.MinDamage;
		this->MaxDamage = SelectedRow.MaxDamage;
		this->BaseDamage = float(FMath::RandRange(this->MinDamage, this->MaxDamage));

		//Increase base damage by level
		this->BaseDamage = UInputLibrary::ChangeValueByPercentage(this->BaseDamage, ps->BaseDamagePercent, true);

		this->HitReactionMoveset = SelectedRow.HitMoveset;
		this->StunDuration = SelectedRow.StunTime;
		this->StunImpulse = SelectedRow.StunImpulse;
	}
	
}

bool ABattleMobaCharacter::CheckDamage_Validate(UParticleSystem * ImpactEffect, FName AttachTo, USoundBase * HitSound, float damageDistance)
{
	return true;	
}

void ABattleMobaCharacter::CheckDamage_Implementation(UParticleSystem * ImpactEffect, FName AttachTo, USoundBase * HitSound, float damageDistance)
{
	if (IsValid(closestActor))
	{
		ABattleMobaCharacter* damagedChar = Cast<ABattleMobaCharacter>(closestActor);
		ADestructibleTower* damagedTower = Cast<ADestructibleTower>(closestActor);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("THERE IS CLOSEST ACTOR")));

		if (IsValid(damagedChar))
		{
			if (damagedChar->IsStunned == false && damagedChar->Health > 0)
			{
				float distanceToChar = damagedChar->GetDistanceTo(this);
				ABattleMobaPlayerState* attackerPS = Cast<ABattleMobaPlayerState>(this->GetPlayerState());

				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Damage Distance: %f"), distanceToChar));

				if (distanceToChar < damageDistance)
				{
					//		when attacker is damaging enemy who is on Silat counter skill
					if (damagedChar->GetMesh()->GetAnimInstance()->Montage_IsPlaying(CounterMoveset))
					{
						ServerRotateHitActor(damagedChar, this);
						ServerCounterAttack(damagedChar);

						/*damagedChar->MulticastRotateHitActor(damagedChar, this);
						damagedChar->MulticastCounterAttack(damagedChar);
						*/
					}

					else
					{
						damagedChar->HitReactionMoveset = this->HitReactionMoveset;

						//		triggers status effect if there is one when attacker is on special attack
						if (this->OnSpecialAttack == true)
						{
							if (IsValid(attackerPS))
							{
								if (attackerPS->CurrentStyle == 0)
								{

								}

								else if (attackerPS->CurrentStyle == 1)
								{

								}

								else if (attackerPS->CurrentStyle == 2)
								{
								}

								DoDamage(damagedChar);
							}
						}

						//		apply regular damage to enemy on valid if the attacker is on normal attack
						else
						{
							DoDamage(damagedChar);

						}
					}

					//		display visual effect and produce sound effect on enemy hit
					PlayEffectsClient(ImpactEffect, AttachTo, HitSound);

				}
			}
		}

		else if (IsValid(damagedTower) && !IsValid(damagedChar))
		{
			float distanceToTower = damagedTower->GetDistanceTo(this);

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Damage Distance: %f"), distanceToTower));

			if (distanceToTower < 600.0f)
			{
				TowerReceiveDamage(damagedTower, this->BaseDamage);

				//		display visual effect and produce sound effect on enemy hit
				PlayEffectsClient(ImpactEffect, AttachTo, HitSound);
			}
		}
		//		store current closestActor in a temp
		damagedActor = closestActor;
	}
	closestActor = nullptr;
}

bool ABattleMobaCharacter::AttackTrace_Validate(bool traceStart, int activeAttack, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound)
{
	return true;
}

void ABattleMobaCharacter::AttackTrace_Implementation(bool traceStart, int activeAttack, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Start Tracing? %s"), traceStart ? TEXT("True") : TEXT("False")));

	if (traceStart)
	{
		FHitResult hitResult;

		FVector startTrace;
		FVector endTrace;

		TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));

		TArray<class AActor*> IgnoreActors;
		IgnoreActors.Add(this);

		ActiveColliders.Empty();

		if (activeAttack == 1)
		{
			ActiveColliders.Add(LPC1);
			ActiveColliders.Add(LPC2);
			ActiveColliders.Add(LPC3);
			ActiveColliders.Add(LPC4);
			ActiveColliders.Add(LPC5);
			ActiveColliders.Add(LPC6);
		}

		else if (activeAttack == 2)
		{
			ActiveColliders.Add(RPC1);
			ActiveColliders.Add(RPC2);
			ActiveColliders.Add(RPC3);
			ActiveColliders.Add(RPC4);
			ActiveColliders.Add(RPC5);
			ActiveColliders.Add(RPC6);
		}

		else if (activeAttack == 3)
		{
			ActiveColliders.Add(LKC1);
			ActiveColliders.Add(LKC2);
			ActiveColliders.Add(LKC3);
			ActiveColliders.Add(LKC4);
			ActiveColliders.Add(LKC5);
			ActiveColliders.Add(LKC6);
		}

		else if (activeAttack == 4)
		{
			ActiveColliders.Add(RKC1);
			ActiveColliders.Add(RKC2);
			ActiveColliders.Add(RKC3);
			ActiveColliders.Add(RKC4);
			ActiveColliders.Add(RKC5);
			ActiveColliders.Add(RKC6);
		}

		for (auto& attackCol : ActiveColliders)
		{
			startTrace = attackCol->GetComponentLocation();
			endTrace = startTrace + (GetActorForwardVector() * TraceDistance);

			//bool bHit = GetWorld()->LineTraceSingleByObjectType(hitResult, startTrace, endTrace, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_Attack)), FCollisionQueryParams(TEXT("IKTrace"), false, this));
			bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), startTrace, endTrace, ObjectTypes, true, IgnoreActors, EDrawDebugTrace::ForDuration, hitResult, true, FColor::Red, FColor::Green, 3.0f);

			if (bHit)
			{
				HitResult(hitResult, ImpactEffect, AttachTo, HitSound);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *hitResult.Actor->GetName()));
			}
		}
	}

	else
	{
		ArrDamagedEnemy.Empty();
	}
}

bool ABattleMobaCharacter::HitResult_Validate(FHitResult hit, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound)
{
	return true;
}

void ABattleMobaCharacter::HitResult_Implementation(FHitResult hit, UParticleSystem* ImpactEffect, FName AttachTo, USoundBase* HitSound)
{
	ABattleMobaCharacter* DamagedEnemy = Cast<ABattleMobaCharacter>(hit.Actor);
	ADestructibleTower* DamagedTower = Cast<ADestructibleTower>(hit.Actor);

	if (IsValid(DamagedEnemy))
	{
		if (DamagedEnemy->TeamName != this->TeamName && (DamagedEnemy == hit.Actor) && !(ArrDamagedEnemy.Contains(DamagedEnemy)) && DamagedEnemy->Health > 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *UKismetSystemLibrary::GetDisplayName(DamagedEnemy)));
			if (DamagedEnemy->AnimInsta->Montage_IsPlaying(DamagedEnemy->CounterMoveset))
			{
				if (DamagedEnemy->IsLocallyControlled())
				{
					ServerRotateHitActor(DamagedEnemy, this);
					ServerCounterAttack(DamagedEnemy);
				}
			}

			else if (DamagedEnemy->AnimInsta->Montage_IsPlaying(DamagedEnemy->CounterMoveset) == false)
			{
				/**		set the hitActor hit movesets from the same row of skill moveset the attacker used*/
				DamagedEnemy->HitReactionMoveset = this->HitReactionMoveset;
				ArrDamagedEnemy.Add(DamagedEnemy);
				DoDamage(DamagedEnemy);
			}

			PlayEffectsClient(ImpactEffect, AttachTo, HitSound);
		}
	}

	else if (IsValid(DamagedTower) && !IsValid(DamagedEnemy))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("DamagedTower = %s"), IsValid(DamagedTower) ? TEXT("True") : TEXT("False")));
		if (DamagedTower->TeamName != this->TeamName && DamagedTower == hit.Actor && !(ArrDamagedEnemy.Contains(DamagedTower)) && DamagedTower->isDestroyed == false)
		{
			ArrDamagedEnemy.Add(DamagedTower);
			TowerReceiveDamage(DamagedTower, this->BaseDamage);

			PlayEffectsClient(ImpactEffect, AttachTo, HitSound);
		}
	}
}

bool ABattleMobaCharacter::SpecialAttackTrace_Validate(FVector BoxSize, UParticleSystem* ImpactEffect, FName DamageSocket, FName ParticleSocket, USoundBase* HitSound)
{
	return true;
}

void ABattleMobaCharacter::SpecialAttackTrace_Implementation(FVector BoxSize, UParticleSystem* ImpactEffect, FName DamageSocket, FName ParticleSocket, USoundBase* HitSound)
{
	//		initialize hit results
	TArray<FHitResult> hitResults;

	//		start and end locations
	FVector Start = this->GetActorLocation();
	FVector End = FVector(this->GetActorLocation().X + 0.1f, this->GetActorLocation().Y + 0.1f, this->GetActorLocation().Z + 0.1f);

	TArray<class AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));

	TArray<class AActor*> Victims;
	
	//		check if something got hit in the sweep, red on false, green on true Col1->GetComponentLocation() + (GetActorForwardVector() * TraceDistance
	if (DamageSocket != NAME_None)
	{
		bool bHit = UKismetSystemLibrary::BoxTraceMultiForObjects(this->GetWorld(), this->GetMesh()->GetSocketLocation(DamageSocket), this->GetMesh()->GetSocketLocation(DamageSocket)+ 0.1f, BoxSize, this->GetActorRotation(), ObjectTypes, true, IgnoreActors, EDrawDebugTrace::ForDuration, hitResults, true, FColor::Red, FColor::Green, 2.0f);

		if (bHit)
		{
			for (auto& Hit : hitResults)
			{
				ABattleMobaCharacter* pc = Cast<ABattleMobaCharacter>(Hit.Actor);
				ADestructibleTower* tower = Cast<ADestructibleTower>(Hit.Actor);

				if (pc != nullptr)
				{
					if (pc->Health > 0 && pc->TeamName != this->TeamName && !(Victims.Contains(pc)))
					{
						if (pc->AnimInsta->Montage_IsPlaying(pc->CounterMoveset))
						{
							if (pc->IsLocallyControlled())
							{
								ServerRotateHitActor(pc, this);
								ServerCounterAttack(pc);
							}
						}

						else if (pc->AnimInsta->Montage_IsPlaying(pc->CounterMoveset) == false)
						{
							/**		set the hitActor hit movesets from the same row of skill moveset the attacker used*/
							pc->HitReactionMoveset = this->HitReactionMoveset;

							//		apply damage once on enemy
							Victims.Add(pc);
							DoDamage(pc);
						}

						PlayEffectsClient(ImpactEffect, ParticleSocket, HitSound);
					}
				}

				else if (tower != nullptr && pc == nullptr)
				{
					if (tower->TeamName != this->TeamName && tower->isDestroyed == false && !(Victims.Contains(tower)))
					{
						//		apply damage on tower
						TowerReceiveDamage(tower, this->BaseDamage);
						Victims.Add(tower);

						PlayEffectsClient(ImpactEffect, ParticleSocket, HitSound);
					}
				}
			}
		}
	}
}

bool ABattleMobaCharacter::ServerPlayEffects_Validate(UParticleSystem * ImpactEffect, FName ParticleSocket, USoundBase * HitSound)
{
	return true;
}

void ABattleMobaCharacter::ServerPlayEffects_Implementation(UParticleSystem * ImpactEffect, FName ParticleSocket, USoundBase * HitSound)
{
	if (this->GetLocalRole() == ROLE_Authority)
	{
		PlayEffectsClient(ImpactEffect, ParticleSocket, HitSound);
	}
}

bool ABattleMobaCharacter::PlayEffectsClient_Validate(UParticleSystem * ImpactEffect, FName ParticleSocket, USoundBase * HitSound)
{
	return true;
}

void ABattleMobaCharacter::PlayEffectsClient_Implementation(UParticleSystem * ImpactEffect, FName ParticleSocket, USoundBase * HitSound)
{
	if (IsValid(ImpactEffect))
	{
		if (ParticleSocket != NAME_None)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Effect: "), *ImpactEffect->GetName()));

			//		spawn particle on closest bone location to hit impact
			UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), ImpactEffect, this->GetMesh()->GetSocketLocation(ParticleSocket), FRotator::ZeroRotator, false);
		}
	}

	if (IsValid(HitSound))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Hit Sound: "), *HitSound->GetName()));
		UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), HitSound, this->GetActorLocation());
	}
}

bool ABattleMobaCharacter::DoDamage_Validate(AActor* HitActor)
{
	return true;
}

void ABattleMobaCharacter::DoDamage_Implementation(AActor* HitActor)
{
	if (this != HitActor)
	{
		/**		Calculate Damage Dealt by Enemy and set precision to tenth */
		this->ActualDamage = (this->BaseDamage * this->BuffDamage) * (100 / (100 + ((Defence * BuffDefence) * ((1 - ReducedDefence) * 0.84))));
		this->ActualDamage = FMath::RoundToInt(ActualDamage);

		/**		Apply Damage */
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Damage Applied: %f"), this->ActualDamage));
		UE_LOG(LogTemp, Warning, TEXT("Damage Applied: %f"), this->ActualDamage);
		this->ActualDamage = UGameplayStatics::ApplyDamage(HitActor, this->ActualDamage, nullptr, this, nullptr);
	}
}

bool ABattleMobaCharacter::ServerExecuteAction_Validate(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack)
{
	return true;
}

void ABattleMobaCharacter::ServerExecuteAction_Implementation(FActionSkill SelectedRow, FName MontageSection, bool bSpecialAttack)
{
	MulticastExecuteAction(SelectedRow, MontageSection, bSpecialAttack);
}

void ABattleMobaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	//Jump();
}

void ABattleMobaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	//StopJumping();
}

void ABattleMobaCharacter::OnCameraShake()
{
	CombatCamShake();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Calling Camera Shake Function")));
}

void ABattleMobaCharacter::OnRep_Team()
{
	UUserWidget* HPWidget = Cast<UUserWidget>(W_DamageOutput->GetUserWidgetObject());
	if (HPWidget)
	{
		const FName hptext = FName(TEXT("TeamName"));
		UTextBlock* HealthText = (UTextBlock*)(HPWidget->WidgetTree->FindWidget(hptext));

		if (HealthText)
		{
			HealthText->SetText(FText::FromName(TeamName));
		}
	}
}

bool ABattleMobaCharacter::TowerReceiveDamage_Validate(ADestructibleTower * Tower, float DamageApply)
{
	return true;
}

void ABattleMobaCharacter::TowerReceiveDamage_Implementation(ADestructibleTower * Tower, float DamageApply)
{
	if (Tower)
	{
		//ABattleMobaCharacter* Player = Cast<ABattleMobaCharacter>(HitActor);
		Tower->CurrentHealth = FMath::Clamp(Tower->CurrentHealth - DamageApply, 0.0f, Tower->MaxHealth);
		Tower->IsHit = false;
		Tower->OnRep_UpdateHealth();

		if (Tower->CurrentHealth <= 0.0f)
		{
			//Tower->CurrentHealth = 0.0f;
			Tower->isDestroyed = true;


			/**		Destroy Tower*/
			//Tower->SetActorHiddenInGame(true);
			Tower->OnRep_Destroy();
		}
	}

}

void ABattleMobaCharacter::TurnAtRate(float Rate)
{
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		YawRate = Rate;
	}
}

void ABattleMobaCharacter::LookUpAtRate(float Rate)
{
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ABattleMobaCharacter::MoveForward(float Value)
{
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			if (this->AnimInsta)
			{
				if (this->AnimInsta->CanMove && this->IsStunned == false)
				{
					// find out which way is forward
					const FRotator Rotation = Controller->GetControlRotation();
					const FRotator YawRotation(0, Rotation.Yaw, 0);

					// get forward vector
					const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
					AddMovementInput(Direction, Value);
					Rotate = false;
					FoundActors.Empty();
					currentTarget = NULL;
				}
			}
		}
	}
}

void ABattleMobaCharacter::MoveRight(float Value)
{
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			if (this->AnimInsta)
			{
				if (this->AnimInsta->CanMove && this->IsStunned == false)
				{
					// find out which way is right
					const FRotator Rotation = Controller->GetControlRotation();
					const FRotator YawRotation(0, Rotation.Yaw, 0);

					// get right vector 
					const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
					// add movement in that direction
					AddMovementInput(Direction, Value);
					Rotate = false;
					FoundActors.Empty();
					currentTarget = NULL;
				}
			}
		}
	}
}

bool ABattleMobaCharacter::ServerEnableMovement_Validate(ABattleMobaCharacter* player, bool allowMove)
{
	return true;
}

void ABattleMobaCharacter::ServerEnableMovement_Implementation(ABattleMobaCharacter* player, bool allowMove)
{
	MulticastEnableMovement(player, allowMove);
}

bool ABattleMobaCharacter::MulticastEnableMovement_Validate(ABattleMobaCharacter* player, bool allowMove)
{
	return true;
}

void ABattleMobaCharacter::MulticastEnableMovement_Implementation(ABattleMobaCharacter* player, bool allowMove)
{
	if (player->GetMesh()->SkeletalMesh != nullptr)
	{
		if (player->AnimInsta != nullptr)
		{
			player->AnimInsta->CanMove = allowMove;
		}
	}
}

bool ABattleMobaCharacter::MulticastSetAtkSpeed_Validate(ABattleMobaCharacter* player, float val)
{
	return true;
}

void ABattleMobaCharacter::MulticastSetAtkSpeed_Implementation(ABattleMobaCharacter* player, float val)
{
	if (IsValid(player))
	{
		player->AtkSpeed = val;
	}
}

bool ABattleMobaCharacter::ServerToggleStun_Validate(ABattleMobaCharacter * player, bool bStun)
{
	return true;
}

void ABattleMobaCharacter::ServerToggleStun_Implementation(ABattleMobaCharacter * player, bool bStun)
{
	MulticastToggleStun(player, bStun);
}

bool ABattleMobaCharacter::MulticastToggleStun_Validate(ABattleMobaCharacter * player, bool bStun)
{
	return true;
}

void ABattleMobaCharacter::MulticastToggleStun_Implementation(ABattleMobaCharacter * player, bool bStun)
{
	if (IsValid(player))
	{
		player->IsStunned = bStun;
	}
}

bool ABattleMobaCharacter::ServerToggleImmunity_Validate(ABattleMobaCharacter * player, bool bImmune)
{
	return true;
}

void ABattleMobaCharacter::ServerToggleImmunity_Implementation(ABattleMobaCharacter * player, bool bImmune)
{
	MulticastToggleImmunity(player, bImmune);
}

bool ABattleMobaCharacter::MulticastToggleImmunity_Validate(ABattleMobaCharacter * player, bool bImmune)
{
	return true;
}

void ABattleMobaCharacter::MulticastToggleImmunity_Implementation(ABattleMobaCharacter * player, bool bImmune)
{
	if (IsValid(player))
	{
		player->IsImmuned = bImmune;
	}
	
}

void ABattleMobaCharacter::Activate_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Implementation"));
}

void ABattleMobaCharacter::ActivatePure(float a, float b, float c, float d, float e, float f, float g)
{
	if (this->IsLocallyControlled())
	{
		this->ServerSetupBaseStats(a, b, c, d, e, f, g);
	}
	if (MainWidget != nullptr && MainWidget->GetClass()->ImplementsInterface(UBattleMobaInterface::StaticClass()))
	{
		//Opens level up windows
		Cast<IBattleMobaInterface>(MainWidget)->Execute_CheckBool(MainWidget, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("Pure"));
}

void ABattleMobaCharacter::CheckBool_Implementation(bool check)
{
	if (check)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("EXIST")));
		IsExist = true;
	}
}
