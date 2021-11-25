// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BattleMobaHUD.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class BATTLEMOBA_API ABattleMobaHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ABattleMobaHUD();

	UPROPERTY()
		FTimerHandle SwitchWidgetHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* GameWidget;

	

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		bool LobbyCheck;

	UUserWidget* LobbyWidget;

	UUserWidget* TimerLobbyWidget;

	UUserWidget* PlayerWidget;

	

private:
	

	UPROPERTY()
		TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> TimerLobbyWidgetClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> GameWidgetClass;
	//UFUNCTION()
	//	void SwitchWidget();

};
