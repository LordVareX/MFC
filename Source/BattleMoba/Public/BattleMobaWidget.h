// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BattleMobaWidget.generated.h"

class ABattleMobaGameState;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BATTLEMOBA_API UBattleMobaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UBattleMobaWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
		FTimerHandle SetTeammateCountHandle;

	UPROPERTY()
		FTimerHandle SetLatestEventHandle;

	UPROPERTY()
		FTimerHandle SetAveragePlayerLatencyHandle;

	UPROPERTY()
		FTimerHandle SetCountdownTimerHandle;

	UPROPERTY()
		FTimerHandle SetUpdateKDAHandle;

	UPROPERTY()
		FTimerHandle SetGetPlayerKDAHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString PID;

	UPROPERTY()
		bool UsernameCheck = false;


protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
		ABattleMobaGameState* GState;

private:
	FHttpModule* HttpModule;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		UTextBlock* TeamNameTextBlock;

	UPROPERTY()
		UTextBlock* TimerTextBlock;

	UPROPERTY()
		UTextBlock* TeammateCountTextBlock;

	UPROPERTY()
		UTextBlock* EventTextBlock;

	UPROPERTY()
		UTextBlock* LatestEventTextBlock;

	UPROPERTY()
		UTextBlock* PingTextBlock;

	/*UFUNCTION()
		void SetTeammateCount();*/

	UFUNCTION()
		void SetLatestEvent();

	UFUNCTION()
		void GetPlayerKDA();

	UFUNCTION()
		void UpdatePlayerKDA();

	UPROPERTY()
		FString Kill;

	UPROPERTY()
		FString Death;

	UPROPERTY()
		FString Assist;

	UPROPERTY()
		FString Username;

	UPROPERTY()
		FString Win;

	UPROPERTY()
		FString Lose;

	UPROPERTY()
		int iKill;

	UPROPERTY()
		int iDeath;

	UPROPERTY()
		int iAssist;

	UPROPERTY()
		int iWin;

	UPROPERTY()
		int iLose;

	UPROPERTY()
		TSubclassOf<UUserWidget> GameWidgetClass;

	void OnGetPlayerKDAResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetUpdateKDAResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/*UFUNCTION()
		void SetAveragePlayerLatency();

	UFUNCTION()
		void SetCountdownTimer();*/
};

