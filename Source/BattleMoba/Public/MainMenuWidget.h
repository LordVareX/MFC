// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "MainMenuWidget.generated.h"

class UWebBrowser;
class UButton;
class UTextBlock;
class UCanvasPanel;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class BATTLEMOBA_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
		FTimerHandle SetAveragePlayerLatencyHandle;

	UPROPERTY()
		FTimerHandle PollMatchmakingHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UsernameRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UsernameCheck = false;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
private:

	FHttpModule* HttpModule;

	UPROPERTY()
		FString LoginUrl;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		FString CallbackUrl;

	UPROPERTY()
		FString RegionCode;



	UPROPERTY()
		FString IdRef;

	UPROPERTY()
		FString Id;

	UPROPERTY()
		FString Wins;

	UPROPERTY()
		FString Losses;

	UPROPERTY()
		FString Username;

	UPROPERTY()
		FString Kill;

	UPROPERTY()
		FString Death;

	UPROPERTY()
		FString Assist;

	UPROPERTY()
		UWebBrowser* WebBrowser;

	UPROPERTY()
		UButton* MatchmakingButton;

	UPROPERTY()
		UTextBlock* WinsTextBlock;

	UPROPERTY()
		UTextBlock* LossesTextBlock;

	UPROPERTY()
		UTextBlock* PingTextBlock;

	UPROPERTY()
		UTextBlock* ErrorTextBlock;

	/*UPROPERTY()
		UTextBlock* MatchmakingEventTextBlock;*/

	UPROPERTY()
		UTextBlock* UsernameTextBlock;

	/*UPROPERTY()
		UTextBlock* PNTextBlock;*/

	UPROPERTY()
		UTextBlock* KillTextBlock;

	UPROPERTY()
		UTextBlock* DeathTextBlock;

	UPROPERTY()
		UTextBlock* AssistTextBlock;

	UPROPERTY()
		UCanvasPanel* NameCanvasPanel;

	UPROPERTY()
		UEditableTextBox* NameEditableTextBox;

	UPROPERTY()
		UButton* CreateNameButton;

	UPROPERTY()
		float AveragePlayerLatency;

	UPROPERTY()
		bool SearchingForGame;

	UFUNCTION()
		void HandleLoginUrlChange();

	UFUNCTION()
		void SetAveragePlayerLatency();

	UFUNCTION()
		void OnMatchmakingButtonClicked();

	UFUNCTION()
		void OnCreateNameButtonClicked();

	UFUNCTION()
		void PollMatchmaking();

	void OnExchangeCodeForTokensResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetPlayerDataResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnStartMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnStopMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnPollMatchmakingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnCreateNameButtonClickedResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
