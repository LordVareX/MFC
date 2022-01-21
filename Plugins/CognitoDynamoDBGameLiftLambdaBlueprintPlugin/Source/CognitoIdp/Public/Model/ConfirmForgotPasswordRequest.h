/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/ConfirmForgotPasswordRequest.h"

#endif

#include "Model/AnalyticsMetadataType.h"
#include "Model/UserContextDataType.h"

#include "ConfirmForgotPasswordRequest.generated.h"

USTRUCT(BlueprintType)
struct FConfirmForgotPasswordRequest {
GENERATED_BODY()

    /**
    *  <p>The app client ID of the app associated with the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientId;

    /**
    *  <p>A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString secretHash;

    /**
    *  <p>The user name of the user for whom you want to enter a code to retrieve a forgotten password.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString username;

    /**
    *  <p>The confirmation code sent by a user's request to retrieve a forgotten password. For more information, see </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString confirmationCode;

    /**
    *  <p>The password sent by a user's request to retrieve a forgotten password.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString password;

    /**
    *  <p>The Amazon Pinpoint analytics metadata for collecting metrics for <code>ConfirmForgotPassword</code> calls.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FAnalyticsMetadataType analyticsMetadata;

    /**
    *  <p>Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FUserContextDataType userContextData;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest awsConfirmForgotPasswordRequest;

        if (!(this->clientId.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetClientId(TCHAR_TO_UTF8(*this->clientId));
        }

        if (!(this->secretHash.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetSecretHash(TCHAR_TO_UTF8(*this->secretHash));
        }

        if (!(this->username.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetUsername(TCHAR_TO_UTF8(*this->username));
        }

        if (!(this->confirmationCode.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetConfirmationCode(TCHAR_TO_UTF8(*this->confirmationCode));
        }

        if (!(this->password.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetPassword(TCHAR_TO_UTF8(*this->password));
        }

        if (!(this->analyticsMetadata.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetAnalyticsMetadata(this->analyticsMetadata.toAWS());
        }

        if (!(this->userContextData.IsEmpty())) {
            awsConfirmForgotPasswordRequest.SetUserContextData(this->userContextData.toAWS());
        }

        return awsConfirmForgotPasswordRequest;
    }

    bool IsEmpty() const {
        return this->clientId.IsEmpty() && this->secretHash.IsEmpty() && this->username.IsEmpty() && this->confirmationCode.IsEmpty() && this->password.IsEmpty() && this->analyticsMetadata.IsEmpty() && this->userContextData.IsEmpty();
    }
#endif
};
