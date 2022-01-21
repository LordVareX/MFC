/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/UpdateUserAttributesRequest.h"

#endif

#include "Model/AttributeType.h"

#include "UpdateUserAttributesRequest.generated.h"

USTRUCT(BlueprintType)
struct FUpdateUserAttributesRequest {
GENERATED_BODY()

    /**
    *  <p>An array of name-value pairs representing user attributes.</p> <p>For custom attributes, you must prepend the <code>custom:</code> prefix to the attribute name.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FAttributeType> userAttributes;

    /**
    *  <p>The access token for the request to update user attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString accessToken;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest awsUpdateUserAttributesRequest;

        for (const FAttributeType& elem : this->userAttributes) {
            awsUpdateUserAttributesRequest.AddUserAttributes(elem.toAWS());
        }

        if (!(this->accessToken.IsEmpty())) {
            awsUpdateUserAttributesRequest.SetAccessToken(TCHAR_TO_UTF8(*this->accessToken));
        }

        return awsUpdateUserAttributesRequest;
    }

    bool IsEmpty() const {
        return this->userAttributes.Num() == 0 && this->accessToken.IsEmpty();
    }
#endif
};
