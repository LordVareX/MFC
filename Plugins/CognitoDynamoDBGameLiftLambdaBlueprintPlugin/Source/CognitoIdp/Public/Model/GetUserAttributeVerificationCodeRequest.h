/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/GetUserAttributeVerificationCodeRequest.h"

#endif


#include "GetUserAttributeVerificationCodeRequest.generated.h"

USTRUCT(BlueprintType)
struct FGetUserAttributeVerificationCodeRequest {
GENERATED_BODY()

    /**
    *  <p>The access token returned by the server response to get the user attribute verification code.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString accessToken;

    /**
    *  <p>The attribute name returned by the server response to get the user attribute verification code.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString attributeName;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest awsGetUserAttributeVerificationCodeRequest;

        if (!(this->accessToken.IsEmpty())) {
            awsGetUserAttributeVerificationCodeRequest.SetAccessToken(TCHAR_TO_UTF8(*this->accessToken));
        }

        if (!(this->attributeName.IsEmpty())) {
            awsGetUserAttributeVerificationCodeRequest.SetAttributeName(TCHAR_TO_UTF8(*this->attributeName));
        }

        return awsGetUserAttributeVerificationCodeRequest;
    }

    bool IsEmpty() const {
        return this->accessToken.IsEmpty() && this->attributeName.IsEmpty();
    }
#endif
};
