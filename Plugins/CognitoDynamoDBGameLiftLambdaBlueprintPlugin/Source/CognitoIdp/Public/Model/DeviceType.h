/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/DeviceType.h"

#endif

#include "Model/AttributeType.h"

#include "DeviceType.generated.h"

USTRUCT(BlueprintType)
struct FDeviceType {
GENERATED_BODY()

    /**
    *  <p>The device key.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString deviceKey;

    /**
    *  <p>The device attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FAttributeType> deviceAttributes;

    /**
    *  <p>The creation date of the device.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime deviceCreateDate;

    /**
    *  <p>The last modified date of the device.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime deviceLastModifiedDate;

    /**
    *  <p>The date in which the device was last authenticated.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime deviceLastAuthenticatedDate;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    FDeviceType &fromAWS(const Aws::CognitoIdentityProvider::Model::DeviceType &awsDeviceType) {
        this->deviceKey = UTF8_TO_TCHAR(awsDeviceType.GetDeviceKey().c_str());

        this->deviceAttributes.Empty();
        for (const Aws::CognitoIdentityProvider::Model::AttributeType& elem : awsDeviceType.GetDeviceAttributes()) {
            this->deviceAttributes.Add(FAttributeType().fromAWS(elem));
        }

        this->deviceCreateDate = FDateTime::FromUnixTimestamp(awsDeviceType.GetDeviceCreateDate().Millis());

        this->deviceLastModifiedDate = FDateTime::FromUnixTimestamp(awsDeviceType.GetDeviceLastModifiedDate().Millis());

        this->deviceLastAuthenticatedDate = FDateTime::FromUnixTimestamp(awsDeviceType.GetDeviceLastAuthenticatedDate().Millis());

        return *this;
    }
#endif
};
