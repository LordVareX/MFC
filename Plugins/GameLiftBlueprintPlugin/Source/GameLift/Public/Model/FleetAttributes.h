/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/FleetAttributes.h"

#endif

#include "Model/FleetType.h"
#include "Model/EC2InstanceType.h"
#include "Model/FleetStatus.h"
#include "Model/ProtectionPolicy.h"
#include "Model/OperatingSystem.h"
#include "Model/ResourceCreationLimitPolicy.h"
#include "Model/FleetAction.h"
#include "Model/CertificateConfiguration.h"

#include "FleetAttributes.generated.h"

USTRUCT(BlueprintType)
struct FFleetAttributes {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

    /**
    *  <p>Identifier for a fleet that is unique across all regions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetArn;

    /**
    *  <p>Indicates whether the fleet uses on-demand or spot instances. A spot instance in use may be interrupted with a two-minute notification.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EFleetType fleetType;

    /**
    *  <p>EC2 instance type indicating the computing resources of each instance in the fleet, including CPU, memory, storage, and networking capacity. See <a href="http://aws.amazon.com/ec2/instance-types/">Amazon EC2 Instance Types</a> for detailed descriptions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EEC2InstanceType instanceType;

    /**
    *  <p>Human-readable description of the fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString description;

    /**
    *  <p>Descriptive label that is associated with a fleet. Fleet names do not need to be unique.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Time stamp indicating when this data object was created. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime creationTime;

    /**
    *  <p>Time stamp indicating when this data object was terminated. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime terminationTime;

    /**
    *  <p>Current status of the fleet.</p> <p>Possible fleet statuses include the following:</p> <ul> <li> <p> <b>NEW</b> -- A new fleet has been defined and desired instances is set to 1. </p> </li> <li> <p> <b>DOWNLOADING/VALIDATING/BUILDING/ACTIVATING</b> -- Amazon GameLift is setting up the new fleet, creating new instances with the game build or Realtime script and starting server processes.</p> </li> <li> <p> <b>ACTIVE</b> -- Hosts can now accept game sessions.</p> </li> <li> <p> <b>ERROR</b> -- An error occurred when downloading, validating, building, or activating the fleet.</p> </li> <li> <p> <b>DELETING</b> -- Hosts are responding to a delete fleet request.</p> </li> <li> <p> <b>TERMINATED</b> -- The fleet no longer exists.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EFleetStatus status;

    /**
    *  <p>Unique identifier for a build.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString buildId;

    /**
    *  <p>Unique identifier for a Realtime script.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString scriptId;

    /**
    *  <p>Path to a game server executable in the fleet's build, specified for fleets created before 2016-08-04 (or AWS SDK v. 0.12.16). Server launch paths for fleets created after this date are specified in the fleet's <a>RuntimeConfiguration</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString serverLaunchPath;

    /**
    *  <p>Game server launch parameters specified for fleets created before 2016-08-04 (or AWS SDK v. 0.12.16). Server launch parameters for fleets created after this date are specified in the fleet's <a>RuntimeConfiguration</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString serverLaunchParameters;

    /**
    *  <p>Location of default log files. When a server process is shut down, Amazon GameLift captures and stores any log files in this location. These logs are in addition to game session logs; see more on game session logs in the <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-api-server-code">Amazon GameLift Developer Guide</a>. If no default log path for a fleet is specified, Amazon GameLift automatically uploads logs that are stored on each instance at <code>C:\game\logs</code> (for Windows) or <code>/local/game/logs</code> (for Linux). Use the Amazon GameLift console to access stored logs. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FString> logPaths;

    /**
    *  <p>Type of game session protection to set for all new instances started in the fleet.</p> <ul> <li> <p> <b>NoProtection</b> -- The game session can be terminated during a scale-down event.</p> </li> <li> <p> <b>FullProtection</b> -- If the game session is in an <code>ACTIVE</code> status, it cannot be terminated during a scale-down event.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EProtectionPolicy newGameSessionProtectionPolicy;

    /**
    *  <p>Operating system of the fleet's computing resources. A fleet's operating system depends on the OS specified for the build that is deployed on this fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EOperatingSystem operatingSystem;

    /**
    *  <p>Fleet policy to limit the number of game sessions an individual player can create over a span of time.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FResourceCreationLimitPolicy resourceCreationLimitPolicy;

    /**
    *  <p>Names of metric groups that this fleet is included in. In Amazon CloudWatch, you can view metrics for an individual fleet or aggregated metrics for fleets that are in a fleet metric group. A fleet can be included in only one metric group at a time.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FString> metricGroups;

    /**
    *  <p>List of fleet actions that have been suspended using <a>StopFleetActions</a>. This includes auto-scaling.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<EFleetAction> stoppedActions;

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
    FFleetAttributes &fromAWS(const Aws::GameLift::Model::FleetAttributes &awsFleetAttributes) {
        this->fleetId = awsFleetAttributes.GetFleetId().c_str();

        this->fleetArn = awsFleetAttributes.GetFleetArn().c_str();

        switch(awsFleetAttributes.GetFleetType()) {
            case Aws::GameLift::Model::FleetType::NOT_SET:
                this->fleetType = EFleetType::NOT_SET;
                break;
            case Aws::GameLift::Model::FleetType::ON_DEMAND:
                this->fleetType = EFleetType::ON_DEMAND;
                break;
            case Aws::GameLift::Model::FleetType::SPOT:
                this->fleetType = EFleetType::SPOT;
                break;
            default:
                this->fleetType = EFleetType::NOT_SET;
                break;
        }

        switch(awsFleetAttributes.GetInstanceType()) {
            case Aws::GameLift::Model::EC2InstanceType::NOT_SET:
                this->instanceType = EEC2InstanceType::NOT_SET;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_micro:
                this->instanceType = EEC2InstanceType::t2_micro;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_small:
                this->instanceType = EEC2InstanceType::t2_small;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_medium:
                this->instanceType = EEC2InstanceType::t2_medium;
                break;
            case Aws::GameLift::Model::EC2InstanceType::t2_large:
                this->instanceType = EEC2InstanceType::t2_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_large:
                this->instanceType = EEC2InstanceType::c3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_xlarge:
                this->instanceType = EEC2InstanceType::c3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_2xlarge:
                this->instanceType = EEC2InstanceType::c3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_4xlarge:
                this->instanceType = EEC2InstanceType::c3_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c3_8xlarge:
                this->instanceType = EEC2InstanceType::c3_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_large:
                this->instanceType = EEC2InstanceType::c4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_xlarge:
                this->instanceType = EEC2InstanceType::c4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_2xlarge:
                this->instanceType = EEC2InstanceType::c4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_4xlarge:
                this->instanceType = EEC2InstanceType::c4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::c4_8xlarge:
                this->instanceType = EEC2InstanceType::c4_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_large:
                this->instanceType = EEC2InstanceType::r3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_xlarge:
                this->instanceType = EEC2InstanceType::r3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_2xlarge:
                this->instanceType = EEC2InstanceType::r3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_4xlarge:
                this->instanceType = EEC2InstanceType::r3_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r3_8xlarge:
                this->instanceType = EEC2InstanceType::r3_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_large:
                this->instanceType = EEC2InstanceType::r4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_xlarge:
                this->instanceType = EEC2InstanceType::r4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_2xlarge:
                this->instanceType = EEC2InstanceType::r4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_4xlarge:
                this->instanceType = EEC2InstanceType::r4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_8xlarge:
                this->instanceType = EEC2InstanceType::r4_8xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::r4_16xlarge:
                this->instanceType = EEC2InstanceType::r4_16xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_medium:
                this->instanceType = EEC2InstanceType::m3_medium;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_large:
                this->instanceType = EEC2InstanceType::m3_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_xlarge:
                this->instanceType = EEC2InstanceType::m3_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m3_2xlarge:
                this->instanceType = EEC2InstanceType::m3_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_large:
                this->instanceType = EEC2InstanceType::m4_large;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_xlarge:
                this->instanceType = EEC2InstanceType::m4_xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_2xlarge:
                this->instanceType = EEC2InstanceType::m4_2xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_4xlarge:
                this->instanceType = EEC2InstanceType::m4_4xlarge;
                break;
            case Aws::GameLift::Model::EC2InstanceType::m4_10xlarge:
                this->instanceType = EEC2InstanceType::m4_10xlarge;
                break;
            default:
                this->instanceType = EEC2InstanceType::NOT_SET;
                break;
        }

        this->description = awsFleetAttributes.GetDescription().c_str();

        this->name = awsFleetAttributes.GetName().c_str();

        this->creationTime = FDateTime::FromUnixTimestamp(awsFleetAttributes.GetCreationTime().Millis());

        this->terminationTime = FDateTime::FromUnixTimestamp(awsFleetAttributes.GetTerminationTime().Millis());

        switch(awsFleetAttributes.GetStatus()) {
            case Aws::GameLift::Model::FleetStatus::NOT_SET:
                this->status = EFleetStatus::NOT_SET;
                break;
            case Aws::GameLift::Model::FleetStatus::NEW_:
                this->status = EFleetStatus::NEW_;
                break;
            case Aws::GameLift::Model::FleetStatus::DOWNLOADING:
                this->status = EFleetStatus::DOWNLOADING;
                break;
            case Aws::GameLift::Model::FleetStatus::VALIDATING:
                this->status = EFleetStatus::VALIDATING;
                break;
            case Aws::GameLift::Model::FleetStatus::BUILDING:
                this->status = EFleetStatus::BUILDING;
                break;
            case Aws::GameLift::Model::FleetStatus::ACTIVATING:
                this->status = EFleetStatus::ACTIVATING;
                break;
            case Aws::GameLift::Model::FleetStatus::ACTIVE:
                this->status = EFleetStatus::ACTIVE;
                break;
            case Aws::GameLift::Model::FleetStatus::DELETING:
                this->status = EFleetStatus::DELETING;
                break;
            case Aws::GameLift::Model::FleetStatus::ERROR_:
                this->status = EFleetStatus::ERROR_;
                break;
            case Aws::GameLift::Model::FleetStatus::TERMINATED:
                this->status = EFleetStatus::TERMINATED;
                break;
            default:
                this->status = EFleetStatus::NOT_SET;
                break;
        }

        this->buildId = awsFleetAttributes.GetBuildId().c_str();

        this->scriptId = awsFleetAttributes.GetScriptId().c_str();

        this->serverLaunchPath = awsFleetAttributes.GetServerLaunchPath().c_str();

        this->serverLaunchParameters = awsFleetAttributes.GetServerLaunchParameters().c_str();

        this->logPaths.Empty();
        for (const Aws::String& elem : awsFleetAttributes.GetLogPaths()) {
            this->logPaths.Add(elem.c_str());
        }

        switch(awsFleetAttributes.GetNewGameSessionProtectionPolicy()) {
            case Aws::GameLift::Model::ProtectionPolicy::NOT_SET:
                this->newGameSessionProtectionPolicy = EProtectionPolicy::NOT_SET;
                break;
            case Aws::GameLift::Model::ProtectionPolicy::NoProtection:
                this->newGameSessionProtectionPolicy = EProtectionPolicy::NoProtection;
                break;
            case Aws::GameLift::Model::ProtectionPolicy::FullProtection:
                this->newGameSessionProtectionPolicy = EProtectionPolicy::FullProtection;
                break;
            default:
                this->newGameSessionProtectionPolicy = EProtectionPolicy::NOT_SET;
                break;
        }

        switch(awsFleetAttributes.GetOperatingSystem()) {
            case Aws::GameLift::Model::OperatingSystem::NOT_SET:
                this->operatingSystem = EOperatingSystem::NOT_SET;
                break;
            case Aws::GameLift::Model::OperatingSystem::WINDOWS_2012:
                this->operatingSystem = EOperatingSystem::WINDOWS_2012;
                break;
            case Aws::GameLift::Model::OperatingSystem::AMAZON_LINUX:
                this->operatingSystem = EOperatingSystem::AMAZON_LINUX;
                break;
            default:
                this->operatingSystem = EOperatingSystem::NOT_SET;
                break;
        }

        this->resourceCreationLimitPolicy.fromAWS(awsFleetAttributes.GetResourceCreationLimitPolicy());

        this->metricGroups.Empty();
        for (const Aws::String& elem : awsFleetAttributes.GetMetricGroups()) {
            this->metricGroups.Add(elem.c_str());
        }

        this->stoppedActions.Empty();
        for (const Aws::GameLift::Model::FleetAction& elem : awsFleetAttributes.GetStoppedActions()) {
            switch(elem) {
                case Aws::GameLift::Model::FleetAction::NOT_SET:
                    this->stoppedActions.Add(EFleetAction::NOT_SET);
                    break;
                case Aws::GameLift::Model::FleetAction::AUTO_SCALING:
                    this->stoppedActions.Add(EFleetAction::AUTO_SCALING);
                    break;
                default:
                    this->stoppedActions.Add(EFleetAction::NOT_SET);
                    break;
            };
        }

        this->instanceRoleArn = awsFleetAttributes.GetInstanceRoleArn().c_str();

        this->certificateConfiguration.fromAWS(awsFleetAttributes.GetCertificateConfiguration());

        return *this;
    }
#endif
};
