/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, November 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/ReplicaDescription.h"

#endif

#include "ReplicaDescription.generated.h"

USTRUCT(BlueprintType)
struct FReplicaDescription {
GENERATED_BODY()

    /**
    *  <p>The name of the region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamoDB Client")
    FString regionName;

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
public:
    FReplicaDescription &fromAWS(const Aws::DynamoDB::Model::ReplicaDescription &awsReplicaDescription) {
        this->regionName = UTF8_TO_TCHAR(awsReplicaDescription.GetRegionName().c_str());

        return *this;
    }
#endif
};
