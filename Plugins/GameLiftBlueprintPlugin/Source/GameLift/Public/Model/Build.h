/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/Build.h"

#endif

#include "Model/BuildStatus.h"
#include "Model/OperatingSystem.h"

#include "Build.generated.h"

USTRUCT(BlueprintType)
struct FBuild {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a build.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString buildId;

    /**
    *  <p>Descriptive label that is associated with a build. Build names do not need to be unique. It can be set using <a>CreateBuild</a> or <a>UpdateBuild</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Version that is associated with a build or script. Version strings do not need to be unique. This value can be set using <a>CreateBuild</a> or <a>UpdateBuild</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString version;

    /**
    *  <p>Current status of the build.</p> <p>Possible build statuses include the following:</p> <ul> <li> <p> <b>INITIALIZED</b> -- A new build has been defined, but no files have been uploaded. You cannot create fleets for builds that are in this status. When a build is successfully created, the build status is set to this value. </p> </li> <li> <p> <b>READY</b> -- The game build has been successfully uploaded. You can now create new fleets for this build.</p> </li> <li> <p> <b>FAILED</b> -- The game build upload failed. You cannot create new fleets for this build. </p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EBuildStatus status;

    /**
    *  <p>File size of the uploaded game build, expressed in bytes. When the build status is <code>INITIALIZED</code>, this value is 0.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int sizeOnDisk;

    /**
    *  <p>Operating system that the game server binaries are built to run on. This value determines the type of fleet resources that you can use for this build.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EOperatingSystem operatingSystem;

    /**
    *  <p>Time stamp indicating when this data object was created. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime creationTime;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FBuild &fromAWS(const Aws::GameLift::Model::Build &awsBuild) {
        this->buildId = awsBuild.GetBuildId().c_str();

        this->name = awsBuild.GetName().c_str();

        this->version = awsBuild.GetVersion().c_str();

        switch(awsBuild.GetStatus()) {
            case Aws::GameLift::Model::BuildStatus::NOT_SET:
                this->status = EBuildStatus::NOT_SET;
                break;
            case Aws::GameLift::Model::BuildStatus::INITIALIZED:
                this->status = EBuildStatus::INITIALIZED;
                break;
            case Aws::GameLift::Model::BuildStatus::READY:
                this->status = EBuildStatus::READY;
                break;
            case Aws::GameLift::Model::BuildStatus::FAILED:
                this->status = EBuildStatus::FAILED;
                break;
            default:
                this->status = EBuildStatus::NOT_SET;
                break;
        }

        this->sizeOnDisk = (int)awsBuild.GetSizeOnDisk();

        switch(awsBuild.GetOperatingSystem()) {
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

        this->creationTime = FDateTime::FromUnixTimestamp(awsBuild.GetCreationTime().Millis());

        return *this;
    }
#endif
};