/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE

#include "aws/cognito-idp/model/EmailConfigurationType.h"

#endif

#include "Model/EmailSendingAccountType.h"

#include "EmailConfigurationType.generated.h"

USTRUCT(BlueprintType)
struct FEmailConfigurationType {
GENERATED_BODY()

    /**
    *  <p>The Amazon Resource Name (ARN) of a verified email address in Amazon SES. This email address is used in one of the following ways, depending on the value that you specify for the <code>EmailSendingAccount</code> parameter:</p> <ul> <li> <p>If you specify <code>COGNITO_DEFAULT</code>, Amazon Cognito uses this address as the custom FROM address when it emails your users by using its built-in email account.</p> </li> <li> <p>If you specify <code>DEVELOPER</code>, Amazon Cognito emails your users with this address by calling Amazon SES on your behalf.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString sourceArn;

    /**
    *  <p>The destination to which the receiver of the email should reply to.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    FString replyToEmailAddress;

    /**
    *  <p>Specifies whether Amazon Cognito emails your users by using its built-in email functionality or your Amazon SES email configuration. Specify one of the following values:</p> <dl> <dt>COGNITO_DEFAULT</dt> <dd> <p>When Amazon Cognito emails your users, it uses its built-in email functionality. When you use the default option, Amazon Cognito allows only a limited number of emails each day for your user pool. For typical production environments, the default email limit is below the required delivery volume. To achieve a higher delivery volume, specify DEVELOPER to use your Amazon SES email configuration.</p> <p>To look up the email delivery limit for the default option, see <a href="https://docs.aws.amazon.com/cognito/latest/developerguide/limits.html">Limits in Amazon Cognito</a> in the <i>Amazon Cognito Developer Guide</i>.</p> <p>The default FROM address is no-reply@verificationemail.com. To customize the FROM address, provide the ARN of an Amazon SES verified email address for the <code>SourceArn</code> parameter.</p> </dd> <dt>DEVELOPER</dt> <dd> <p>When Amazon Cognito emails your users, it uses your Amazon SES configuration. Amazon Cognito calls Amazon SES on your behalf to send email from your verified email address. When you use this option, the email delivery limits are the same limits that apply to your Amazon SES verified email address in your AWS account.</p> <p>If you use this option, you must provide the ARN of an Amazon SES verified email address for the <code>SourceArn</code> parameter.</p> <p>Before Amazon Cognito can email your users, it requires additional permissions to call Amazon SES on your behalf. When you update your user pool with this option, Amazon Cognito creates a <i>service-linked role</i>, which is a type of IAM role, in your AWS account. This role contains the permissions that allow Amazon Cognito to access Amazon SES and send email messages with your address. For more information about the service-linked role that Amazon Cognito creates, see <a href="https://docs.aws.amazon.com/cognito/latest/developerguide/using-service-linked-roles.html">Using Service-Linked Roles for Amazon Cognito</a> in the <i>Amazon Cognito Developer Guide</i>.</p> </dd> </dl>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CognitoIdentityProvider Client")
    EEmailSendingAccountType emailSendingAccount;

#if WITH_COGNITOIDENTITYPROVIDERCLIENTSDK && WITH_CORE
public:
    Aws::CognitoIdentityProvider::Model::EmailConfigurationType toAWS() const {
        Aws::CognitoIdentityProvider::Model::EmailConfigurationType awsEmailConfigurationType;

        if (!(this->sourceArn.IsEmpty())) {
            awsEmailConfigurationType.SetSourceArn(TCHAR_TO_UTF8(*this->sourceArn));
        }

        if (!(this->replyToEmailAddress.IsEmpty())) {
            awsEmailConfigurationType.SetReplyToEmailAddress(TCHAR_TO_UTF8(*this->replyToEmailAddress));
        }

        switch(this->emailSendingAccount) {
            case EEmailSendingAccountType::COGNITO_DEFAULT:
                awsEmailConfigurationType.SetEmailSendingAccount(Aws::CognitoIdentityProvider::Model::EmailSendingAccountType::COGNITO_DEFAULT);
                break;
            case EEmailSendingAccountType::DEVELOPER:
                awsEmailConfigurationType.SetEmailSendingAccount(Aws::CognitoIdentityProvider::Model::EmailSendingAccountType::DEVELOPER);
                break;
            default:
                break;
        }

        return awsEmailConfigurationType;
    }

    bool IsEmpty() const {
        return this->sourceArn.IsEmpty() && this->replyToEmailAddress.IsEmpty() && this->emailSendingAccount == EEmailSendingAccountType::NOT_SET;
    }

    FEmailConfigurationType &fromAWS(const Aws::CognitoIdentityProvider::Model::EmailConfigurationType &awsEmailConfigurationType) {
        this->sourceArn = UTF8_TO_TCHAR(awsEmailConfigurationType.GetSourceArn().c_str());

        this->replyToEmailAddress = UTF8_TO_TCHAR(awsEmailConfigurationType.GetReplyToEmailAddress().c_str());

        switch(awsEmailConfigurationType.GetEmailSendingAccount()) {
            case Aws::CognitoIdentityProvider::Model::EmailSendingAccountType::NOT_SET:
                this->emailSendingAccount = EEmailSendingAccountType::NOT_SET;
                break;
            case Aws::CognitoIdentityProvider::Model::EmailSendingAccountType::COGNITO_DEFAULT:
                this->emailSendingAccount = EEmailSendingAccountType::COGNITO_DEFAULT;
                break;
            case Aws::CognitoIdentityProvider::Model::EmailSendingAccountType::DEVELOPER:
                this->emailSendingAccount = EEmailSendingAccountType::DEVELOPER;
                break;
            default:
                this->emailSendingAccount = EEmailSendingAccountType::NOT_SET;
                break;
        }

        return *this;
    }
#endif
};
