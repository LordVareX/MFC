// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleMobaHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerStart.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "TextReaderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Json.h"
#include "JsonUtilities.h"

//BattleMoba
#include "BattleMobaCharacter.h"
#include "BattleMobaPlayerState.h"
#include "BattleMobaGameState.h"
#include "BattleMobaHUD.h"
#include "BattleMobaPC.h"

ABattleMobaHUD::ABattleMobaHUD() {

	//static ConstructorHelpers::FClassFinder<UUserWidget> GameObj(TEXT("/Game/ThirdPersonCPP/Blueprints/InGame_W1")); //" / Game / UI / Widgets / UI_Game"
	//GameWidgetClass = GameObj.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> PlayerObj(TEXT("/Game/ThirdPersonCPP/Blueprints/InGame_W2")); //" / Game / UI / Widgets / UI_Game"
	//PlayerWidgetClass = PlayerObj.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> LobbyGameObj(TEXT("/Game/ThirdPersonCPP/Blueprints/W_Lobby")); //" / Game / UI / Widgets / UI_Game"
	//LobbyWidgetClass = LobbyGameObj.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> TimerLobbyGameObj(TEXT("/Game/ThirdPersonCPP/Blueprints/W_TimerLobby")); //" / Game / UI / Widgets / UI_Game"
	//TimerLobbyWidgetClass = TimerLobbyGameObj.Class;

}

void ABattleMobaHUD::BeginPlay() {
	Super::BeginPlay();

	/*APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->bShowMouseCursor = false;
	}*/

	/*if (LobbyWidgetClass != nullptr) {
		LobbyWidget = CreateWidget<UUserWidget>(GetWorld(), LobbyWidgetClass);
		if (LobbyWidget != nullptr) {
			LobbyWidget->AddToViewport();
		}
	}

	if (TimerLobbyWidgetClass != nullptr) {
		TimerLobbyWidget = CreateWidget<UUserWidget>(GetWorld(), TimerLobbyWidgetClass);
		if (TimerLobbyWidget != nullptr) {
			TimerLobbyWidget->AddToViewport();
		}
	}*/

	//if (GameWidgetClass != nullptr) {
	//	GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
	//	if (GameWidget != nullptr) {
	//		GameWidget->AddToViewport();
	//	}
	//}

	/*if (PlayerWidgetClass != nullptr) {
		PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget != nullptr) {
			PlayerWidget->AddToViewport();
		}
	}*/

	//GetWorldTimerManager().SetTimer(SwitchWidgetHandle, this, &ABattleMobaHUD::SwitchWidget, 1.0f, true, 0.1f);
}

//void ABattleMobaHUD::SwitchWidget() {
//	ABattleMobaGameState* BattleMobaGameState = Cast<ABattleMobaGameState>(UGameplayStatics::GetGameState(this));
//	if (BattleMobaGameState != nullptr) {
//		LobbyCheck = BattleMobaGameState->LobbyCheck;
//		if (LobbyCheck == true) {
//			LobbyWidget->RemoveFromParent();
//			TimerLobbyWidget->RemoveFromParent();
//			PlayerWidget->RemoveFromParent();
//			GetWorldTimerManager().ClearTimer(SwitchWidgetHandle);
//			if (GameWidgetClass != nullptr) {
//				UUserWidget* GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
//				if (GameWidget != nullptr) {
//					GameWidget->AddToViewport();
//				}
//			}
//		}
//	}
//}

