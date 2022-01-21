/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/DeleteEventSourceMappingResult.h"

#endif

#include "DeleteEventSourceMappingResult.generated.h"

USTRUCT(BlueprintType)
struct FDeleteEventSourceMappingResult {
GENERATED_BODY()

    /**
    *  <p>The identifier of the event source mapping.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString UUID;

    /**
    *  <p>The maximum number of items to retrieve in a single batch.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int batchSize;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int maximumBatchingWindowInSeconds;

    /**
    *  <p>The Amazon Resource Name (ARN) of the event source.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString eventSourceArn;

    /**
    *  <p>The ARN of the Lambda function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString functionArn;

    /**
    *  <p>The date that the event source mapping was last updated.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FDateTime lastModified;

    /**
    *  <p>The result of the last AWS Lambda invocation of your Lambda function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString lastProcessingResult;

    /**
    *  <p>The state of the event source mapping. It can be one of the following: <code>Creating</code>, <code>Enabling</code>, <code>Enabled</code>, <code>Disabling</code>, <code>Disabled</code>, <code>Updating</code>, or <code>Deleting</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString state;

    /**
    *  <p>The cause of the last state change, either <code>User initiated</code> or <code>Lambda initiated</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString stateTransitionReason;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FDeleteEventSourceMappingResult &fromAWS(const Aws::Lambda::Model::DeleteEventSourceMappingResult &awsDeleteEventSourceMappingResult) {
        this->UUID = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetUUID().c_str());

		this->batchSize = awsDeleteEventSourceMappingResult.GetBatchSize();

		this->maximumBatchingWindowInSeconds = awsDeleteEventSourceMappingResult.GetMaximumBatchingWindowInSeconds();

        this->eventSourceArn = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetEventSourceArn().c_str());

        this->functionArn = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetFunctionArn().c_str());

        this->lastModified = FDateTime::FromUnixTimestamp(awsDeleteEventSourceMappingResult.GetLastModified().Millis());

        this->lastProcessingResult = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetLastProcessingResult().c_str());

        this->state = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetState().c_str());

        this->stateTransitionReason = UTF8_TO_TCHAR(awsDeleteEventSourceMappingResult.GetStateTransitionReason().c_str());

        return *this;
    }
#endif
};
