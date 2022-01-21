/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/Layer.h"

#endif

#include "AWSLayer.generated.h"

USTRUCT(BlueprintType)
struct FAWSLayer {
GENERATED_BODY()

    /**
    *  <p>The Amazon Resource Name (ARN) of the function layer.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString arn;

    /**
    *  <p>The size of the layer archive in bytes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int codeSize;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FAWSLayer &fromAWS(const Aws::Lambda::Model::Layer &awsLayer) {
        this->arn = UTF8_TO_TCHAR(awsLayer.GetArn().c_str());

        this->codeSize = (int)awsLayer.GetCodeSize();

        return *this;
    }
#endif
};
