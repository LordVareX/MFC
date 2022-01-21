/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/UpdateEventSourceMappingRequest.h"

#endif

#include "UpdateEventSourceMappingRequest.generated.h"

USTRUCT(BlueprintType)
struct FUpdateEventSourceMappingRequest {
GENERATED_BODY()

    /**
    *  <p>The identifier of the event source mapping.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString UUID;

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

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    Aws::Lambda::Model::UpdateEventSourceMappingRequest toAWS() const {
        Aws::Lambda::Model::UpdateEventSourceMappingRequest awsUpdateEventSourceMappingRequest;

		if (!(this->UUID.IsEmpty())) {
            awsUpdateEventSourceMappingRequest.SetUUID(TCHAR_TO_UTF8(*this->UUID));
        }

		if (!(this->functionName.IsEmpty())) {
            awsUpdateEventSourceMappingRequest.SetFunctionName(TCHAR_TO_UTF8(*this->functionName));
        }

		awsUpdateEventSourceMappingRequest.SetEnabled(this->enabled);

        if (this->batchSize != 0) {
            awsUpdateEventSourceMappingRequest.SetBatchSize(this->batchSize);
        }

        if (this->maximumBatchingWindowInSeconds != 0) {
            awsUpdateEventSourceMappingRequest.SetMaximumBatchingWindowInSeconds(this->maximumBatchingWindowInSeconds);
        }

        return awsUpdateEventSourceMappingRequest;
    }

    bool IsEmpty() const {
        return this->UUID.IsEmpty() && this->functionName.IsEmpty() && false && this->batchSize == 0 && this->maximumBatchingWindowInSeconds == 0;
    }

    
#endif
};
