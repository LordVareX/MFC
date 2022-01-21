/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/AdminResetUserPasswordRequest.h"

#endif


#include "AdminResetUserPasswordRequest.generated.h"

USTRUCT(BlueprintType)
struct FAdminResetUserPasswordRequest {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for the user pool where you want to reset the user's password.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The user name of the user whose password you wish to reset.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString username;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest awsAdminResetUserPasswordRequest;

        if (!(this->userPoolId.IsEmpty())) {
            awsAdminResetUserPasswordRequest.SetUserPoolId(TCHAR_TO_UTF8(*this->userPoolId));
        }

        if (!(this->username.IsEmpty())) {
            awsAdminResetUserPasswordRequest.SetUsername(TCHAR_TO_UTF8(*this->username));
        }

        return awsAdminResetUserPasswordRequest;
    }

    bool IsEmpty() const {
        return this->userPoolId.IsEmpty() && this->username.IsEmpty();
    }
#endif
};
