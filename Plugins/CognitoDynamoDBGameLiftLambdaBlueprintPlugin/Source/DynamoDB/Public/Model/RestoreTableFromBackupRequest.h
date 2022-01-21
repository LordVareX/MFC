/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, November 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/RestoreTableFromBackupRequest.h"

#endif

#include "RestoreTableFromBackupRequest.generated.h"

USTRUCT(BlueprintType)
struct FRestoreTableFromBackupRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the new table to which the backup must be restored.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FString targetTableName;

    /**
    *  <p>The Amazon Resource Name (ARN) associated with the backup.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FString backupArn;

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
public:
    Aws::DynamoDB::Model::RestoreTableFromBackupRequest toAWS() const {
        Aws::DynamoDB::Model::RestoreTableFromBackupRequest awsRestoreTableFromBackupRequest;

		if (!(this->targetTableName.IsEmpty())) {
            awsRestoreTableFromBackupRequest.SetTargetTableName(TCHAR_TO_UTF8(*this->targetTableName));
        }

		if (!(this->backupArn.IsEmpty())) {
            awsRestoreTableFromBackupRequest.SetBackupArn(TCHAR_TO_UTF8(*this->backupArn));
        }

        return awsRestoreTableFromBackupRequest;
    }

    bool IsEmpty() const {
        return this->targetTableName.IsEmpty() && this->backupArn.IsEmpty();
    }
#endif
};
