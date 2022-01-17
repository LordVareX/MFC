// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InputLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BattleMobaGameInstance.generated.h"
/**
 *
 */
UCLASS()
class BATTLEMOBA_API UBattleMobaGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* RewardTable;

public:
	UBattleMobaGameInstance();

	virtual void Shutdown() override;

	virtual void Init() override;

	UPROPERTY()
		FString AccessToken;

	UPROPERTY()
		FString IdToken;

	UPROPERTY()
		FString RefreshToken;

	UPROPERTY()
		FString MatchmakingTicketId;

	UPROPERTY()
		FTimerHandle RetrieveNewTokensHandle;

	UPROPERTY()
		FTimerHandle GetResponseTimeHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerId;// = "b55fb4bb-62ff-449f-a9c9-0aed93722d90";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Username;//= "VareX";

	TDoubleLinkedList<float> PlayerLatencies;

	UFUNCTION()
		void SetCognitoTokens(FString NewAccessToken, FString NewIdToken, FString NewRefreshToken);

	//Get row from Rewards datatable
	FRewards* GetRewardsData(FName& rowName, int rowIndex);

private:
	FHttpModule* HttpModule;

	UPROPERTY()
		FString ApiUrl;

	UPROPERTY()
		FString RegionCode;

	UFUNCTION()
		void RetrieveNewTokens();

	UFUNCTION()
		void GetResponseTime();

	void OnRetrieveNewTokensResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetResponseTimeResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
