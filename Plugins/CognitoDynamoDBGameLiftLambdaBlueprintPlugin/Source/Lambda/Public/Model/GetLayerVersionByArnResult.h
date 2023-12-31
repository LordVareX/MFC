/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/GetLayerVersionByArnResult.h"

#endif

#include "Model/LayerVersionContentOutput.h"
#include "Model/Runtime.h"

#include "GetLayerVersionByArnResult.generated.h"

USTRUCT(BlueprintType)
struct FGetLayerVersionByArnResult {
GENERATED_BODY()

    /**
    *  <p>Details about the layer version.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FLayerVersionContentOutput content;

    /**
    *  <p>The ARN of the layer.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString layerArn;

    /**
    *  <p>The ARN of the layer version.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString layerVersionArn;

    /**
    *  <p>The description of the version.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString description;

    /**
    *  <p>The date that the layer version was created, in <a href="https://www.w3.org/TR/NOTE-datetime">ISO-8601 format</a> (YYYY-MM-DDThh:mm:ss.sTZD).</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString createdDate;

    /**
    *  <p>The version number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int version;

    /**
    *  <p>The layer's compatible runtimes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    TArray<EAWSRuntime> compatibleRuntimes;

    /**
    *  <p>The layer's software license.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString licenseInfo;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FGetLayerVersionByArnResult &fromAWS(const Aws::Lambda::Model::GetLayerVersionByArnResult &awsGetLayerVersionByArnResult) {
        this->content.fromAWS(awsGetLayerVersionByArnResult.GetContent());

        this->layerArn = UTF8_TO_TCHAR(awsGetLayerVersionByArnResult.GetLayerArn().c_str());

        this->layerVersionArn = UTF8_TO_TCHAR(awsGetLayerVersionByArnResult.GetLayerVersionArn().c_str());

        this->description = UTF8_TO_TCHAR(awsGetLayerVersionByArnResult.GetDescription().c_str());

        this->createdDate = UTF8_TO_TCHAR(awsGetLayerVersionByArnResult.GetCreatedDate().c_str());

        this->version = (int)awsGetLayerVersionByArnResult.GetVersion();

        this->compatibleRuntimes.Empty();
        for (const Aws::Lambda::Model::Runtime& elem : awsGetLayerVersionByArnResult.GetCompatibleRuntimes()) {
            switch(elem) {
                case Aws::Lambda::Model::Runtime::NOT_SET:
                    this->compatibleRuntimes.Add(EAWSRuntime::NOT_SET);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs4_3:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs4_3);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs6_10:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs6_10);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs8_10:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs8_10);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs10_x:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs10_x);
                    break;
                case Aws::Lambda::Model::Runtime::java8:
                    this->compatibleRuntimes.Add(EAWSRuntime::java8);
                    break;
                case Aws::Lambda::Model::Runtime::python2_7:
                    this->compatibleRuntimes.Add(EAWSRuntime::python2_7);
                    break;
                case Aws::Lambda::Model::Runtime::python3_6:
                    this->compatibleRuntimes.Add(EAWSRuntime::python3_6);
                    break;
                case Aws::Lambda::Model::Runtime::python3_7:
                    this->compatibleRuntimes.Add(EAWSRuntime::python3_7);
                    break;
                case Aws::Lambda::Model::Runtime::dotnetcore1_0:
                    this->compatibleRuntimes.Add(EAWSRuntime::dotnetcore1_0);
                    break;
                case Aws::Lambda::Model::Runtime::dotnetcore2_0:
                    this->compatibleRuntimes.Add(EAWSRuntime::dotnetcore2_0);
                    break;
                case Aws::Lambda::Model::Runtime::dotnetcore2_1:
                    this->compatibleRuntimes.Add(EAWSRuntime::dotnetcore2_1);
                    break;
                case Aws::Lambda::Model::Runtime::nodejs4_3_edge:
                    this->compatibleRuntimes.Add(EAWSRuntime::nodejs4_3_edge);
                    break;
                case Aws::Lambda::Model::Runtime::go1_x:
                    this->compatibleRuntimes.Add(EAWSRuntime::go1_x);
                    break;
                case Aws::Lambda::Model::Runtime::ruby2_5:
                    this->compatibleRuntimes.Add(EAWSRuntime::ruby2_5);
                    break;
                case Aws::Lambda::Model::Runtime::provided:
                    this->compatibleRuntimes.Add(EAWSRuntime::provided);
                    break;
                default:
                    this->compatibleRuntimes.Add(EAWSRuntime::NOT_SET);
                    break;
		    };
        }

        this->licenseInfo = UTF8_TO_TCHAR(awsGetLayerVersionByArnResult.GetLicenseInfo().c_str());

        return *this;
    }
#endif
};
