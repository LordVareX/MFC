/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/FunctionCodeLocation.h"

#endif

#include "FunctionCodeLocation.generated.h"

USTRUCT(BlueprintType)
struct FFunctionCodeLocation {
GENERATED_BODY()

    /**
    *  <p>The service that's hosting the file.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString repositoryType;

    /**
    *  <p>A presigned URL that you can use to download the deployment package.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString location;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FFunctionCodeLocation &fromAWS(const Aws::Lambda::Model::FunctionCodeLocation &awsFunctionCodeLocation) {
        this->repositoryType = UTF8_TO_TCHAR(awsFunctionCodeLocation.GetRepositoryType().c_str());

        this->location = UTF8_TO_TCHAR(awsFunctionCodeLocation.GetLocation().c_str());

        return *this;
    }
#endif
};
