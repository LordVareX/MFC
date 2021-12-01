/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/UnrealMemory.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/CreateScriptRequest.h"

#endif

#include "Model/S3Location.h"

#include "CreateScriptRequest.generated.h"

USTRUCT(BlueprintType)

struct FCreateScriptRequest {
    GENERATED_BODY()

    /**
    *  <p>Descriptive label that is associated with a script. Script names do not need to be unique. You can use <a>UpdateScript</a> to change this value later. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Version that is associated with a build or script. Version strings do not need to be unique. You can use <a>UpdateScript</a> to change this value later. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString version;

    /**
    *  <p>Location of the Amazon S3 bucket where a zipped file containing your Realtime scripts is stored. The storage location must specify the Amazon S3 bucket name, the zip file name (the "key"), and a role ARN that allows Amazon GameLift to access the Amazon S3 storage location. The S3 bucket must be in the same region where you want to create a new script. By default, Amazon GameLift uploads the latest version of the zip file; if you have S3 object versioning turned on, you can use the <code>ObjectVersion</code> parameter to specify an earlier version. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FS3Location storageLocation;

    /**
     * Indicate the zip file path. Absolute File Path
    *  <p>Data object containing your Realtime scripts and dependencies as a zip file. The zip file can have one or multiple files. Maximum size of a zip file is 5 MB.</p> <p>When using the AWS CLI tool to create a script, this parameter is set to the zip file name. It must be prepended with the string "fileb://" to indicate that the file data is a binary object. For example: <code>--zip-file fileb://myRealtimeScript.zip</code>.</p>
     *  unsupported
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString zipFile;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    public:
        Aws::GameLift::Model::CreateScriptRequest toAWS() const {
            Aws::GameLift::Model::CreateScriptRequest awsCreateScriptRequest;

            if (!(this->name.IsEmpty())) {
                awsCreateScriptRequest.SetName(TCHAR_TO_UTF8(*this->name));
            }

            if (!(this->version.IsEmpty())) {
                awsCreateScriptRequest.SetVersion(TCHAR_TO_UTF8(*this->version));
            }

            if (!(this->storageLocation.IsEmpty())) {
                awsCreateScriptRequest.SetStorageLocation(this->storageLocation.toAWS());
            }

            if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*this->zipFile)) {
                IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

                IFileHandle* FileHandle = PlatformFile.OpenRead(*this->zipFile);
                if(FileHandle) {
                    uint8* ByteBuffer = (uint8*)FMemory::Malloc(FPlatformFileManager::Get().GetPlatformFile().FileSize(*this->zipFile));

                    FileHandle->Read(ByteBuffer, sizeof(ByteBuffer));

                    awsCreateScriptRequest.SetZipFile(Aws::Utils::CryptoBuffer(Aws::Utils::ByteBuffer(ByteBuffer, sizeof(ByteBuffer))));

                    delete FileHandle;
                    FMemory::Free(ByteBuffer);
                }
            }

            return awsCreateScriptRequest;
        }

        bool IsEmpty() const {
            return this->name.IsEmpty() && this->version.IsEmpty() && this->storageLocation.IsEmpty() && !FPlatformFileManager::Get().GetPlatformFile().FileExists(*this->zipFile);
        }
#endif
};
