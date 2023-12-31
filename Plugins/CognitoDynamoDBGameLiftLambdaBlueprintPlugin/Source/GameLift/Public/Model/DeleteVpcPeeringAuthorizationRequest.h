/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/DeleteVpcPeeringAuthorizationRequest.h"

#endif


#include "DeleteVpcPeeringAuthorizationRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteVpcPeeringAuthorizationRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for the AWS account that you use to manage your Amazon GameLift fleet. You can find your Account ID in the AWS Management Console under account settings.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameLiftAwsAccountId;

    /**
    *  <p>Unique identifier for a VPC with resources to be accessed by your Amazon GameLift fleet. The VPC must be in the same region where your fleet is deployed. Look up a VPC ID using the <a href="https://console.aws.amazon.com/vpc/">VPC Dashboard</a> in the AWS Management Console. Learn more about VPC peering in <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/vpc-peering.html">VPC Peering with Amazon GameLift Fleets</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString peerVpcId;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::DeleteVpcPeeringAuthorizationRequest toAWS() const {
        Aws::GameLift::Model::DeleteVpcPeeringAuthorizationRequest awsDeleteVpcPeeringAuthorizationRequest;

        if (!(this->gameLiftAwsAccountId.IsEmpty())) {
            awsDeleteVpcPeeringAuthorizationRequest.SetGameLiftAwsAccountId(TCHAR_TO_UTF8(*this->gameLiftAwsAccountId));
        }

        if (!(this->peerVpcId.IsEmpty())) {
            awsDeleteVpcPeeringAuthorizationRequest.SetPeerVpcId(TCHAR_TO_UTF8(*this->peerVpcId));
        }

        return awsDeleteVpcPeeringAuthorizationRequest;
    }

    bool IsEmpty() const {
        return this->gameLiftAwsAccountId.IsEmpty() && this->peerVpcId.IsEmpty();
    }
#endif
};
