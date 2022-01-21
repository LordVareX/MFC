/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/UserPoolClientType.h"

#endif

#include "Model/ExplicitAuthFlowsType.h"
#include "Model/OAuthFlowType.h"
#include "Model/AnalyticsConfigurationType.h"

#include "UserPoolClientType.generated.h"

USTRUCT(BlueprintType)
struct FUserPoolClientType {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for the user pool client.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The client name from the user pool request of the client type.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientName;

    /**
    *  <p>The ID of the client associated with the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientId;

    /**
    *  <p>The client secret from the user pool request of the client type.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientSecret;

    /**
    *  <p>The date the user pool client was last modified.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime lastModifiedDate;

    /**
    *  <p>The date the user pool client was created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FDateTime creationDate;

    /**
    *  <p>The time limit, in days, after which the refresh token is no longer valid and cannot be used.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    int refreshTokenValidity;

    /**
    *  <p>The Read-only attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> readAttributes;

    /**
    *  <p>The writeable attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> writeAttributes;

    /**
    *  <p>The explicit authentication flows.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<EExplicitAuthFlowsType> explicitAuthFlows;

    /**
    *  <p>A list of provider names for the identity providers that are supported on this client.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> supportedIdentityProviders;

    /**
    *  <p>A list of allowed redirect (callback) URLs for the identity providers.</p> <p>A redirect URI must:</p> <ul> <li> <p>Be an absolute URI.</p> </li> <li> <p>Be registered with the authorization server.</p> </li> <li> <p>Not include a fragment component.</p> </li> </ul> <p>See <a href="https://tools.ietf.org/html/rfc6749#section-3.1.2">OAuth 2.0 - Redirection Endpoint</a>.</p> <p>Amazon Cognito requires HTTPS over HTTP except for http://localhost for testing purposes only.</p> <p>App callback URLs such as myapp://example are also supported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> callbackURLs;

    /**
    *  <p>A list of allowed logout URLs for the identity providers.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> logoutURLs;

    /**
    *  <p>The default redirect URI. Must be in the <code>CallbackURLs</code> list.</p> <p>A redirect URI must:</p> <ul> <li> <p>Be an absolute URI.</p> </li> <li> <p>Be registered with the authorization server.</p> </li> <li> <p>Not include a fragment component.</p> </li> </ul> <p>See <a href="https://tools.ietf.org/html/rfc6749#section-3.1.2">OAuth 2.0 - Redirection Endpoint</a>.</p> <p>Amazon Cognito requires HTTPS over HTTP except for http://localhost for testing purposes only.</p> <p>App callback URLs such as myapp://example are also supported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString defaultRedirectURI;

    /**
    *  <p>Set to <code>code</code> to initiate a code grant flow, which provides an authorization code as the response. This code can be exchanged for access tokens with the token endpoint.</p> <p>Set to <code>token</code> to specify that the client should get the access token (and, optionally, ID token, based on scopes) directly.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<EOAuthFlowType> allowedOAuthFlows;

    /**
    *  <p>A list of allowed <code>OAuth</code> scopes. Currently supported values are <code>"phone"</code>, <code>"email"</code>, <code>"openid"</code>, and <code>"Cognito"</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> allowedOAuthScopes;

    /**
    *  <p>Set to TRUE if the client is allowed to follow the OAuth protocol when interacting with Cognito user pools.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    bool allowedOAuthFlowsUserPoolClient;

    /**
    *  <p>The Amazon Pinpoint analytics configuration for the user pool client.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FAnalyticsConfigurationType analyticsConfiguration;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    FUserPoolClientType &fromAWS(const Aws::CognitoIdentityProvider::Model::UserPoolClientType &awsUserPoolClientType) {
        this->userPoolId = UTF8_TO_TCHAR(awsUserPoolClientType.GetUserPoolId().c_str());

        this->clientName = UTF8_TO_TCHAR(awsUserPoolClientType.GetClientName().c_str());

        this->clientId = UTF8_TO_TCHAR(awsUserPoolClientType.GetClientId().c_str());

        this->clientSecret = UTF8_TO_TCHAR(awsUserPoolClientType.GetClientSecret().c_str());

        this->lastModifiedDate = FDateTime::FromUnixTimestamp(awsUserPoolClientType.GetLastModifiedDate().Millis());

        this->creationDate = FDateTime::FromUnixTimestamp(awsUserPoolClientType.GetCreationDate().Millis());

        this->refreshTokenValidity = awsUserPoolClientType.GetRefreshTokenValidity();

        this->readAttributes.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetReadAttributes()) {
            this->readAttributes.Add(elem.c_str());
        }

        this->writeAttributes.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetWriteAttributes()) {
            this->writeAttributes.Add(elem.c_str());
        }

        this->explicitAuthFlows.Empty();
        for (const Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType& elem : awsUserPoolClientType.GetExplicitAuthFlows()) {
            switch(elem) {
                case Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::NOT_SET:
                    this->explicitAuthFlows.Add(EExplicitAuthFlowsType::NOT_SET);
                    break;
                case Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH:
                    this->explicitAuthFlows.Add(EExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH);
                    break;
                case Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY:
                    this->explicitAuthFlows.Add(EExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY);
                    break;
                case Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::USER_PASSWORD_AUTH:
                    this->explicitAuthFlows.Add(EExplicitAuthFlowsType::USER_PASSWORD_AUTH);
                    break;
                default:
                    this->explicitAuthFlows.Add(EExplicitAuthFlowsType::NOT_SET);
                    break;
            };
        }

        this->supportedIdentityProviders.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetSupportedIdentityProviders()) {
            this->supportedIdentityProviders.Add(elem.c_str());
        }

        this->callbackURLs.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetCallbackURLs()) {
            this->callbackURLs.Add(elem.c_str());
        }

        this->logoutURLs.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetLogoutURLs()) {
            this->logoutURLs.Add(elem.c_str());
        }

        this->defaultRedirectURI = UTF8_TO_TCHAR(awsUserPoolClientType.GetDefaultRedirectURI().c_str());

        this->allowedOAuthFlows.Empty();
        for (const Aws::CognitoIdentityProvider::Model::OAuthFlowType& elem : awsUserPoolClientType.GetAllowedOAuthFlows()) {
            switch(elem) {
                case Aws::CognitoIdentityProvider::Model::OAuthFlowType::NOT_SET:
                    this->allowedOAuthFlows.Add(EOAuthFlowType::NOT_SET);
                    break;
                case Aws::CognitoIdentityProvider::Model::OAuthFlowType::code:
                    this->allowedOAuthFlows.Add(EOAuthFlowType::code);
                    break;
                case Aws::CognitoIdentityProvider::Model::OAuthFlowType::implicit:
                    this->allowedOAuthFlows.Add(EOAuthFlowType::implicit);
                    break;
                case Aws::CognitoIdentityProvider::Model::OAuthFlowType::client_credentials:
                    this->allowedOAuthFlows.Add(EOAuthFlowType::client_credentials);
                    break;
                default:
                    this->allowedOAuthFlows.Add(EOAuthFlowType::NOT_SET);
                    break;
            };
        }

        this->allowedOAuthScopes.Empty();
        for (const Aws::String& elem : awsUserPoolClientType.GetAllowedOAuthScopes()) {
            this->allowedOAuthScopes.Add(elem.c_str());
        }

        this->allowedOAuthFlowsUserPoolClient = awsUserPoolClientType.GetAllowedOAuthFlowsUserPoolClient();

        this->analyticsConfiguration.fromAWS(awsUserPoolClientType.GetAnalyticsConfiguration());

        return *this;
    }
#endif
};
