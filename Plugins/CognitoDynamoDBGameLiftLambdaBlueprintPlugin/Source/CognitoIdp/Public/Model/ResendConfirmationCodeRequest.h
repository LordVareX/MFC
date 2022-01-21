/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/ResendConfirmationCodeRequest.h"

#endif

#include "Model/UserContextDataType.h"
#include "Model/AnalyticsMetadataType.h"

#include "ResendConfirmationCodeRequest.generated.h"

USTRUCT(BlueprintType)
struct FResendConfirmationCodeRequest {
GENERATED_BODY()

    /**
    *  <p>The ID of the client associated with the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientId;

    /**
    *  <p>A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString secretHash;

    /**
    *  <p>Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FUserContextDataType userContextData;

    /**
    *  <p>The user name of the user to whom you wish to resend a confirmation code.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString username;

    /**
    *  <p>The Amazon Pinpoint analytics metadata for collecting metrics for <code>ResendConfirmationCode</code> calls.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FAnalyticsMetadataType analyticsMetadata;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest awsResendConfirmationCodeRequest;

        if (!(this->clientId.IsEmpty())) {
            awsResendConfirmationCodeRequest.SetClientId(TCHAR_TO_UTF8(*this->clientId));
        }

        if (!(this->secretHash.IsEmpty())) {
            awsResendConfirmationCodeRequest.SetSecretHash(TCHAR_TO_UTF8(*this->secretHash));
        }

        if (!(this->userContextData.IsEmpty())) {
            awsResendConfirmationCodeRequest.SetUserContextData(this->userContextData.toAWS());
        }

        if (!(this->username.IsEmpty())) {
            awsResendConfirmationCodeRequest.SetUsername(TCHAR_TO_UTF8(*this->username));
        }

        if (!(this->analyticsMetadata.IsEmpty())) {
            awsResendConfirmationCodeRequest.SetAnalyticsMetadata(this->analyticsMetadata.toAWS());
        }

        return awsResendConfirmationCodeRequest;
    }

    bool IsEmpty() const {
        return this->clientId.IsEmpty() && this->secretHash.IsEmpty() && this->userContextData.IsEmpty() && this->username.IsEmpty() && this->analyticsMetadata.IsEmpty();
    }
#endif
};
