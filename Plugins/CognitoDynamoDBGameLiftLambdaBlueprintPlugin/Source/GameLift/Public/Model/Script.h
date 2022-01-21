/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/Script.h"

#endif

#include "Model/S3Location.h"

#include "Script.generated.h"

USTRUCT(BlueprintType)
struct FScript {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a Realtime script</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString scriptId;

    /**
    *  <p>Descriptive label that is associated with a script. Script names do not need to be unique.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Version that is associated with a build or script. Version strings do not need to be unique.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString version;

    /**
    *  <p>File size of the uploaded Realtime script, expressed in bytes. When files are uploaded from an S3 location, this value remains at "0".</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int sizeOnDisk;

    /**
    *  <p>Time stamp indicating when this data object was created. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime creationTime;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FS3Location storageLocation;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FScript &fromAWS(const Aws::GameLift::Model::Script &awsScript) {
        this->scriptId = UTF8_TO_TCHAR(awsScript.GetScriptId().c_str());

        this->name = UTF8_TO_TCHAR(awsScript.GetName().c_str());

        this->version = UTF8_TO_TCHAR(awsScript.GetVersion().c_str());

        this->sizeOnDisk = (int)awsScript.GetSizeOnDisk();

        this->creationTime = FDateTime::FromUnixTimestamp(awsScript.GetCreationTime().Millis());

        this->storageLocation.fromAWS(awsScript.GetStorageLocation());

        return *this;
    }
#endif
};
