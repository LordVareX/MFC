/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/UpdateUserPoolClientRequest.h"

#endif

#include "Model/ExplicitAuthFlowsType.h"
#include "Model/OAuthFlowType.h"
#include "Model/AnalyticsConfigurationType.h"

#include "UpdateUserPoolClientRequest.generated.h"

USTRUCT(BlueprintType)
struct FUpdateUserPoolClientRequest {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for the user pool where you want to update the user pool client.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The ID of the client associated with the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientId;

    /**
    *  <p>The client name from the update user pool client request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientName;

    /**
    *  <p>The time limit, in days, after which the refresh token is no longer valid and cannot be used.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    int refreshTokenValidity;

    /**
    *  <p>The read-only attributes of the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> readAttributes;

    /**
    *  <p>The writeable attributes of the user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> writeAttributes;

    /**
    *  <p>Explicit authentication flows.</p>
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
    *  <p>Set to <code>code</code> to initiate a code grant flow, which provides an authorization code as the response. This code can be exchanged for access tokens with the token endpoint.</p>
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
    *  <p>The Amazon Pinpoint analytics configuration for collecting metrics for this user pool.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FAnalyticsConfigurationType analyticsConfiguration;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest awsUpdateUserPoolClientRequest;

        if (!(this->userPoolId.IsEmpty())) {
            awsUpdateUserPoolClientRequest.SetUserPoolId(TCHAR_TO_UTF8(*this->userPoolId));
        }

        if (!(this->clientId.IsEmpty())) {
            awsUpdateUserPoolClientRequest.SetClientId(TCHAR_TO_UTF8(*this->clientId));
        }

        if (!(this->clientName.IsEmpty())) {
            awsUpdateUserPoolClientRequest.SetClientName(TCHAR_TO_UTF8(*this->clientName));
        }

        if (!(this->refreshTokenValidity == 0)) {
            awsUpdateUserPoolClientRequest.SetRefreshTokenValidity(this->refreshTokenValidity);
        }

        for (const FString& elem : this->readAttributes) {
            awsUpdateUserPoolClientRequest.AddReadAttributes(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->writeAttributes) {
            awsUpdateUserPoolClientRequest.AddWriteAttributes(TCHAR_TO_UTF8(*elem));
        }

        for (const EExplicitAuthFlowsType& elem : this->explicitAuthFlows) {
            switch(elem) {
                case EExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH:
                    awsUpdateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH);
                    break;
                case EExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY:
                    awsUpdateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY);
                    break;
                case EExplicitAuthFlowsType::USER_PASSWORD_AUTH:
                    awsUpdateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::USER_PASSWORD_AUTH);
                    break;
                default:
                    break;
            };
        }

        for (const FString& elem : this->supportedIdentityProviders) {
            awsUpdateUserPoolClientRequest.AddSupportedIdentityProviders(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->callbackURLs) {
            awsUpdateUserPoolClientRequest.AddCallbackURLs(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->logoutURLs) {
            awsUpdateUserPoolClientRequest.AddLogoutURLs(TCHAR_TO_UTF8(*elem));
        }

        if (!(this->defaultRedirectURI.IsEmpty())) {
            awsUpdateUserPoolClientRequest.SetDefaultRedirectURI(TCHAR_TO_UTF8(*this->defaultRedirectURI));
        }

        for (const EOAuthFlowType& elem : this->allowedOAuthFlows) {
            switch(elem) {
                case EOAuthFlowType::code:
                    awsUpdateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::code);
                    break;
                case EOAuthFlowType::implicit:
                    awsUpdateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::implicit);
                    break;
                case EOAuthFlowType::client_credentials:
                    awsUpdateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::client_credentials);
                    break;
                default:
                    break;
            };
        }

        for (const FString& elem : this->allowedOAuthScopes) {
            awsUpdateUserPoolClientRequest.AddAllowedOAuthScopes(TCHAR_TO_UTF8(*elem));
        }

        if (!(false)) {
            awsUpdateUserPoolClientRequest.SetAllowedOAuthFlowsUserPoolClient(this->allowedOAuthFlowsUserPoolClient);
        }

        if (!(this->analyticsConfiguration.IsEmpty())) {
            awsUpdateUserPoolClientRequest.SetAnalyticsConfiguration(this->analyticsConfiguration.toAWS());
        }

        return awsUpdateUserPoolClientRequest;
    }

    bool IsEmpty() const {
        return this->userPoolId.IsEmpty() && this->clientId.IsEmpty() && this->clientName.IsEmpty() && this->refreshTokenValidity == 0 && this->readAttributes.Num() == 0 && this->writeAttributes.Num() == 0 && this->explicitAuthFlows.Num() == 0 && this->supportedIdentityProviders.Num() == 0 && this->callbackURLs.Num() == 0 && this->logoutURLs.Num() == 0 && this->defaultRedirectURI.IsEmpty() && this->allowedOAuthFlows.Num() == 0 && this->allowedOAuthScopes.Num() == 0 && false && this->analyticsConfiguration.IsEmpty();
    }
#endif
};
