/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/PublishVersionResult.h"

#endif

#include "Model/Runtime.h"
#include "Model/VpcConfigResponse.h"
#include "Model/DeadLetterConfig.h"
#include "Model/EnvironmentResponse.h"
#include "Model/TracingConfigResponse.h"
#include "Model/AWSLayer.h"

#include "PublishVersionResult.generated.h"

USTRUCT(BlueprintType)
struct FPublishVersionResult {
GENERATED_BODY()

    /**
    *  <p>The name of the function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString functionName;

    /**
    *  <p>The function's Amazon Resource Name (ARN).</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString functionArn;

    /**
    *  <p>The runtime environment for the Lambda function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    EAWSRuntime runtime;

    /**
    *  <p>The function's execution role.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString role;

    /**
    *  <p>The function that Lambda calls to begin executing your function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString handler;

    /**
    *  <p>The size of the function's deployment package, in bytes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int codeSize;

    /**
    *  <p>The function's description.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString description;

    /**
    *  <p>The amount of time that Lambda allows a function to run before stopping it.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int timeout;

    /**
    *  <p>The memory that's allocated to the function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int memorySize;

    /**
    *  <p>The date and time that the function was last updated, in <a href="https://www.w3.org/TR/NOTE-datetime">ISO-8601 format</a> (YYYY-MM-DDThh:mm:ss.sTZD).</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString lastModified;

    /**
    *  <p>The SHA256 hash of the function's deployment package.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString codeSha256;

    /**
    *  <p>The version of the Lambda function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString version;

    /**
    *  <p>The function's networking configuration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FVpcConfigResponse vpcConfig;

    /**
    *  <p>The function's dead letter queue.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FDeadLetterConfig deadLetterConfig;

    /**
    *  <p>The function's environment variables.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FEnvironmentResponse environment;

    /**
    *  <p>The KMS key that's used to encrypt the function's environment variables. This key is only returned if you've configured a customer-managed CMK.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString kMSKeyArn;

    /**
    *  <p>The function's AWS X-Ray tracing configuration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FTracingConfigResponse tracingConfig;

    /**
    *  <p>For Lambda@Edge functions, the ARN of the master function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString masterArn;

    /**
    *  <p>The latest updated revision of the function or alias.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString revisionId;

    /**
    *  <p>The function's <a href="https://docs.aws.amazon.com/lambda/latest/dg/configuration-layers.html"> layers</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    TArray<FAWSLayer> layers;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    FPublishVersionResult &fromAWS(const Aws::Lambda::Model::PublishVersionResult &awsPublishVersionResult) {
        this->functionName = UTF8_TO_TCHAR(awsPublishVersionResult.GetFunctionName().c_str());

        this->functionArn = UTF8_TO_TCHAR(awsPublishVersionResult.GetFunctionArn().c_str());

        switch(awsPublishVersionResult.GetRuntime()) {
            case Aws::Lambda::Model::Runtime::NOT_SET:
                this->runtime = EAWSRuntime::NOT_SET;
                break;
            case Aws::Lambda::Model::Runtime::nodejs:
                this->runtime = EAWSRuntime::nodejs;
                break;
            case Aws::Lambda::Model::Runtime::nodejs4_3:
                this->runtime = EAWSRuntime::nodejs4_3;
                break;
            case Aws::Lambda::Model::Runtime::nodejs6_10:
                this->runtime = EAWSRuntime::nodejs6_10;
                break;
            case Aws::Lambda::Model::Runtime::nodejs8_10:
                this->runtime = EAWSRuntime::nodejs8_10;
                break;
            case Aws::Lambda::Model::Runtime::nodejs10_x:
                this->runtime = EAWSRuntime::nodejs10_x;
                break;
            case Aws::Lambda::Model::Runtime::java8:
                this->runtime = EAWSRuntime::java8;
                break;
            case Aws::Lambda::Model::Runtime::python2_7:
                this->runtime = EAWSRuntime::python2_7;
                break;
            case Aws::Lambda::Model::Runtime::python3_6:
                this->runtime = EAWSRuntime::python3_6;
                break;
            case Aws::Lambda::Model::Runtime::python3_7:
                this->runtime = EAWSRuntime::python3_7;
                break;
            case Aws::Lambda::Model::Runtime::dotnetcore1_0:
                this->runtime = EAWSRuntime::dotnetcore1_0;
                break;
            case Aws::Lambda::Model::Runtime::dotnetcore2_0:
                this->runtime = EAWSRuntime::dotnetcore2_0;
                break;
            case Aws::Lambda::Model::Runtime::dotnetcore2_1:
                this->runtime = EAWSRuntime::dotnetcore2_1;
                break;
            case Aws::Lambda::Model::Runtime::nodejs4_3_edge:
                this->runtime = EAWSRuntime::nodejs4_3_edge;
                break;
            case Aws::Lambda::Model::Runtime::go1_x:
                this->runtime = EAWSRuntime::go1_x;
                break;
            case Aws::Lambda::Model::Runtime::ruby2_5:
                this->runtime = EAWSRuntime::ruby2_5;
                break;
            case Aws::Lambda::Model::Runtime::provided:
                this->runtime = EAWSRuntime::provided;
                break;
            default:
                this->runtime = EAWSRuntime::NOT_SET;
                break;
            }

        this->role = UTF8_TO_TCHAR(awsPublishVersionResult.GetRole().c_str());

        this->handler = UTF8_TO_TCHAR(awsPublishVersionResult.GetHandler().c_str());

        this->codeSize = (int)awsPublishVersionResult.GetCodeSize();

        this->description = UTF8_TO_TCHAR(awsPublishVersionResult.GetDescription().c_str());

		this->timeout = awsPublishVersionResult.GetTimeout();

		this->memorySize = awsPublishVersionResult.GetMemorySize();

        this->lastModified = UTF8_TO_TCHAR(awsPublishVersionResult.GetLastModified().c_str());

        this->codeSha256 = UTF8_TO_TCHAR(awsPublishVersionResult.GetCodeSha256().c_str());

        this->version = UTF8_TO_TCHAR(awsPublishVersionResult.GetVersion().c_str());

        this->vpcConfig.fromAWS(awsPublishVersionResult.GetVpcConfig());

        this->deadLetterConfig.fromAWS(awsPublishVersionResult.GetDeadLetterConfig());

        this->environment.fromAWS(awsPublishVersionResult.GetEnvironment());

        this->kMSKeyArn = UTF8_TO_TCHAR(awsPublishVersionResult.GetKMSKeyArn().c_str());

        this->tracingConfig.fromAWS(awsPublishVersionResult.GetTracingConfig());

        this->masterArn = UTF8_TO_TCHAR(awsPublishVersionResult.GetMasterArn().c_str());

        this->revisionId = UTF8_TO_TCHAR(awsPublishVersionResult.GetRevisionId().c_str());

        this->layers.Empty();
        for (const Aws::Lambda::Model::Layer& elem : awsPublishVersionResult.GetLayers()) {
            this->layers.Add(FAWSLayer().fromAWS(elem));
        }

        return *this;
    }
#endif
};
