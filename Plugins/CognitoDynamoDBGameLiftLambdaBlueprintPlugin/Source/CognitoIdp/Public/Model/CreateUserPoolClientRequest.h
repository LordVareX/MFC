/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/CreateUserPoolClientRequest.h"

#endif

#include "Model/ExplicitAuthFlowsType.h"
#include "Model/OAuthFlowType.h"
#include "Model/AnalyticsConfigurationType.h"

#include "CreateUserPoolClientRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateUserPoolClientRequest {
GENERATED_BODY()

    /**
    *  <p>The user pool ID for the user pool where you want to create a user pool client.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString userPoolId;

    /**
    *  <p>The client name for the user pool client you would like to create.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString clientName;

    /**
    *  <p>Boolean to specify whether you want to generate a secret for the user pool client being created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    bool generateSecret;

    /**
    *  <p>The time limit, in days, after which the refresh token is no longer valid and cannot be used.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    int refreshTokenValidity;

    /**
    *  <p>The read attributes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> readAttributes;

    /**
    *  <p>The user pool attributes that the app client can write to.</p> <p>If your app client allows users to sign in through an identity provider, this array must include all attributes that are mapped to identity provider attributes. Amazon Cognito updates mapped attributes when users sign in to your application through an identity provider. If your app client lacks write access to a mapped attribute, Amazon Cognito throws an error when it attempts to update the attribute. For more information, see <a href="https://docs.aws.amazon.com/cognito/latest/developerguide/cognito-user-pools-specifying-attribute-mapping.html">Specifying Identity Provider Attribute Mappings for Your User Pool</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<FString> writeAttributes;

    /**
    *  <p>The explicit authentication flows.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    TArray<EExplicitAuthFlowsType> explicitAuthFlows;

    /**
    *  <p>A list of provider names for the identity providers that are supported on this client. The following are supported: <code>COGNITO</code>, <code>Facebook</code>, <code>Google</code> and <code>LoginWithAmazon</code>.</p>
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
    *  <p>Set to <code>True</code> if the client is allowed to follow the OAuth protocol when interacting with Cognito user pools.</p>
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
    Aws::CognitoIdentityProvider::Model::CreateUserPoolClientRequest toAWS() const {
        Aws::CognitoIdentityProvider::Model::CreateUserPoolClientRequest awsCreateUserPoolClientRequest;

        if (!(this->userPoolId.IsEmpty())) {
            awsCreateUserPoolClientRequest.SetUserPoolId(TCHAR_TO_UTF8(*this->userPoolId));
        }

        if (!(this->clientName.IsEmpty())) {
            awsCreateUserPoolClientRequest.SetClientName(TCHAR_TO_UTF8(*this->clientName));
        }

        if (!(false)) {
            awsCreateUserPoolClientRequest.SetGenerateSecret(this->generateSecret);
        }

        if (this->refreshTokenValidity != 0) {
            awsCreateUserPoolClientRequest.SetRefreshTokenValidity(this->refreshTokenValidity);
        }

        for (const FString& elem : this->readAttributes) {
            awsCreateUserPoolClientRequest.AddReadAttributes(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->writeAttributes) {
            awsCreateUserPoolClientRequest.AddWriteAttributes(TCHAR_TO_UTF8(*elem));
        }

        for (const EExplicitAuthFlowsType& elem : this->explicitAuthFlows) {
            switch(elem) {
                case EExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH:
                    awsCreateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::ADMIN_NO_SRP_AUTH);
                    break;
                case EExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY:
                    awsCreateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::CUSTOM_AUTH_FLOW_ONLY);
                    break;
                case EExplicitAuthFlowsType::USER_PASSWORD_AUTH:
                    awsCreateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType::USER_PASSWORD_AUTH);
                    break;
                default:
                    break;
            };
        }

        for (const FString& elem : this->supportedIdentityProviders) {
            awsCreateUserPoolClientRequest.AddSupportedIdentityProviders(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->callbackURLs) {
            awsCreateUserPoolClientRequest.AddCallbackURLs(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->logoutURLs) {
            awsCreateUserPoolClientRequest.AddLogoutURLs(TCHAR_TO_UTF8(*elem));
        }

        if (!(this->defaultRedirectURI.IsEmpty())) {
            awsCreateUserPoolClientRequest.SetDefaultRedirectURI(TCHAR_TO_UTF8(*this->defaultRedirectURI));
        }

        for (const EOAuthFlowType& elem : this->allowedOAuthFlows) {
            switch(elem) {
                case EOAuthFlowType::code:
                    awsCreateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::code);
                    break;
                case EOAuthFlowType::implicit:
                    awsCreateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::implicit);
                    break;
                case EOAuthFlowType::client_credentials:
                    awsCreateUserPoolClientRequest.AddAllowedOAuthFlows(Aws::CognitoIdentityProvider::Model::OAuthFlowType::client_credentials);
                    break;
                default:
                    break;
            };
        }

        for (const FString& elem : this->allowedOAuthScopes) {
            awsCreateUserPoolClientRequest.AddAllowedOAuthScopes(TCHAR_TO_UTF8(*elem));
        }

        if (!(false)) {
            awsCreateUserPoolClientRequest.SetAllowedOAuthFlowsUserPoolClient(this->allowedOAuthFlowsUserPoolClient);
        }


        if (!(this->analyticsConfiguration.IsEmpty())) {
            awsCreateUserPoolClientRequest.SetAnalyticsConfiguration(this->analyticsConfiguration.toAWS());
        }

        return awsCreateUserPoolClientRequest;
    }

    bool IsEmpty() const {
        return this->userPoolId.IsEmpty() && this->clientName.IsEmpty() && false && this->refreshTokenValidity == 0 && this->readAttributes.Num() == 0 && this->writeAttributes.Num() == 0 && this->explicitAuthFlows.Num() == 0 && this->supportedIdentityProviders.Num() == 0 && this->callbackURLs.Num() == 0 && this->logoutURLs.Num() == 0 && this->defaultRedirectURI.IsEmpty() && this->allowedOAuthFlows.Num() == 0 && this->allowedOAuthScopes.Num() == 0 && false && this->analyticsConfiguration.IsEmpty();
    }
#endif
};
