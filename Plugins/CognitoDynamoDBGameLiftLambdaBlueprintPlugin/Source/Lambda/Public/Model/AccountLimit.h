/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/AccountLimit.h"

#endif

#include "AccountLimit.generated.h"

USTRUCT(BlueprintType)
struct FAccountLimit {
GENERATED_BODY()

    /**
    *  <p>The amount of storage space that you can use for all deployment packages and layer archives.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int totalCodeSize;

    /**
    *  <p>The maximum size of your function's code and layers when they're extracted.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int codeSizeUnzipped;

    /**
    *  <p>The maximum size of a deployment package when it's uploaded directly to AWS Lambda. Use Amazon S3 for larger files.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int codeSizeZipped;

    /**
    *  <p>The maximum number of simultaneous function executions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int concurrentExecutions;

    /**
    *  <p>The maximum number of simultaneous function executions, minus the capacity that's reserved for individual functions with <a>PutFunctionConcurrency</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int unreservedConcurrentExecutions;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FAccountLimit &fromAWS(const Aws::Lambda::Model::AccountLimit &awsAccountLimit) {
        this->totalCodeSize = (int)awsAccountLimit.GetTotalCodeSize();

        this->codeSizeUnzipped = (int)awsAccountLimit.GetCodeSizeUnzipped();

        this->codeSizeZipped = (int)awsAccountLimit.GetCodeSizeZipped();

		this->concurrentExecutions = awsAccountLimit.GetConcurrentExecutions();

		this->unreservedConcurrentExecutions = awsAccountLimit.GetUnreservedConcurrentExecutions();

        return *this;
    }
#endif
};
