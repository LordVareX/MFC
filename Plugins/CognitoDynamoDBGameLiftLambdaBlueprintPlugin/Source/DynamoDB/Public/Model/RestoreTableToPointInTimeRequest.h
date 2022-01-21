/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, November 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/RestoreTableToPointInTimeRequest.h"

#endif

#include "RestoreTableToPointInTimeRequest.generated.h"

USTRUCT(BlueprintType)
struct FRestoreTableToPointInTimeRequest {
GENERATED_BODY()

    /**
    *  <p>Name of the source table that is being restored.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FString sourceTableName;

    /**
    *  <p>The name of the new table to which it must be restored to.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FString targetTableName;

    /**
    *  <p>Restore the table to the latest possible time. <code>LatestRestorableDateTime</code> is typically 5 minutes before the current time. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    bool useLatestRestorableTime;

    /**
    *  <p>Time in the past to restore the table to.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FDateTime restoreDateTime;

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
public:
    Aws::DynamoDB::Model::RestoreTableToPointInTimeRequest toAWS() const {
        Aws::DynamoDB::Model::RestoreTableToPointInTimeRequest awsRestoreTableToPointInTimeRequest;

		if (!(this->sourceTableName.IsEmpty())) {
            awsRestoreTableToPointInTimeRequest.SetSourceTableName(TCHAR_TO_UTF8(*this->sourceTableName));
        }

		if (!(this->targetTableName.IsEmpty())) {
            awsRestoreTableToPointInTimeRequest.SetTargetTableName(TCHAR_TO_UTF8(*this->targetTableName));
        }

		awsRestoreTableToPointInTimeRequest.SetUseLatestRestorableTime(this->useLatestRestorableTime);

		awsRestoreTableToPointInTimeRequest.SetRestoreDateTime(Aws::Utils::DateTime((int64_t)this->restoreDateTime.ToUnixTimestamp()));

        return awsRestoreTableToPointInTimeRequest;
    }

    bool IsEmpty() const {
        return this->sourceTableName.IsEmpty() && this->targetTableName.IsEmpty() && false && false;
    }
#endif
};
