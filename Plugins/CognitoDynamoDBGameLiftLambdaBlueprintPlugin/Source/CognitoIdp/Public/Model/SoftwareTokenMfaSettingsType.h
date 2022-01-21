/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/SoftwareTokenMfaSettingsType.h"

#endif


#include "SoftwareTokenMfaSettingsType.generated.h"

USTRUCT(BlueprintType)
struct FSoftwareTokenMfaSettingsType {
GENERATED_BODY()

    /**
    *  <p>Specifies whether software token MFA is enabled.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    bool enabled;

    /**
    *  <p>The preferred MFA method.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    bool preferredMfa;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType toAWS() const {
        Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType awsSoftwareTokenMfaSettingsType;

        if (!(false)) {
            awsSoftwareTokenMfaSettingsType.SetEnabled(this->enabled);
        }

        if (!(false)) {
            awsSoftwareTokenMfaSettingsType.SetPreferredMfa(this->preferredMfa);
        }

        return awsSoftwareTokenMfaSettingsType;
    }

    bool IsEmpty() const {
        return false && false;
    }
#endif
};
