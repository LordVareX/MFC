/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, October 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_LAMBDACLIENTSDK && WITH_CORE

#include "aws/lambda/model/CreateFunctionRequest.h"

#endif

#include "Model/Runtime.h"
#include "Model/FunctionCode.h"
#include "Model/VpcConfig.h"
#include "Model/DeadLetterConfig.h"
#include "Model/Environment.h"
#include "Model/TracingConfig.h"

#include "CreateFunctionRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateFunctionRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the Lambda function.</p> <p class="title"> <b>Name formats</b> </p> <ul> <li> <p> <b>Function name</b> - <code>my-function</code>.</p> </li> <li> <p> <b>Function ARN</b> - <code>arn:aws:lambda:us-west-2:123456789012:function:my-function</code>.</p> </li> <li> <p> <b>Partial ARN</b> - <code>123456789012:function:my-function</code>.</p> </li> </ul> <p>The length constraint applies only to the full ARN. If you specify only the function name, it is limited to 64 characters in length.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString functionName;

    /**
    *  <p>The identifier of the function's <a href="https://docs.aws.amazon.com/lambda/latest/dg/lambda-runtimes.html">runtime</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    EAWSRuntime runtime;

    /**
    *  <p>The Amazon Resource Name (ARN) of the function's execution role.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString role;

    /**
    *  <p>The name of the method within your code that Lambda calls to execute your function. The format includes the file name. It can also include namespaces and other qualifiers, depending on the runtime. For more information, see <a href="https://docs.aws.amazon.com/lambda/latest/dg/programming-model-v2.html">Programming Model</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString handler;

    /**
    *  <p>The code for the function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FFunctionCode code;

    /**
    *  <p>A description of the function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString description;

    /**
    *  <p>The amount of time that Lambda allows a function to run before stopping it. The default is 3 seconds. The maximum allowed value is 900 seconds.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int timeout;

    /**
    *  <p>The amount of memory that your function has access to. Increasing the function's memory also increases its CPU allocation. The default value is 128 MB. The value must be a multiple of 64 MB.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    int memorySize;

    /**
    *  <p>Set to true to publish the first version of the function during creation.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    bool publish;

    /**
    *  <p>For network connectivity to AWS resources in a VPC, specify a list of security groups and subnets in the VPC. When you connect a function to a VPC, it can only access resources and the internet through that VPC. For more information, see <a href="https://docs.aws.amazon.com/lambda/latest/dg/vpc.html">VPC Settings</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FVpcConfig vpcConfig;

    /**
    *  <p>A dead letter queue configuration that specifies the queue or topic where Lambda sends asynchronous events when they fail processing. For more information, see <a href="https://docs.aws.amazon.com/lambda/latest/dg/dlq.html">Dead Letter Queues</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FDeadLetterConfig deadLetterConfig;

    /**
    *  <p>Environment variables that are accessible from function code during execution.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FEnvironment environment;

    /**
    *  <p>The ARN of the AWS Key Management Service (AWS KMS) key that's used to encrypt your function's environment variables. If it's not provided, AWS Lambda uses a default service key.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FString kMSKeyArn;

    /**
    *  <p>Set <code>Mode</code> to <code>Active</code> to sample and trace a subset of incoming requests with AWS X-Ray.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    FTracingConfig tracingConfig;

    /**
    *  <p>A list of <a href="https://docs.aws.amazon.com/lambda/latest/dg/tagging.html">tags</a> to apply to the function.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    TMap<FString, FString> tags;

    /**
    *  <p>A list of <a href="https://docs.aws.amazon.com/lambda/latest/dg/configuration-layers.html">function layers</a> to add to the function's execution environment. Specify each layer by its ARN, including the version.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda Client")
    TArray<FString> layers;

#if WITH_LAMBDACLIENTSDK && WITH_CORE
public:
    Aws::Lambda::Model::CreateFunctionRequest toAWS() const {
        Aws::Lambda::Model::CreateFunctionRequest awsCreateFunctionRequest;

		if (!(this->functionName.IsEmpty())) {
            awsCreateFunctionRequest.SetFunctionName(TCHAR_TO_UTF8(*this->functionName));
        }

        switch(this->runtime) {
            case EAWSRuntime::nodejs:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs);
                break;
            case EAWSRuntime::nodejs4_3:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs4_3);
                break;
            case EAWSRuntime::nodejs6_10:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs6_10);
                break;
            case EAWSRuntime::nodejs8_10:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs8_10);
                break;
            case EAWSRuntime::nodejs10_x:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs10_x);
                break;
            case EAWSRuntime::java8:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::java8);
                break;
            case EAWSRuntime::python2_7:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::python2_7);
                break;
            case EAWSRuntime::python3_6:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::python3_6);
                break;
            case EAWSRuntime::python3_7:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::python3_7);
                break;
            case EAWSRuntime::dotnetcore1_0:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::dotnetcore1_0);
                break;
            case EAWSRuntime::dotnetcore2_0:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::dotnetcore2_0);
                break;
            case EAWSRuntime::dotnetcore2_1:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::dotnetcore2_1);
                break;
            case EAWSRuntime::nodejs4_3_edge:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::nodejs4_3_edge);
                break;
            case EAWSRuntime::go1_x:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::go1_x);
                break;
            case EAWSRuntime::ruby2_5:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::ruby2_5);
                break;
            case EAWSRuntime::provided:
                awsCreateFunctionRequest.SetRuntime(Aws::Lambda::Model::Runtime::provided);
                break;
            default:
                break;
		}

		if (!(this->role.IsEmpty())) {
            awsCreateFunctionRequest.SetRole(TCHAR_TO_UTF8(*this->role));
        }

		if (!(this->handler.IsEmpty())) {
            awsCreateFunctionRequest.SetHandler(TCHAR_TO_UTF8(*this->handler));
        }

        if (!(this->code.IsEmpty())) {
            awsCreateFunctionRequest.SetCode(this->code.toAWS());
        }

		if (!(this->description.IsEmpty())) {
            awsCreateFunctionRequest.SetDescription(TCHAR_TO_UTF8(*this->description));
        }

        if (this->timeout != 0) {
            awsCreateFunctionRequest.SetTimeout(this->timeout);
        }

        if (this->memorySize != 0) {
            awsCreateFunctionRequest.SetMemorySize(this->memorySize);
        }

        awsCreateFunctionRequest.SetPublish(this->publish);

        if (!(this->vpcConfig.IsEmpty())) {
            awsCreateFunctionRequest.SetVpcConfig(this->vpcConfig.toAWS());
        }

        if (!(this->deadLetterConfig.IsEmpty())) {
            awsCreateFunctionRequest.SetDeadLetterConfig(this->deadLetterConfig.toAWS());
        }

        if (!(this->environment.IsEmpty())) {
            awsCreateFunctionRequest.SetEnvironment(this->environment.toAWS());
        }

		if (!(this->kMSKeyArn.IsEmpty())) {
            awsCreateFunctionRequest.SetKMSKeyArn(TCHAR_TO_UTF8(*this->kMSKeyArn));
        }

        if (!(this->tracingConfig.IsEmpty())) {
            awsCreateFunctionRequest.SetTracingConfig(this->tracingConfig.toAWS());
        }

        for (const TPair<FString, FString>& elem : this->tags) {
            awsCreateFunctionRequest.AddTags(TCHAR_TO_UTF8(*elem.Key), TCHAR_TO_UTF8(*elem.Value));
        }

        for (const FString& elem : this->layers) {
            awsCreateFunctionRequest.AddLayers(TCHAR_TO_UTF8(*elem));
        }

        return awsCreateFunctionRequest;
    }

    bool IsEmpty() const {
        return this->functionName.IsEmpty() && this->runtime == EAWSRuntime::NOT_SET && this->role.IsEmpty() && this->handler.IsEmpty() && this->code.IsEmpty() && this->description.IsEmpty() && this->timeout == 0 && this->memorySize == 0 && false && this->vpcConfig.IsEmpty() && this->deadLetterConfig.IsEmpty() && this->environment.IsEmpty() && this->kMSKeyArn.IsEmpty() && this->tracingConfig.IsEmpty() && this->tags.Num() == 0 && this->layers.Num() == 0;
    }
#endif
};
