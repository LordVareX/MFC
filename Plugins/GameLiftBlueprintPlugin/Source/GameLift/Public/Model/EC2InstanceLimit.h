/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/EC2InstanceLimit.h"

#endif

#include "Model/EC2InstanceType.h"

#include "EC2InstanceLimit.generated.h"

USTRUCT(BlueprintType)
struct FEC2InstanceLimit {
GENERATED_BODY()

    /**
    *  <p>Name of an EC2 instance type that is supported in Amazon GameLift. A fleet instance type determines the computing resources of each instance in the fleet, including CPU, memory, storage, and networking capacity. Amazon GameLift supports the following EC2 instance types. See <a href="http://aws.amazon.com/ec2/instance-types/">Amazon EC2 Instance Types</a> for detailed descriptions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EEC2InstanceType eC2InstanceType;

    /**
    *  <p>Number of instances of the specified type that are currently in use by this AWS account.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int currentInstances;

    /**
    *  <p>Number of instances allowed.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int instanceLimit;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FEC2InstanceLimit &fromAWS(const Aws::GameLift::Model::EC2InstanceLimit &awsEC2InstanceLimit) {
        switch(awsEC2InstanceLimit.GetEC2InstanceType()) {
            case Aws::GameLift::Model::EC2InstanceType::NOT_SET:
                this->eC2InstanceType = EEC2InstanceType::NOT_SET;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_micro:
                this->eC2InstanceType = EEC2InstanceType::t2_micro;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_small:
                this->eC2InstanceType = EEC2InstanceType::t2_small;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_medium:
                this->eC2InstanceType = EEC2InstanceType::t2_medium;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_large:
                this->eC2InstanceType = EEC2InstanceType::t2_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_large:
                this->eC2InstanceType = EEC2InstanceType::c3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_xlarge:
                this->eC2InstanceType = EEC2InstanceType::c3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::c3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_4xlarge:
                this->eC2InstanceType = EEC2InstanceType::c3_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_8xlarge:
                this->eC2InstanceType = EEC2InstanceType::c3_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_large:
                this->eC2InstanceType = EEC2InstanceType::c4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_xlarge:
                this->eC2InstanceType = EEC2InstanceType::c4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::c4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_4xlarge:
                this->eC2InstanceType = EEC2InstanceType::c4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_8xlarge:
                this->eC2InstanceType = EEC2InstanceType::c4_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_large:
                this->eC2InstanceType = EEC2InstanceType::r3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_xlarge:
                this->eC2InstanceType = EEC2InstanceType::r3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::r3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_4xlarge:
                this->eC2InstanceType = EEC2InstanceType::r3_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_8xlarge:
                this->eC2InstanceType = EEC2InstanceType::r3_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_large:
                this->eC2InstanceType = EEC2InstanceType::r4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_xlarge:
                this->eC2InstanceType = EEC2InstanceType::r4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::r4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_4xlarge:
                this->eC2InstanceType = EEC2InstanceType::r4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_8xlarge:
                this->eC2InstanceType = EEC2InstanceType::r4_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_16xlarge:
                this->eC2InstanceType = EEC2InstanceType::r4_16xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_medium:
                this->eC2InstanceType = EEC2InstanceType::m3_medium;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_large:
                this->eC2InstanceType = EEC2InstanceType::m3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_xlarge:
                this->eC2InstanceType = EEC2InstanceType::m3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::m3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_large:
                this->eC2InstanceType = EEC2InstanceType::m4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_xlarge:
                this->eC2InstanceType = EEC2InstanceType::m4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_2xlarge:
                this->eC2InstanceType = EEC2InstanceType::m4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_4xlarge:
                this->eC2InstanceType = EEC2InstanceType::m4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_10xlarge:
                this->eC2InstanceType = EEC2InstanceType::m4_10xlarge;
                break;
            default:
                this->eC2InstanceType = EEC2InstanceType::NOT_SET;
                break;
        }

        this->currentInstances = awsEC2InstanceLimit.GetCurrentInstances();

        this->instanceLimit = awsEC2InstanceLimit.GetInstanceLimit();

        return *this;
    }
#endif
};
