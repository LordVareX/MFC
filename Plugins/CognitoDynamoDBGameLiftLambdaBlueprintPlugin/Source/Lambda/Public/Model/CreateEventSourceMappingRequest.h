/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/CreateEventSourceMappingRequest.h"

#endif

#include "Model/EventSourcePosition.h"

#include "CreateEventSourceMappingRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateEventSourceMappingRequest {
GENERATED_BODY()

    /**
    *  <p>The Amazon Resource Name (ARN) of the event source.</p> <ul> <li> <p> <b>Amazon Kinesis</b> - The ARN of the data stream or a stream consumer.</p> </li> <li> <p> <b>Amazon DynamoDB Streams</b> - The ARN of the stream.</p> </li> <li> <p> <b>Amazon Simple Queue Service</b> - The ARN of the queue.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString eventSourceArn;

    /**
    *  <p>The name of the Lambda function.</p> <p class="title"> <b>Name formats</b> </p> <ul> <li> <p> <b>Function name</b> - <code>MyFunction</code>.</p> </li> <li> <p> <b>Function ARN</b> - <code>arn:aws:lambda:us-west-2:123456789012:function:MyFunction</code>.</p> </li> <li> <p> <b>Version or Alias ARN</b> - <code>arn:aws:lambda:us-west-2:123456789012:function:MyFunction:PROD</code>.</p> </li> <li> <p> <b>Partial ARN</b> - <code>123456789012:function:MyFunction</code>.</p> </li> </ul> <p>The length constraint applies only to the full ARN. If you specify only the function name, it's limited to 64 characters in length.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString functionName;

    /**
    *  <p>Disables the event source mapping to pause polling and invocation.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    bool enabled;

    /**
    *  <p>The maximum number of items to retrieve in a single batch.</p> <ul> <li> <p> <b>Amazon Kinesis</b> - Default 100. Max 10,000.</p> </li> <li> <p> <b>Amazon DynamoDB Streams</b> - Default 100. Max 1,000.</p> </li> <li> <p> <b>Amazon Simple Queue Service</b> - Default 10. Max 10.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int batchSize;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int maximumBatchingWindowInSeconds;

    /**
    *  <p>The position in a stream from which to start reading. Required for Amazon Kinesis and Amazon DynamoDB Streams sources. <code>AT_TIMESTAMP</code> is only supported for Amazon Kinesis streams.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    EAWSEventSourcePosition startingPosition;

    /**
    *  <p>With <code>StartingPosition</code> set to <code>AT_TIMESTAMP</code>, the time from which to start reading.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FDateTime startingPositionTimestamp;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    Aws::Lambda::Model::CreateEventSourceMappingRequest toAWS() const {
        Aws::Lambda::Model::CreateEventSourceMappingRequest awsCreateEventSourceMappingRequest;

		if (!(this->eventSourceArn.IsEmpty())) {
            awsCreateEventSourceMappingRequest.SetEventSourceArn(TCHAR_TO_UTF8(*this->eventSourceArn));
        }

		if (!(this->functionName.IsEmpty())) {
            awsCreateEventSourceMappingRequest.SetFunctionName(TCHAR_TO_UTF8(*this->functionName));
        }

        awsCreateEventSourceMappingRequest.SetEnabled(this->enabled);

        if (this->batchSize != 0) {
            awsCreateEventSourceMappingRequest.SetBatchSize(this->batchSize);
        }

        if (!(this->maximumBatchingWindowInSeconds == 0)) {
            awsCreateEventSourceMappingRequest.SetMaximumBatchingWindowInSeconds(this->maximumBatchingWindowInSeconds);
        }

        switch(this->startingPosition) {
            case EAWSEventSourcePosition::TRIM_HORIZON:
                awsCreateEventSourceMappingRequest.SetStartingPosition(Aws::Lambda::Model::EventSourcePosition::TRIM_HORIZON);
                break;
            case EAWSEventSourcePosition::LATEST:
                awsCreateEventSourceMappingRequest.SetStartingPosition(Aws::Lambda::Model::EventSourcePosition::LATEST);
                break;
            case EAWSEventSourcePosition::AT_TIMESTAMP:
                awsCreateEventSourceMappingRequest.SetStartingPosition(Aws::Lambda::Model::EventSourcePosition::AT_TIMESTAMP);
                break;
            default:
                break;
        }

        awsCreateEventSourceMappingRequest.SetStartingPositionTimestamp(Aws::Utils::DateTime((int64_t)this->startingPositionTimestamp.ToUnixTimestamp()));

        return awsCreateEventSourceMappingRequest;
    }

    bool IsEmpty() const {
        return this->eventSourceArn.IsEmpty() && this->functionName.IsEmpty() && false && this->batchSize == 0 && this->maximumBatchingWindowInSeconds == 0 && this->startingPosition == EAWSEventSourcePosition::NOT_SET && false;
    }

    
#endif
};
