/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/AdminConfirmSignUpRequest.h"

#endif


#include "AdminConfirmSignUpRequest.generated.h"

USTRUCT(BlueprintType)
struct FAdminConfirmSignUpRequest {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for which you want to confirm user registration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The user name for which you want to confirm user registration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString username;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest awsAdminConfirmSignUpRequest;

        if (!(this->userPoolId.IsEmpty())) {
            awsAdminConfirmSignUpRequest.SetUserPoolId(TCHAR_TO_UTF8(*this->userPoolId));
        }

        if (!(this->username.IsEmpty())) {
            awsAdminConfirmSignUpRequest.SetUsername(TCHAR_TO_UTF8(*this->username));
        }

        return awsAdminConfirmSignUpRequest;
    }

    bool IsEmpty() const {
        return this->userPoolId.IsEmpty() && this->username.IsEmpty();
    }
#endif
};
