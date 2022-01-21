/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/AdminUpdateUserAttributesRequest.h"

#endif

#include "Model/AttributeType.h"

#include "AdminUpdateUserAttributesRequest.generated.h"

USTRUCT(BlueprintType)
struct FAdminUpdateUserAttributesRequest {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for the user pool where you want to update user attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The user name of the user for whom you want to update user attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString username;

    /**
    *  <p>An array of name-value pairs representing user attributes.</p> <p>For custom attributes, you must prepend the <code>custom:</code> prefix to the attribute name.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FAttributeType> userAttributes;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest awsAdminUpdateUserAttributesRequest;

        if (!(this->userPoolId.IsEmpty())) {
            awsAdminUpdateUserAttributesRequest.SetUserPoolId(TCHAR_TO_UTF8(*this->userPoolId));
        }

        if (!(this->username.IsEmpty())) {
            awsAdminUpdateUserAttributesRequest.SetUsername(TCHAR_TO_UTF8(*this->username));
        }

        for (const FAttributeType& elem : this->userAttributes) {
            awsAdminUpdateUserAttributesRequest.AddUserAttributes(elem.toAWS());
        }

        return awsAdminUpdateUserAttributesRequest;
    }

    bool IsEmpty() const {
        return this->userPoolId.IsEmpty() && this->username.IsEmpty() && this->userAttributes.Num() == 0;
    }
#endif
};
