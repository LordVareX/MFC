/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, November 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/ProvisionedThroughputDescription.h"

#endif

#include "ProvisionedThroughputDescription.generated.h"

USTRUCT(BlueprintType)
struct FProvisionedThroughputDescription {
GENERATED_BODY()

    /**
    *  <p>The date and time of the last provisioned throughput increase for this table.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FDateTime lastIncreaseDateTime;

    /**
    *  <p>The date and time of the last provisioned throughput decrease for this table.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FDateTime lastDecreaseDateTime;

    /**
    *  <p>The number of provisioned throughput decreases for this table during this UTC calendar day. For current maximums on provisioned throughput decreases, see <a href="https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/Limits.html">Limits</a> in the <i>Amazon DynamoDB Developer Guide</i>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    int numberOfDecreasesToday;

    /**
    *  <p>The maximum number of strongly consistent reads consumed per second before DynamoDB returns a <code>ThrottlingException</code>. Eventually consistent reads require less effort than strongly consistent reads, so a setting of 50 <code>ReadCapacityUnits</code> per second provides 100 eventually consistent <code>ReadCapacityUnits</code> per second.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    int readCapacityUnits;

    /**
    *  <p>The maximum number of writes consumed per second before DynamoDB returns a <code>ThrottlingException</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    int writeCapacityUnits;

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
public:
    FProvisionedThroughputDescription &fromAWS(const Aws::DynamoDB::Model::ProvisionedThroughputDescription &awsProvisionedThroughputDescription) {
        this->lastIncreaseDateTime = FDateTime::FromUnixTimestamp(awsProvisionedThroughputDescription.GetLastIncreaseDateTime().Millis());

        this->lastDecreaseDateTime = FDateTime::FromUnixTimestamp(awsProvisionedThroughputDescription.GetLastDecreaseDateTime().Millis());

        this->numberOfDecreasesToday = (int)awsProvisionedThroughputDescription.GetNumberOfDecreasesToday();

        this->readCapacityUnits = (int)awsProvisionedThroughputDescription.GetReadCapacityUnits();

        this->writeCapacityUnits = (int)awsProvisionedThroughputDescription.GetWriteCapacityUnits();

        return *this;
    }
#endif
};
