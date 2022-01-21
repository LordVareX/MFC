/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/CreateEventSourceMappingResult.h"

#endif

#include "CreateEventSourceMappingResult.generated.h"

USTRUCT(BlueprintType)
struct FCreateEventSourceMappingResult {
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
    FCreateEventSourceMappingResult &fromAWS(const Aws::Lambda::Model::CreateEventSourceMappingResult &awsCreateEventSourceMappingResult) {
        this->UUID = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetUUID().c_str());

		this->batchSize = awsCreateEventSourceMappingResult.GetBatchSize();

		this->maximumBatchingWindowInSeconds = awsCreateEventSourceMappingResult.GetMaximumBatchingWindowInSeconds();

        this->eventSourceArn = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetEventSourceArn().c_str());

        this->functionArn = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetFunctionArn().c_str());

        this->lastModified = FDateTime::FromUnixTimestamp(awsCreateEventSourceMappingResult.GetLastModified().Millis());

        this->lastProcessingResult = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetLastProcessingResult().c_str());

        this->state = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetState().c_str());

        this->stateTransitionReason = UTF8_TO_TCHAR(awsCreateEventSourceMappingResult.GetStateTransitionReason().c_str());

        return *this;
    }
#endif
};
