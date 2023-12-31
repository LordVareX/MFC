/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/ProviderDescription.h"

#endif

#include "Model/IdentityProviderTypeType.h"

#include "ProviderDescription.generated.h"

USTRUCT(BlueprintType)
struct FProviderDescription {
GENERATED_BODY()

    /**
    *  <p>The identity provider name.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString providerName;

    /**
    *  <p>The identity provider type.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    EIdentityProviderTypeType providerType;

    /**
    *  <p>The date the provider was last modified.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime lastModifiedDate;

    /**
    *  <p>The date the provider was added to the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime creationDate;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    FProviderDescription &fromAWS(const Aws::CognitoIdentityProvider::Model::ProviderDescription &awsProviderDescription) {
        this->providerName = UTF8_TO_TCHAR(awsProviderDescription.GetProviderName().c_str());

        switch(awsProviderDescription.GetProviderType()) {
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::NOT_SET:
                this->providerType = EIdentityProviderTypeType::NOT_SET;
                break;
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::SAML:
                this->providerType = EIdentityProviderTypeType::SAML;
                break;
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::Facebook:
                this->providerType = EIdentityProviderTypeType::Facebook;
                break;
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::Google:
                this->providerType = EIdentityProviderTypeType::Google;
                break;
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::LoginWithAmazon:
                this->providerType = EIdentityProviderTypeType::LoginWithAmazon;
                break;
            case Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType::OIDC:
                this->providerType = EIdentityProviderTypeType::OIDC;
                break;
            default:
                this->providerType = EIdentityProviderTypeType::NOT_SET;
                break;
        }

        this->lastModifiedDate = FDateTime::FromUnixTimestamp(awsProviderDescription.GetLastModifiedDate().Millis());

        this->creationDate = FDateTime::FromUnixTimestamp(awsProviderDescription.GetCreationDate().Millis());

        return *this;
    }
#endif
};
