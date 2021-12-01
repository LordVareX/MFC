/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/CreateFleetRequest.h"

#endif

#include "Model/EC2InstanceType.h"
#include "Model/IpPermission.h"
#include "Model/ProtectionPolicy.h"
#include "Model/RuntimeConfiguration.h"
#include "Model/ResourceCreationLimitPolicy.h"
#include "Model/FleetType.h"
#include "Model/CertificateConfiguration.h"

#include "CreateFleetRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateFleetRequest {
GENERATED_BODY()

    /**
    *  <p>Descriptive label that is associated with a fleet. Fleet names do not need to be unique.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Human-readable description of a fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString description;

    /**
    *  <p>Unique identifier for a build to be deployed on the new fleet. The custom game server build must have been successfully uploaded to Amazon GameLift and be in a <code>READY</code> status. This fleet setting cannot be changed once the fleet is created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString buildId;

    /**
    *  <p>Unique identifier for a Realtime script to be deployed on the new fleet. The Realtime script must have been successfully uploaded to Amazon GameLift. This fleet setting cannot be changed once the fleet is created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString scriptId;

    /**
    *  <p>This parameter is no longer used. Instead, specify a server launch path using the <code>RuntimeConfiguration</code> parameter. (Requests that specify a server launch path and launch parameters instead of a run-time configuration will continue to work.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString serverLaunchPath;

    /**
    *  <p>This parameter is no longer used. Instead, specify server launch parameters in the <code>RuntimeConfiguration</code> parameter. (Requests that specify a server launch path and launch parameters instead of a run-time configuration will continue to work.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString serverLaunchParameters;

    /**
    *  <p>This parameter is no longer used. Instead, to specify where Amazon GameLift should store log files once a server process shuts down, use the Amazon GameLift server API <code>ProcessReady()</code> and specify one or more directory paths in <code>logParameters</code>. See more information in the <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api-ref.html#gamelift-sdk-server-api-ref-dataypes-process">Server API Reference</a>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FString> logPaths;

    /**
    *  <p>Name of an EC2 instance type that is supported in Amazon GameLift. A fleet instance type determines the computing resources of each instance in the fleet, including CPU, memory, storage, and networking capacity. Amazon GameLift supports the following EC2 instance types. See <a href="http://aws.amazon.com/ec2/instance-types/">Amazon EC2 Instance Types</a> for detailed descriptions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EEC2InstanceType eC2InstanceType;

    /**
    *  <p>Range of IP addresses and port settings that permit inbound traffic to access game sessions that running on the fleet. For fleets using a custom game build, this parameter is required before game sessions running on the fleet can accept connections. For Realtime Servers fleets, Amazon GameLift automatically sets TCP and UDP ranges for use by the Realtime servers. You can specify multiple permission settings or add more by updating the fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FIpPermission> eC2InboundPermissions;

    /**
    *  <p>Game session protection policy to apply to all instances in this fleet. If this parameter is not set, instances in this fleet default to no protection. You can change a fleet's protection policy using <a>UpdateFleetAttributes</a>, but this change will only affect sessions created after the policy change. You can also set protection for individual instances using <a>UpdateGameSession</a>.</p> <ul> <li> <p> <b>NoProtection</b> -- The game session can be terminated during a scale-down event.</p> </li> <li> <p> <b>FullProtection</b> -- If the game session is in an <code>ACTIVE</code> status, it cannot be terminated during a scale-down event.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EProtectionPolicy newGameSessionProtectionPolicy;

    /**
    *  <p>Instructions for launching server processes on each instance in the fleet. Server processes run either a custom game build executable or a Realtime Servers script. The run-time configuration lists the types of server processes to run on an instance and includes the following configuration settings: the server executable or launch script file, launch parameters, and the number of processes to run concurrently on each instance. A CreateFleet request must include a run-time configuration with at least one server process configuration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FRuntimeConfiguration runtimeConfiguration;

    /**
    *  <p>Policy that limits the number of game sessions an individual player can create over a span of time for this fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FResourceCreationLimitPolicy resourceCreationLimitPolicy;

    /**
    *  <p>Name of an Amazon CloudWatch metric group to add this fleet to. A metric group aggregates the metrics for all fleets in the group. Specify an existing metric group name, or provide a new name to create a new metric group. A fleet can only be included in one metric group at a time. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FString> metricGroups;

    /**
    *  <p>Unique identifier for the AWS account with the VPC that you want to peer your Amazon GameLift fleet with. You can find your Account ID in the AWS Management Console under account settings. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString peerVpcAwsAccountId;

    /**
    *  <p>Unique identifier for a VPC with resources to be accessed by your Amazon GameLift fleet. The VPC must be in the same region where your fleet is deployed. Look up a VPC ID using the <a href="https://console.aws.amazon.com/vpc/">VPC Dashboard</a> in the AWS Management Console. Learn more about VPC peering in <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/vpc-peering.html">VPC Peering with Amazon GameLift Fleets</a>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString peerVpcId;

    /**
    *  <p>Indicates whether to use on-demand instances or spot instances for this fleet. If empty, the default is ON_DEMAND. Both categories of instances use identical hardware and configurations based on the instance type selected for this fleet. Learn more about <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-ec2-instances.html#gamelift-ec2-instances-spot"> On-Demand versus Spot Instances</a>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EFleetType fleetType;

    /**
    *  <p>Unique identifier for an AWS IAM role that manages access to your AWS services. With an instance role ARN set, any application that runs on an instance in this fleet can assume the role, including install scripts, server processes, daemons (background processes). Create a role or look up a role's ARN using the <a href="https://console.aws.amazon.com/iam/">IAM dashboard</a> in the AWS Management Console. Learn more about using on-box credentials for your game servers at <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-resources.html"> Access external resources from a game server</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString instanceRoleArn;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FCertificateConfiguration certificateConfiguration;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::CreateFleetRequest toAWS() const {
        Aws::GameLift::Model::CreateFleetRequest awsCreateFleetRequest;

        if (!(this->name.IsEmpty())) {
            awsCreateFleetRequest.SetName(TCHAR_TO_UTF8(*this->name));
        }

        if (!(this->description.IsEmpty())) {
            awsCreateFleetRequest.SetDescription(TCHAR_TO_UTF8(*this->description));
        }

        if (!(this->buildId.IsEmpty())) {
            awsCreateFleetRequest.SetBuildId(TCHAR_TO_UTF8(*this->buildId));
        }

        if (!(this->scriptId.IsEmpty())) {
            awsCreateFleetRequest.SetScriptId(TCHAR_TO_UTF8(*this->scriptId));
        }

        if (!(this->serverLaunchPath.IsEmpty())) {
            awsCreateFleetRequest.SetServerLaunchPath(TCHAR_TO_UTF8(*this->serverLaunchPath));
        }

        if (!(this->serverLaunchParameters.IsEmpty())) {
            awsCreateFleetRequest.SetServerLaunchParameters(TCHAR_TO_UTF8(*this->serverLaunchParameters));
        }

        for (const FString& elem : this->logPaths) {
            awsCreateFleetRequest.AddLogPaths(TCHAR_TO_UTF8(*elem));
        }

        switch(this->eC2InstanceType) {
            case EEC2InstanceType::NOT_SET:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::NOT_SET);
                break;
            case EEC2InstanceType::t2_micro:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_micro);
                break;
            case EEC2InstanceType::t2_small:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_small);
                break;
            case EEC2InstanceType::t2_medium:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_medium);
                break;
            case EEC2InstanceType::t2_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::t2_large);
                break;
            case EEC2InstanceType::c3_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_large);
                break;
            case EEC2InstanceType::c3_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_xlarge);
                break;
            case EEC2InstanceType::c3_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_2xlarge);
                break;
            case EEC2InstanceType::c3_4xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_4xlarge);
                break;
            case EEC2InstanceType::c3_8xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c3_8xlarge);
                break;
            case EEC2InstanceType::c4_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_large);
                break;
            case EEC2InstanceType::c4_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_xlarge);
                break;
            case EEC2InstanceType::c4_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_2xlarge);
                break;
            case EEC2InstanceType::c4_4xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_4xlarge);
                break;
            case EEC2InstanceType::c4_8xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::c4_8xlarge);
                break;
            case EEC2InstanceType::r3_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_large);
                break;
            case EEC2InstanceType::r3_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_xlarge);
                break;
            case EEC2InstanceType::r3_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_2xlarge);
                break;
            case EEC2InstanceType::r3_4xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_4xlarge);
                break;
            case EEC2InstanceType::r3_8xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r3_8xlarge);
                break;
            case EEC2InstanceType::r4_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_large);
                break;
            case EEC2InstanceType::r4_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_xlarge);
                break;
            case EEC2InstanceType::r4_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_2xlarge);
                break;
            case EEC2InstanceType::r4_4xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_4xlarge);
                break;
            case EEC2InstanceType::r4_8xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_8xlarge);
                break;
            case EEC2InstanceType::r4_16xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::r4_16xlarge);
                break;
            case EEC2InstanceType::m3_medium:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_medium);
                break;
            case EEC2InstanceType::m3_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_large);
                break;
            case EEC2InstanceType::m3_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_xlarge);
                break;
            case EEC2InstanceType::m3_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m3_2xlarge);
                break;
            case EEC2InstanceType::m4_large:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_large);
                break;
            case EEC2InstanceType::m4_xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_xlarge);
                break;
            case EEC2InstanceType::m4_2xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_2xlarge);
                break;
            case EEC2InstanceType::m4_4xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_4xlarge);
                break;
            case EEC2InstanceType::m4_10xlarge:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::m4_10xlarge);
                break;
            default:
                awsCreateFleetRequest.SetEC2InstanceType(Aws::GameLift::Model::EC2InstanceType::NOT_SET);
                break;
        }

        for (const FIpPermission& elem : this->eC2InboundPermissions) {
            awsCreateFleetRequest.AddEC2InboundPermissions(elem.toAWS());
        }

        switch(this->newGameSessionProtectionPolicy) {
            case EProtectionPolicy::NOT_SET:
                awsCreateFleetRequest.SetNewGameSessionProtectionPolicy(Aws::GameLift::Model::ProtectionPolicy::NOT_SET);
                break;
            case EProtectionPolicy::NoProtection:
                awsCreateFleetRequest.SetNewGameSessionProtectionPolicy(Aws::GameLift::Model::ProtectionPolicy::NoProtection);
                break;
            case EProtectionPolicy::FullProtection:
                awsCreateFleetRequest.SetNewGameSessionProtectionPolicy(Aws::GameLift::Model::ProtectionPolicy::FullProtection);
                break;
            default:
                awsCreateFleetRequest.SetNewGameSessionProtectionPolicy(Aws::GameLift::Model::ProtectionPolicy::NOT_SET);
                break;
        }

        if (!(this->runtimeConfiguration.IsEmpty())) {
            awsCreateFleetRequest.SetRuntimeConfiguration(this->runtimeConfiguration.toAWS());
        }

        if (!(this->resourceCreationLimitPolicy.IsEmpty())) {
            awsCreateFleetRequest.SetResourceCreationLimitPolicy(this->resourceCreationLimitPolicy.toAWS());
        }

        for (const FString& elem : this->metricGroups) {
            awsCreateFleetRequest.AddMetricGroups(TCHAR_TO_UTF8(*elem));
        }

        if (!(this->peerVpcAwsAccountId.IsEmpty())) {
            awsCreateFleetRequest.SetPeerVpcAwsAccountId(TCHAR_TO_UTF8(*this->peerVpcAwsAccountId));
        }

        if (!(this->peerVpcId.IsEmpty())) {
            awsCreateFleetRequest.SetPeerVpcId(TCHAR_TO_UTF8(*this->peerVpcId));
        }

        switch(this->fleetType) {
            case EFleetType::NOT_SET:
                awsCreateFleetRequest.SetFleetType(Aws::GameLift::Model::FleetType::NOT_SET);
                break;
            case EFleetType::ON_DEMAND:
                awsCreateFleetRequest.SetFleetType(Aws::GameLift::Model::FleetType::ON_DEMAND);
                break;
            case EFleetType::SPOT:
                awsCreateFleetRequest.SetFleetType(Aws::GameLift::Model::FleetType::SPOT);
                break;
            default:
                awsCreateFleetRequest.SetFleetType(Aws::GameLift::Model::FleetType::NOT_SET);
                break;
        }

        if (!(this->instanceRoleArn.IsEmpty())) {
            awsCreateFleetRequest.SetInstanceRoleArn(TCHAR_TO_UTF8(*this->instanceRoleArn));
        }


        if (!(this->certificateConfiguration.IsEmpty())) {
            awsCreateFleetRequest.SetCertificateConfiguration(this->certificateConfiguration.toAWS());
        }

        return awsCreateFleetRequest;
    }

    bool IsEmpty() const {
        return this->name.IsEmpty() && this->description.IsEmpty() && this->buildId.IsEmpty() && this->scriptId.IsEmpty() && this->serverLaunchPath.IsEmpty() && this->serverLaunchParameters.IsEmpty() && this->logPaths.Num() == 0 && this->eC2InstanceType == EEC2InstanceType::NOT_SET && this->eC2InboundPermissions.Num() == 0 && this->newGameSessionProtectionPolicy == EProtectionPolicy::NOT_SET && this->runtimeConfiguration.IsEmpty() && this->resourceCreationLimitPolicy.IsEmpty() && this->metricGroups.Num() == 0 && this->peerVpcAwsAccountId.IsEmpty() && this->peerVpcId.IsEmpty() && this->fleetType == EFleetType::NOT_SET && this->instanceRoleArn.IsEmpty() && this->certificateConfiguration.IsEmpty();
    }
#endif
};
