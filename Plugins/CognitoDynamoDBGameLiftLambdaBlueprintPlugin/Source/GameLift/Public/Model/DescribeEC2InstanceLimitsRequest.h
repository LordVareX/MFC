/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/DescribeEC2InstanceLimitsRequest.h"

#endif

#include "Model/EC2InstanceType.h"

#include "DescribeEC2InstanceLimitsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeEC2InstanceLimitsRequest {
GENERATED_BODY()

    /**
    *  <p>Name of an EC2 instance type that is supported in Amazon GameLift. A fleet instance type determines the computing resources of each instance in the fleet, including CPU, memory, storage, and networking capacity. Amazon GameLift supports the following EC2 instance types. See <a href="http://aws.amazon.com/ec2/instance-types/">Amazon EC2 Instance Types</a> for detailed descriptions. Leave this parameter blank to retrieve limits for all types.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EEC2InstanceType eC2InstanceType;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::DescribeEC2InstanceLimitsRequest toAWS() const {
        Aws::GameLift::Model::DescribeEC2InstanceLimitsRequest awsDescribeEC2InstanceLimitsRequest;

        switch(this->eC2InstanceType) {
            case EEC2InstanceType::t2_micro:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_micro);
                break;
            case EEC2InstanceType::t2_small:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_small);
                break;
            case EEC2InstanceType::t2_medium:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_medium);
                break;
            case EEC2InstanceType::t2_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_large);
                break;
            case EEC2InstanceType::c3_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_large);
                break;
            case EEC2InstanceType::c3_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_xlarge);
                break;
            case EEC2InstanceType::c3_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_2xlarge);
                break;
            case EEC2InstanceType::c3_4xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_4xlarge);
                break;
            case EEC2InstanceType::c3_8xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_8xlarge);
                break;
            case EEC2InstanceType::c4_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_large);
                break;
            case EEC2InstanceType::c4_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_xlarge);
                break;
            case EEC2InstanceType::c4_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_2xlarge);
                break;
            case EEC2InstanceType::c4_4xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_4xlarge);
                break;
            case EEC2InstanceType::c4_8xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_8xlarge);
                break;
            case EEC2InstanceType::r3_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_large);
                break;
            case EEC2InstanceType::r3_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_xlarge);
                break;
            case EEC2InstanceType::r3_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_2xlarge);
                break;
            case EEC2InstanceType::r3_4xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_4xlarge);
                break;
            case EEC2InstanceType::r3_8xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_8xlarge);
                break;
            case EEC2InstanceType::r4_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_large);
                break;
            case EEC2InstanceType::r4_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_xlarge);
                break;
            case EEC2InstanceType::r4_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_2xlarge);
                break;
            case EEC2InstanceType::r4_4xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_4xlarge);
                break;
            case EEC2InstanceType::r4_8xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_8xlarge);
                break;
            case EEC2InstanceType::r4_16xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_16xlarge);
                break;
            case EEC2InstanceType::m3_medium:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_medium);
                break;
            case EEC2InstanceType::m3_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_large);
                break;
            case EEC2InstanceType::m3_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_xlarge);
                break;
            case EEC2InstanceType::m3_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_2xlarge);
                break;
            case EEC2InstanceType::m4_large:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_large);
                break;
            case EEC2InstanceType::m4_xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_xlarge);
                break;
            case EEC2InstanceType::m4_2xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_2xlarge);
                break;
            case EEC2InstanceType::m4_4xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_4xlarge);
                break;
            case EEC2InstanceType::m4_10xlarge:
                awsDescribeEC2InstanceLimitsRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_10xlarge);
                break;
            default:
                break;
        }

        return awsDescribeEC2InstanceLimitsRequest;
    }

    bool IsEmpty() const {
        return this->eC2InstanceType == EEC2InstanceType::NOT_SET;
    }
#endif
};
