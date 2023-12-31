/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, November 2019
*/

#include "DynamoDBClientObject.h"
#include "DynamoDBGlobals.h"
#include "DynamoDBPrivatePCH.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "LatentActions.h"

#include "aws/core/utils/Outcome.h"
#include "aws/core/client/AWSError.h"

#endif

#if WITH_DYNAMODBCLIENTSDK

EDynamoDBError fromAWS(Aws::DynamoDB::DynamoDBErrors awsErrorType) {
    switch (awsErrorType) {
        case Aws::DynamoDB::DynamoDBErrors::INCOMPLETE_SIGNATURE:
            return EDynamoDBError::INCOMPLETE_SIGNATURE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INTERNAL_FAILURE:
            return EDynamoDBError::INTERNAL_FAILURE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_ACTION:
            return EDynamoDBError::INVALID_ACTION;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_CLIENT_TOKEN_ID:
            return EDynamoDBError::INVALID_CLIENT_TOKEN_ID;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_PARAMETER_COMBINATION:
            return EDynamoDBError::INVALID_PARAMETER_COMBINATION;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_QUERY_PARAMETER:
            return EDynamoDBError::INVALID_QUERY_PARAMETER;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_PARAMETER_VALUE:
            return EDynamoDBError::INVALID_PARAMETER_VALUE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::MISSING_ACTION:
            return EDynamoDBError::MISSING_ACTION;
            break;
        case Aws::DynamoDB::DynamoDBErrors::MISSING_AUTHENTICATION_TOKEN:
            return EDynamoDBError::MISSING_AUTHENTICATION_TOKEN;
            break;
        case Aws::DynamoDB::DynamoDBErrors::MISSING_PARAMETER:
            return EDynamoDBError::MISSING_PARAMETER;
            break;
        case Aws::DynamoDB::DynamoDBErrors::OPT_IN_REQUIRED:
            return EDynamoDBError::OPT_IN_REQUIRED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REQUEST_EXPIRED:
            return EDynamoDBError::REQUEST_EXPIRED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::SERVICE_UNAVAILABLE:
            return EDynamoDBError::SERVICE_UNAVAILABLE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::THROTTLING:
            return EDynamoDBError::THROTTLING;
            break;
        case Aws::DynamoDB::DynamoDBErrors::VALIDATION:
            return EDynamoDBError::VALIDATION;
            break;
        case Aws::DynamoDB::DynamoDBErrors::ACCESS_DENIED:
            return EDynamoDBError::ACCESS_DENIED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::RESOURCE_NOT_FOUND:
            return EDynamoDBError::RESOURCE_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::UNRECOGNIZED_CLIENT:
            return EDynamoDBError::UNRECOGNIZED_CLIENT;
            break;
        case Aws::DynamoDB::DynamoDBErrors::MALFORMED_QUERY_STRING:
            return EDynamoDBError::MALFORMED_QUERY_STRING;
            break;
        case Aws::DynamoDB::DynamoDBErrors::SLOW_DOWN:
            return EDynamoDBError::SLOW_DOWN;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REQUEST_TIME_TOO_SKEWED:
            return EDynamoDBError::REQUEST_TIME_TOO_SKEWED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_SIGNATURE:
            return EDynamoDBError::INVALID_SIGNATURE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::SIGNATURE_DOES_NOT_MATCH:
            return EDynamoDBError::SIGNATURE_DOES_NOT_MATCH;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_ACCESS_KEY_ID:
            return EDynamoDBError::INVALID_ACCESS_KEY_ID;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REQUEST_TIMEOUT:
            return EDynamoDBError::REQUEST_TIMEOUT;
            break;
        case Aws::DynamoDB::DynamoDBErrors::NETWORK_CONNECTION:
            return EDynamoDBError::NETWORK_CONNECTION;
            break;
        case Aws::DynamoDB::DynamoDBErrors::UNKNOWN:
            return EDynamoDBError::UNKNOWN;
            break;
        case Aws::DynamoDB::DynamoDBErrors::BACKUP_IN_USE:
            return EDynamoDBError::BACKUP_IN_USE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::BACKUP_NOT_FOUND:
            return EDynamoDBError::BACKUP_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::CONDITIONAL_CHECK_FAILED:
            return EDynamoDBError::CONDITIONAL_CHECK_FAILED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::CONTINUOUS_BACKUPS_UNAVAILABLE:
            return EDynamoDBError::CONTINUOUS_BACKUPS_UNAVAILABLE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::GLOBAL_TABLE_ALREADY_EXISTS:
            return EDynamoDBError::GLOBAL_TABLE_ALREADY_EXISTS;
            break;
        case Aws::DynamoDB::DynamoDBErrors::GLOBAL_TABLE_NOT_FOUND:
            return EDynamoDBError::GLOBAL_TABLE_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::IDEMPOTENT_PARAMETER_MISMATCH:
            return EDynamoDBError::IDEMPOTENT_PARAMETER_MISMATCH;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INDEX_NOT_FOUND:
            return EDynamoDBError::INDEX_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::INVALID_RESTORE_TIME:
            return EDynamoDBError::INVALID_RESTORE_TIME;
            break;
        case Aws::DynamoDB::DynamoDBErrors::ITEM_COLLECTION_SIZE_LIMIT_EXCEEDED:
            return EDynamoDBError::ITEM_COLLECTION_SIZE_LIMIT_EXCEEDED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::LIMIT_EXCEEDED:
            return EDynamoDBError::LIMIT_EXCEEDED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::POINT_IN_TIME_RECOVERY_UNAVAILABLE:
            return EDynamoDBError::POINT_IN_TIME_RECOVERY_UNAVAILABLE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::PROVISIONED_THROUGHPUT_EXCEEDED:
            return EDynamoDBError::PROVISIONED_THROUGHPUT_EXCEEDED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REPLICA_ALREADY_EXISTS:
            return EDynamoDBError::REPLICA_ALREADY_EXISTS;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REPLICA_NOT_FOUND:
            return EDynamoDBError::REPLICA_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::REQUEST_LIMIT_EXCEEDED:
            return EDynamoDBError::REQUEST_LIMIT_EXCEEDED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::RESOURCE_IN_USE:
            return EDynamoDBError::RESOURCE_IN_USE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TABLE_ALREADY_EXISTS:
            return EDynamoDBError::TABLE_ALREADY_EXISTS;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TABLE_IN_USE:
            return EDynamoDBError::TABLE_IN_USE;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TABLE_NOT_FOUND:
            return EDynamoDBError::TABLE_NOT_FOUND;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TRANSACTION_CANCELED:
            return EDynamoDBError::TRANSACTION_CANCELED;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TRANSACTION_CONFLICT:
            return EDynamoDBError::TRANSACTION_CONFLICT;
            break;
        case Aws::DynamoDB::DynamoDBErrors::TRANSACTION_IN_PROGRESS:
            return EDynamoDBError::TRANSACTION_IN_PROGRESS;
            break;
        default:
            return EDynamoDBError::UNKNOWN;
            break;
    }
}

#endif

UDynamoDBClientObject *UDynamoDBClientObject::CreateDynamoDBObject(
const FAWSCredentials &credentials,
const FAWSClientConfiguration &clientConfiguration
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    UDynamoDBClientObject *DynamoDBClient = NewObject<UDynamoDBClientObject>();
    DynamoDBClient->awsDynamoDBClient = new Aws::DynamoDB::DynamoDBClient(credentials.toAWS(),
    clientConfiguration.toAWS());
    return DynamoDBClient;
#endif
    return nullptr;
}

FString UDynamoDBClientObject::GetServiceClientName() const {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    return this->awsDynamoDBClient->GetServiceClientName();
#endif
    return FString();
}

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FBatchGetItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FBatchGetItemRequest batchGetItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FBatchGetItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FBatchGetItemRequest batchGetItemRequest,
        FBatchGetItemResult &batchGetItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), batchGetItemRequest(batchGetItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->BatchGetItemAsync(
            batchGetItemRequest.toAWS(),
            [&success, &batchGetItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::BatchGetItemRequest &awsBatchGetItemRequest,
                const Aws::DynamoDB::Model::BatchGetItemOutcome &awsBatchGetItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsBatchGetItemOutcome.IsSuccess();
                if (success) {
                    batchGetItemResult.fromAWS(awsBatchGetItemOutcome.GetResult());
                }

                errorType = fromAWS(awsBatchGetItemOutcome.GetError().GetErrorType());
                errorMessage = awsBatchGetItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("BatchGetItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::BatchGetItem(
    UObject *WorldContextObject,
    bool &success,
    FBatchGetItemRequest batchGetItemRequest,
    FBatchGetItemResult &batchGetItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FBatchGetItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FBatchGetItemAction(this->awsDynamoDBClient,
                success,
                batchGetItemRequest,
                batchGetItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FBatchWriteItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FBatchWriteItemRequest batchWriteItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FBatchWriteItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FBatchWriteItemRequest batchWriteItemRequest,
        FBatchWriteItemResult &batchWriteItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), batchWriteItemRequest(batchWriteItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->BatchWriteItemAsync(
            batchWriteItemRequest.toAWS(),
            [&success, &batchWriteItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::BatchWriteItemRequest &awsBatchWriteItemRequest,
                const Aws::DynamoDB::Model::BatchWriteItemOutcome &awsBatchWriteItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsBatchWriteItemOutcome.IsSuccess();
                if (success) {
                    batchWriteItemResult.fromAWS(awsBatchWriteItemOutcome.GetResult());
                }

                errorType = fromAWS(awsBatchWriteItemOutcome.GetError().GetErrorType());
                errorMessage = awsBatchWriteItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("BatchWriteItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::BatchWriteItem(
    UObject *WorldContextObject,
    bool &success,
    FBatchWriteItemRequest batchWriteItemRequest,
    FBatchWriteItemResult &batchWriteItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FBatchWriteItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FBatchWriteItemAction(this->awsDynamoDBClient,
                success,
                batchWriteItemRequest,
                batchWriteItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FCreateBackupAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FCreateBackupRequest createBackupRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateBackupAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FCreateBackupRequest createBackupRequest,
        FCreateBackupResult &createBackupResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), createBackupRequest(createBackupRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->CreateBackupAsync(
            createBackupRequest.toAWS(),
            [&success, &createBackupResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::CreateBackupRequest &awsCreateBackupRequest,
                const Aws::DynamoDB::Model::CreateBackupOutcome &awsCreateBackupOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsCreateBackupOutcome.IsSuccess();
                if (success) {
                    createBackupResult.fromAWS(awsCreateBackupOutcome.GetResult());
                }

                errorType = fromAWS(awsCreateBackupOutcome.GetError().GetErrorType());
                errorMessage = awsCreateBackupOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateBackup Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::CreateBackup(
    UObject *WorldContextObject,
    bool &success,
    FCreateBackupRequest createBackupRequest,
    FCreateBackupResult &createBackupResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateBackupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateBackupAction(this->awsDynamoDBClient,
                success,
                createBackupRequest,
                createBackupResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FCreateGlobalTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FCreateGlobalTableRequest createGlobalTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateGlobalTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FCreateGlobalTableRequest createGlobalTableRequest,
        FCreateGlobalTableResult &createGlobalTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), createGlobalTableRequest(createGlobalTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->CreateGlobalTableAsync(
            createGlobalTableRequest.toAWS(),
            [&success, &createGlobalTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::CreateGlobalTableRequest &awsCreateGlobalTableRequest,
                const Aws::DynamoDB::Model::CreateGlobalTableOutcome &awsCreateGlobalTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsCreateGlobalTableOutcome.IsSuccess();
                if (success) {
                    createGlobalTableResult.fromAWS(awsCreateGlobalTableOutcome.GetResult());
                }

                errorType = fromAWS(awsCreateGlobalTableOutcome.GetError().GetErrorType());
                errorMessage = awsCreateGlobalTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateGlobalTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::CreateGlobalTable(
    UObject *WorldContextObject,
    bool &success,
    FCreateGlobalTableRequest createGlobalTableRequest,
    FCreateGlobalTableResult &createGlobalTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateGlobalTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateGlobalTableAction(this->awsDynamoDBClient,
                success,
                createGlobalTableRequest,
                createGlobalTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FCreateTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FCreateTableRequest createTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FCreateTableRequest createTableRequest,
        FCreateTableResult &createTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), createTableRequest(createTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->CreateTableAsync(
            createTableRequest.toAWS(),
            [&success, &createTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::CreateTableRequest &awsCreateTableRequest,
                const Aws::DynamoDB::Model::CreateTableOutcome &awsCreateTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsCreateTableOutcome.IsSuccess();
                if (success) {
                    createTableResult.fromAWS(awsCreateTableOutcome.GetResult());
                }

                errorType = fromAWS(awsCreateTableOutcome.GetError().GetErrorType());
                errorMessage = awsCreateTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::CreateTable(
    UObject *WorldContextObject,
    bool &success,
    FCreateTableRequest createTableRequest,
    FCreateTableResult &createTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateTableAction(this->awsDynamoDBClient,
                success,
                createTableRequest,
                createTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDeleteBackupAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDeleteBackupRequest deleteBackupRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteBackupAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDeleteBackupRequest deleteBackupRequest,
        FDeleteBackupResult &deleteBackupResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), deleteBackupRequest(deleteBackupRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DeleteBackupAsync(
            deleteBackupRequest.toAWS(),
            [&success, &deleteBackupResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DeleteBackupRequest &awsDeleteBackupRequest,
                const Aws::DynamoDB::Model::DeleteBackupOutcome &awsDeleteBackupOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDeleteBackupOutcome.IsSuccess();
                if (success) {
                    deleteBackupResult.fromAWS(awsDeleteBackupOutcome.GetResult());
                }

                errorType = fromAWS(awsDeleteBackupOutcome.GetError().GetErrorType());
                errorMessage = awsDeleteBackupOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteBackup Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DeleteBackup(
    UObject *WorldContextObject,
    bool &success,
    FDeleteBackupRequest deleteBackupRequest,
    FDeleteBackupResult &deleteBackupResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteBackupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteBackupAction(this->awsDynamoDBClient,
                success,
                deleteBackupRequest,
                deleteBackupResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDeleteItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDeleteItemRequest deleteItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDeleteItemRequest deleteItemRequest,
        FDeleteItemResult &deleteItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), deleteItemRequest(deleteItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DeleteItemAsync(
            deleteItemRequest.toAWS(),
            [&success, &deleteItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DeleteItemRequest &awsDeleteItemRequest,
                const Aws::DynamoDB::Model::DeleteItemOutcome &awsDeleteItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDeleteItemOutcome.IsSuccess();
                if (success) {
                    deleteItemResult.fromAWS(awsDeleteItemOutcome.GetResult());
                }

                errorType = fromAWS(awsDeleteItemOutcome.GetError().GetErrorType());
                errorMessage = awsDeleteItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DeleteItem(
    UObject *WorldContextObject,
    bool &success,
    FDeleteItemRequest deleteItemRequest,
    FDeleteItemResult &deleteItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteItemAction(this->awsDynamoDBClient,
                success,
                deleteItemRequest,
                deleteItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDeleteTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDeleteTableRequest deleteTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDeleteTableRequest deleteTableRequest,
        FDeleteTableResult &deleteTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), deleteTableRequest(deleteTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DeleteTableAsync(
            deleteTableRequest.toAWS(),
            [&success, &deleteTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DeleteTableRequest &awsDeleteTableRequest,
                const Aws::DynamoDB::Model::DeleteTableOutcome &awsDeleteTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDeleteTableOutcome.IsSuccess();
                if (success) {
                    deleteTableResult.fromAWS(awsDeleteTableOutcome.GetResult());
                }

                errorType = fromAWS(awsDeleteTableOutcome.GetError().GetErrorType());
                errorMessage = awsDeleteTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DeleteTable(
    UObject *WorldContextObject,
    bool &success,
    FDeleteTableRequest deleteTableRequest,
    FDeleteTableResult &deleteTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteTableAction(this->awsDynamoDBClient,
                success,
                deleteTableRequest,
                deleteTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeBackupAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeBackupRequest describeBackupRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeBackupAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeBackupRequest describeBackupRequest,
        FDescribeBackupResult &describeBackupResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeBackupRequest(describeBackupRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeBackupAsync(
            describeBackupRequest.toAWS(),
            [&success, &describeBackupResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeBackupRequest &awsDescribeBackupRequest,
                const Aws::DynamoDB::Model::DescribeBackupOutcome &awsDescribeBackupOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeBackupOutcome.IsSuccess();
                if (success) {
                    describeBackupResult.fromAWS(awsDescribeBackupOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeBackupOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeBackupOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeBackup Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeBackup(
    UObject *WorldContextObject,
    bool &success,
    FDescribeBackupRequest describeBackupRequest,
    FDescribeBackupResult &describeBackupResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeBackupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeBackupAction(this->awsDynamoDBClient,
                success,
                describeBackupRequest,
                describeBackupResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeContinuousBackupsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeContinuousBackupsRequest describeContinuousBackupsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeContinuousBackupsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeContinuousBackupsRequest describeContinuousBackupsRequest,
        FDescribeContinuousBackupsResult &describeContinuousBackupsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeContinuousBackupsRequest(describeContinuousBackupsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeContinuousBackupsAsync(
            describeContinuousBackupsRequest.toAWS(),
            [&success, &describeContinuousBackupsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeContinuousBackupsRequest &awsDescribeContinuousBackupsRequest,
                const Aws::DynamoDB::Model::DescribeContinuousBackupsOutcome &awsDescribeContinuousBackupsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeContinuousBackupsOutcome.IsSuccess();
                if (success) {
                    describeContinuousBackupsResult.fromAWS(awsDescribeContinuousBackupsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeContinuousBackupsOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeContinuousBackupsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeContinuousBackups Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeContinuousBackups(
    UObject *WorldContextObject,
    bool &success,
    FDescribeContinuousBackupsRequest describeContinuousBackupsRequest,
    FDescribeContinuousBackupsResult &describeContinuousBackupsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeContinuousBackupsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeContinuousBackupsAction(this->awsDynamoDBClient,
                success,
                describeContinuousBackupsRequest,
                describeContinuousBackupsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeEndpointsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeEndpointsRequest describeEndpointsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeEndpointsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeEndpointsRequest describeEndpointsRequest,
        FDescribeEndpointsResult &describeEndpointsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeEndpointsRequest(describeEndpointsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeEndpointsAsync(
            describeEndpointsRequest.toAWS(),
            [&success, &describeEndpointsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeEndpointsRequest &awsDescribeEndpointsRequest,
                const Aws::DynamoDB::Model::DescribeEndpointsOutcome &awsDescribeEndpointsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeEndpointsOutcome.IsSuccess();
                if (success) {
                    describeEndpointsResult.fromAWS(awsDescribeEndpointsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeEndpointsOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeEndpointsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeEndpoints Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeEndpoints(
    UObject *WorldContextObject,
    bool &success,
    FDescribeEndpointsRequest describeEndpointsRequest,
    FDescribeEndpointsResult &describeEndpointsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeEndpointsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeEndpointsAction(this->awsDynamoDBClient,
                success,
                describeEndpointsRequest,
                describeEndpointsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeGlobalTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeGlobalTableRequest describeGlobalTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGlobalTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeGlobalTableRequest describeGlobalTableRequest,
        FDescribeGlobalTableResult &describeGlobalTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeGlobalTableRequest(describeGlobalTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeGlobalTableAsync(
            describeGlobalTableRequest.toAWS(),
            [&success, &describeGlobalTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeGlobalTableRequest &awsDescribeGlobalTableRequest,
                const Aws::DynamoDB::Model::DescribeGlobalTableOutcome &awsDescribeGlobalTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeGlobalTableOutcome.IsSuccess();
                if (success) {
                    describeGlobalTableResult.fromAWS(awsDescribeGlobalTableOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeGlobalTableOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeGlobalTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeGlobalTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeGlobalTable(
    UObject *WorldContextObject,
    bool &success,
    FDescribeGlobalTableRequest describeGlobalTableRequest,
    FDescribeGlobalTableResult &describeGlobalTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGlobalTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeGlobalTableAction(this->awsDynamoDBClient,
                success,
                describeGlobalTableRequest,
                describeGlobalTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeGlobalTableSettingsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeGlobalTableSettingsRequest describeGlobalTableSettingsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGlobalTableSettingsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeGlobalTableSettingsRequest describeGlobalTableSettingsRequest,
        FDescribeGlobalTableSettingsResult &describeGlobalTableSettingsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeGlobalTableSettingsRequest(describeGlobalTableSettingsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeGlobalTableSettingsAsync(
            describeGlobalTableSettingsRequest.toAWS(),
            [&success, &describeGlobalTableSettingsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeGlobalTableSettingsRequest &awsDescribeGlobalTableSettingsRequest,
                const Aws::DynamoDB::Model::DescribeGlobalTableSettingsOutcome &awsDescribeGlobalTableSettingsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeGlobalTableSettingsOutcome.IsSuccess();
                if (success) {
                    describeGlobalTableSettingsResult.fromAWS(awsDescribeGlobalTableSettingsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeGlobalTableSettingsOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeGlobalTableSettingsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeGlobalTableSettings Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeGlobalTableSettings(
    UObject *WorldContextObject,
    bool &success,
    FDescribeGlobalTableSettingsRequest describeGlobalTableSettingsRequest,
    FDescribeGlobalTableSettingsResult &describeGlobalTableSettingsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGlobalTableSettingsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeGlobalTableSettingsAction(this->awsDynamoDBClient,
                success,
                describeGlobalTableSettingsRequest,
                describeGlobalTableSettingsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeLimitsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeLimitsRequest describeLimitsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeLimitsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeLimitsRequest describeLimitsRequest,
        FDescribeLimitsResult &describeLimitsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeLimitsRequest(describeLimitsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeLimitsAsync(
            describeLimitsRequest.toAWS(),
            [&success, &describeLimitsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeLimitsRequest &awsDescribeLimitsRequest,
                const Aws::DynamoDB::Model::DescribeLimitsOutcome &awsDescribeLimitsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeLimitsOutcome.IsSuccess();
                if (success) {
                    describeLimitsResult.fromAWS(awsDescribeLimitsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeLimitsOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeLimitsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeLimits Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeLimits(
    UObject *WorldContextObject,
    bool &success,
    FDescribeLimitsRequest describeLimitsRequest,
    FDescribeLimitsResult &describeLimitsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeLimitsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeLimitsAction(this->awsDynamoDBClient,
                success,
                describeLimitsRequest,
                describeLimitsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeTableRequest describeTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeTableRequest describeTableRequest,
        FDescribeTableResult &describeTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeTableRequest(describeTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeTableAsync(
            describeTableRequest.toAWS(),
            [&success, &describeTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeTableRequest &awsDescribeTableRequest,
                const Aws::DynamoDB::Model::DescribeTableOutcome &awsDescribeTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeTableOutcome.IsSuccess();
                if (success) {
                    describeTableResult.fromAWS(awsDescribeTableOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeTableOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeTable(
    UObject *WorldContextObject,
    bool &success,
    FDescribeTableRequest describeTableRequest,
    FDescribeTableResult &describeTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeTableAction(this->awsDynamoDBClient,
                success,
                describeTableRequest,
                describeTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FDescribeTimeToLiveAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDescribeTimeToLiveRequest describeTimeToLiveRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeTimeToLiveAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDescribeTimeToLiveRequest describeTimeToLiveRequest,
        FDescribeTimeToLiveResult &describeTimeToLiveResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), describeTimeToLiveRequest(describeTimeToLiveRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->DescribeTimeToLiveAsync(
            describeTimeToLiveRequest.toAWS(),
            [&success, &describeTimeToLiveResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::DescribeTimeToLiveRequest &awsDescribeTimeToLiveRequest,
                const Aws::DynamoDB::Model::DescribeTimeToLiveOutcome &awsDescribeTimeToLiveOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsDescribeTimeToLiveOutcome.IsSuccess();
                if (success) {
                    describeTimeToLiveResult.fromAWS(awsDescribeTimeToLiveOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeTimeToLiveOutcome.GetError().GetErrorType());
                errorMessage = awsDescribeTimeToLiveOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeTimeToLive Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::DescribeTimeToLive(
    UObject *WorldContextObject,
    bool &success,
    FDescribeTimeToLiveRequest describeTimeToLiveRequest,
    FDescribeTimeToLiveResult &describeTimeToLiveResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeTimeToLiveAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeTimeToLiveAction(this->awsDynamoDBClient,
                success,
                describeTimeToLiveRequest,
                describeTimeToLiveResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FGetItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FGetItemRequest getItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FGetItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FGetItemRequest getItemRequest,
        FGetItemResult &getItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), getItemRequest(getItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->GetItemAsync(
            getItemRequest.toAWS(),
            [&success, &getItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::GetItemRequest &awsGetItemRequest,
                const Aws::DynamoDB::Model::GetItemOutcome &awsGetItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsGetItemOutcome.IsSuccess();
                if (success) {
                    getItemResult.fromAWS(awsGetItemOutcome.GetResult());
                }

                errorType = fromAWS(awsGetItemOutcome.GetError().GetErrorType());
                errorMessage = awsGetItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::GetItem(
    UObject *WorldContextObject,
    bool &success,
    FGetItemRequest getItemRequest,
    FGetItemResult &getItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetItemAction(this->awsDynamoDBClient,
                success,
                getItemRequest,
                getItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FListBackupsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FListBackupsRequest listBackupsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListBackupsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FListBackupsRequest listBackupsRequest,
        FListBackupsResult &listBackupsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), listBackupsRequest(listBackupsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->ListBackupsAsync(
            listBackupsRequest.toAWS(),
            [&success, &listBackupsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::ListBackupsRequest &awsListBackupsRequest,
                const Aws::DynamoDB::Model::ListBackupsOutcome &awsListBackupsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsListBackupsOutcome.IsSuccess();
                if (success) {
                    listBackupsResult.fromAWS(awsListBackupsOutcome.GetResult());
                }

                errorType = fromAWS(awsListBackupsOutcome.GetError().GetErrorType());
                errorMessage = awsListBackupsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("ListBackups Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::ListBackups(
    UObject *WorldContextObject,
    bool &success,
    FListBackupsRequest listBackupsRequest,
    FListBackupsResult &listBackupsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListBackupsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FListBackupsAction(this->awsDynamoDBClient,
                success,
                listBackupsRequest,
                listBackupsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FListGlobalTablesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FListGlobalTablesRequest listGlobalTablesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListGlobalTablesAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FListGlobalTablesRequest listGlobalTablesRequest,
        FListGlobalTablesResult &listGlobalTablesResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), listGlobalTablesRequest(listGlobalTablesRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->ListGlobalTablesAsync(
            listGlobalTablesRequest.toAWS(),
            [&success, &listGlobalTablesResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::ListGlobalTablesRequest &awsListGlobalTablesRequest,
                const Aws::DynamoDB::Model::ListGlobalTablesOutcome &awsListGlobalTablesOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsListGlobalTablesOutcome.IsSuccess();
                if (success) {
                    listGlobalTablesResult.fromAWS(awsListGlobalTablesOutcome.GetResult());
                }

                errorType = fromAWS(awsListGlobalTablesOutcome.GetError().GetErrorType());
                errorMessage = awsListGlobalTablesOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("ListGlobalTables Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::ListGlobalTables(
    UObject *WorldContextObject,
    bool &success,
    FListGlobalTablesRequest listGlobalTablesRequest,
    FListGlobalTablesResult &listGlobalTablesResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListGlobalTablesAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FListGlobalTablesAction(this->awsDynamoDBClient,
                success,
                listGlobalTablesRequest,
                listGlobalTablesResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FListTablesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FListTablesRequest listTablesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListTablesAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FListTablesRequest listTablesRequest,
        FListTablesResult &listTablesResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), listTablesRequest(listTablesRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->ListTablesAsync(
            listTablesRequest.toAWS(),
            [&success, &listTablesResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::ListTablesRequest &awsListTablesRequest,
                const Aws::DynamoDB::Model::ListTablesOutcome &awsListTablesOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsListTablesOutcome.IsSuccess();
                if (success) {
                    listTablesResult.fromAWS(awsListTablesOutcome.GetResult());
                }

                errorType = fromAWS(awsListTablesOutcome.GetError().GetErrorType());
                errorMessage = awsListTablesOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("ListTables Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::ListTables(
    UObject *WorldContextObject,
    bool &success,
    FListTablesRequest listTablesRequest,
    FListTablesResult &listTablesResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListTablesAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FListTablesAction(this->awsDynamoDBClient,
                success,
                listTablesRequest,
                listTablesResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FListTagsOfResourceAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FListTagsOfResourceRequest listTagsOfResourceRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListTagsOfResourceAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FListTagsOfResourceRequest listTagsOfResourceRequest,
        FListTagsOfResourceResult &listTagsOfResourceResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), listTagsOfResourceRequest(listTagsOfResourceRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->ListTagsOfResourceAsync(
            listTagsOfResourceRequest.toAWS(),
            [&success, &listTagsOfResourceResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::ListTagsOfResourceRequest &awsListTagsOfResourceRequest,
                const Aws::DynamoDB::Model::ListTagsOfResourceOutcome &awsListTagsOfResourceOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsListTagsOfResourceOutcome.IsSuccess();
                if (success) {
                    listTagsOfResourceResult.fromAWS(awsListTagsOfResourceOutcome.GetResult());
                }

                errorType = fromAWS(awsListTagsOfResourceOutcome.GetError().GetErrorType());
                errorMessage = awsListTagsOfResourceOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("ListTagsOfResource Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::ListTagsOfResource(
    UObject *WorldContextObject,
    bool &success,
    FListTagsOfResourceRequest listTagsOfResourceRequest,
    FListTagsOfResourceResult &listTagsOfResourceResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListTagsOfResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FListTagsOfResourceAction(this->awsDynamoDBClient,
                success,
                listTagsOfResourceRequest,
                listTagsOfResourceResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FPutItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FPutItemRequest putItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FPutItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FPutItemRequest putItemRequest,
        FPutItemResult &putItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), putItemRequest(putItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->PutItemAsync(
            putItemRequest.toAWS(),
            [&success, &putItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::PutItemRequest &awsPutItemRequest,
                const Aws::DynamoDB::Model::PutItemOutcome &awsPutItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsPutItemOutcome.IsSuccess();
                if (success) {
                    putItemResult.fromAWS(awsPutItemOutcome.GetResult());
                }

                errorType = fromAWS(awsPutItemOutcome.GetError().GetErrorType());
                errorMessage = awsPutItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::PutItem(
    UObject *WorldContextObject,
    bool &success,
    FPutItemRequest putItemRequest,
    FPutItemResult &putItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutItemAction(this->awsDynamoDBClient,
                success,
                putItemRequest,
                putItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FQueryAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FQueryRequest queryRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FQueryAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FQueryRequest queryRequest,
        FQueryResult &queryResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), queryRequest(queryRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->QueryAsync(
            queryRequest.toAWS(),
            [&success, &queryResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::QueryRequest &awsQueryRequest,
                const Aws::DynamoDB::Model::QueryOutcome &awsQueryOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsQueryOutcome.IsSuccess();
                if (success) {
                    queryResult.fromAWS(awsQueryOutcome.GetResult());
                }

                errorType = fromAWS(awsQueryOutcome.GetError().GetErrorType());
                errorMessage = awsQueryOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Query Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::Query(
    UObject *WorldContextObject,
    bool &success,
    FQueryRequest queryRequest,
    FQueryResult &queryResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FQueryAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FQueryAction(this->awsDynamoDBClient,
                success,
                queryRequest,
                queryResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FRestoreTableFromBackupAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FRestoreTableFromBackupRequest restoreTableFromBackupRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FRestoreTableFromBackupAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FRestoreTableFromBackupRequest restoreTableFromBackupRequest,
        FRestoreTableFromBackupResult &restoreTableFromBackupResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), restoreTableFromBackupRequest(restoreTableFromBackupRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->RestoreTableFromBackupAsync(
            restoreTableFromBackupRequest.toAWS(),
            [&success, &restoreTableFromBackupResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::RestoreTableFromBackupRequest &awsRestoreTableFromBackupRequest,
                const Aws::DynamoDB::Model::RestoreTableFromBackupOutcome &awsRestoreTableFromBackupOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsRestoreTableFromBackupOutcome.IsSuccess();
                if (success) {
                    restoreTableFromBackupResult.fromAWS(awsRestoreTableFromBackupOutcome.GetResult());
                }

                errorType = fromAWS(awsRestoreTableFromBackupOutcome.GetError().GetErrorType());
                errorMessage = awsRestoreTableFromBackupOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("RestoreTableFromBackup Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::RestoreTableFromBackup(
    UObject *WorldContextObject,
    bool &success,
    FRestoreTableFromBackupRequest restoreTableFromBackupRequest,
    FRestoreTableFromBackupResult &restoreTableFromBackupResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FRestoreTableFromBackupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FRestoreTableFromBackupAction(this->awsDynamoDBClient,
                success,
                restoreTableFromBackupRequest,
                restoreTableFromBackupResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FRestoreTableToPointInTimeAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FRestoreTableToPointInTimeRequest restoreTableToPointInTimeRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FRestoreTableToPointInTimeAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FRestoreTableToPointInTimeRequest restoreTableToPointInTimeRequest,
        FRestoreTableToPointInTimeResult &restoreTableToPointInTimeResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), restoreTableToPointInTimeRequest(restoreTableToPointInTimeRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->RestoreTableToPointInTimeAsync(
            restoreTableToPointInTimeRequest.toAWS(),
            [&success, &restoreTableToPointInTimeResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::RestoreTableToPointInTimeRequest &awsRestoreTableToPointInTimeRequest,
                const Aws::DynamoDB::Model::RestoreTableToPointInTimeOutcome &awsRestoreTableToPointInTimeOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsRestoreTableToPointInTimeOutcome.IsSuccess();
                if (success) {
                    restoreTableToPointInTimeResult.fromAWS(awsRestoreTableToPointInTimeOutcome.GetResult());
                }

                errorType = fromAWS(awsRestoreTableToPointInTimeOutcome.GetError().GetErrorType());
                errorMessage = awsRestoreTableToPointInTimeOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("RestoreTableToPointInTime Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::RestoreTableToPointInTime(
    UObject *WorldContextObject,
    bool &success,
    FRestoreTableToPointInTimeRequest restoreTableToPointInTimeRequest,
    FRestoreTableToPointInTimeResult &restoreTableToPointInTimeResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FRestoreTableToPointInTimeAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FRestoreTableToPointInTimeAction(this->awsDynamoDBClient,
                success,
                restoreTableToPointInTimeRequest,
                restoreTableToPointInTimeResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FScanAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FScanRequest scanRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FScanAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FScanRequest scanRequest,
        FScanResult &scanResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), scanRequest(scanRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->ScanAsync(
            scanRequest.toAWS(),
            [&success, &scanResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::ScanRequest &awsScanRequest,
                const Aws::DynamoDB::Model::ScanOutcome &awsScanOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsScanOutcome.IsSuccess();
                if (success) {
                    scanResult.fromAWS(awsScanOutcome.GetResult());
                }

                errorType = fromAWS(awsScanOutcome.GetError().GetErrorType());
                errorMessage = awsScanOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Scan Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::Scan(
    UObject *WorldContextObject,
    bool &success,
    FScanRequest scanRequest,
    FScanResult &scanResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FScanAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FScanAction(this->awsDynamoDBClient,
                success,
                scanRequest,
                scanResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FTagResourceAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDynamoDBTagResourceRequest tagResourceRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FTagResourceAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDynamoDBTagResourceRequest tagResourceRequest,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), tagResourceRequest(tagResourceRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->TagResourceAsync(
            tagResourceRequest.toAWS(),
            [&success, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::TagResourceRequest &awsTagResourceRequest,
                const Aws::DynamoDB::Model::TagResourceOutcome &awsTagResourceOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsTagResourceOutcome.IsSuccess();

                errorType = fromAWS(awsTagResourceOutcome.GetError().GetErrorType());
                errorMessage = awsTagResourceOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("TagResource Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::TagResource(
    UObject *WorldContextObject,
    bool &success,
    FDynamoDBTagResourceRequest tagResourceRequest,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FTagResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FTagResourceAction(this->awsDynamoDBClient,
                success,
                tagResourceRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FTransactGetItemsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FTransactGetItemsRequest transactGetItemsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FTransactGetItemsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FTransactGetItemsRequest transactGetItemsRequest,
        FTransactGetItemsResult &transactGetItemsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), transactGetItemsRequest(transactGetItemsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->TransactGetItemsAsync(
            transactGetItemsRequest.toAWS(),
            [&success, &transactGetItemsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::TransactGetItemsRequest &awsTransactGetItemsRequest,
                const Aws::DynamoDB::Model::TransactGetItemsOutcome &awsTransactGetItemsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsTransactGetItemsOutcome.IsSuccess();
                if (success) {
                    transactGetItemsResult.fromAWS(awsTransactGetItemsOutcome.GetResult());
                }

                errorType = fromAWS(awsTransactGetItemsOutcome.GetError().GetErrorType());
                errorMessage = awsTransactGetItemsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("TransactGetItems Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::TransactGetItems(
    UObject *WorldContextObject,
    bool &success,
    FTransactGetItemsRequest transactGetItemsRequest,
    FTransactGetItemsResult &transactGetItemsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FTransactGetItemsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FTransactGetItemsAction(this->awsDynamoDBClient,
                success,
                transactGetItemsRequest,
                transactGetItemsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FTransactWriteItemsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FTransactWriteItemsRequest transactWriteItemsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FTransactWriteItemsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FTransactWriteItemsRequest transactWriteItemsRequest,
        FTransactWriteItemsResult &transactWriteItemsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), transactWriteItemsRequest(transactWriteItemsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->TransactWriteItemsAsync(
            transactWriteItemsRequest.toAWS(),
            [&success, &transactWriteItemsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::TransactWriteItemsRequest &awsTransactWriteItemsRequest,
                const Aws::DynamoDB::Model::TransactWriteItemsOutcome &awsTransactWriteItemsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsTransactWriteItemsOutcome.IsSuccess();
                if (success) {
                    transactWriteItemsResult.fromAWS(awsTransactWriteItemsOutcome.GetResult());
                }

                errorType = fromAWS(awsTransactWriteItemsOutcome.GetError().GetErrorType());
                errorMessage = awsTransactWriteItemsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("TransactWriteItems Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::TransactWriteItems(
    UObject *WorldContextObject,
    bool &success,
    FTransactWriteItemsRequest transactWriteItemsRequest,
    FTransactWriteItemsResult &transactWriteItemsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FTransactWriteItemsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FTransactWriteItemsAction(this->awsDynamoDBClient,
                success,
                transactWriteItemsRequest,
                transactWriteItemsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUntagResourceAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FDynamoDBUntagResourceRequest untagResourceRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUntagResourceAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FDynamoDBUntagResourceRequest untagResourceRequest,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), untagResourceRequest(untagResourceRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UntagResourceAsync(
            untagResourceRequest.toAWS(),
            [&success, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UntagResourceRequest &awsUntagResourceRequest,
                const Aws::DynamoDB::Model::UntagResourceOutcome &awsUntagResourceOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUntagResourceOutcome.IsSuccess();

                errorType = fromAWS(awsUntagResourceOutcome.GetError().GetErrorType());
                errorMessage = awsUntagResourceOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UntagResource Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UntagResource(
    UObject *WorldContextObject,
    bool &success,
    FDynamoDBUntagResourceRequest untagResourceRequest,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUntagResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUntagResourceAction(this->awsDynamoDBClient,
                success,
                untagResourceRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateContinuousBackupsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateContinuousBackupsRequest updateContinuousBackupsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateContinuousBackupsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateContinuousBackupsRequest updateContinuousBackupsRequest,
        FUpdateContinuousBackupsResult &updateContinuousBackupsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateContinuousBackupsRequest(updateContinuousBackupsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateContinuousBackupsAsync(
            updateContinuousBackupsRequest.toAWS(),
            [&success, &updateContinuousBackupsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateContinuousBackupsRequest &awsUpdateContinuousBackupsRequest,
                const Aws::DynamoDB::Model::UpdateContinuousBackupsOutcome &awsUpdateContinuousBackupsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateContinuousBackupsOutcome.IsSuccess();
                if (success) {
                    updateContinuousBackupsResult.fromAWS(awsUpdateContinuousBackupsOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateContinuousBackupsOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateContinuousBackupsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateContinuousBackups Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateContinuousBackups(
    UObject *WorldContextObject,
    bool &success,
    FUpdateContinuousBackupsRequest updateContinuousBackupsRequest,
    FUpdateContinuousBackupsResult &updateContinuousBackupsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateContinuousBackupsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateContinuousBackupsAction(this->awsDynamoDBClient,
                success,
                updateContinuousBackupsRequest,
                updateContinuousBackupsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateGlobalTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateGlobalTableRequest updateGlobalTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateGlobalTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateGlobalTableRequest updateGlobalTableRequest,
        FUpdateGlobalTableResult &updateGlobalTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateGlobalTableRequest(updateGlobalTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateGlobalTableAsync(
            updateGlobalTableRequest.toAWS(),
            [&success, &updateGlobalTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateGlobalTableRequest &awsUpdateGlobalTableRequest,
                const Aws::DynamoDB::Model::UpdateGlobalTableOutcome &awsUpdateGlobalTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateGlobalTableOutcome.IsSuccess();
                if (success) {
                    updateGlobalTableResult.fromAWS(awsUpdateGlobalTableOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateGlobalTableOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateGlobalTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateGlobalTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateGlobalTable(
    UObject *WorldContextObject,
    bool &success,
    FUpdateGlobalTableRequest updateGlobalTableRequest,
    FUpdateGlobalTableResult &updateGlobalTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateGlobalTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateGlobalTableAction(this->awsDynamoDBClient,
                success,
                updateGlobalTableRequest,
                updateGlobalTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateGlobalTableSettingsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateGlobalTableSettingsRequest updateGlobalTableSettingsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateGlobalTableSettingsAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateGlobalTableSettingsRequest updateGlobalTableSettingsRequest,
        FUpdateGlobalTableSettingsResult &updateGlobalTableSettingsResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateGlobalTableSettingsRequest(updateGlobalTableSettingsRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateGlobalTableSettingsAsync(
            updateGlobalTableSettingsRequest.toAWS(),
            [&success, &updateGlobalTableSettingsResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateGlobalTableSettingsRequest &awsUpdateGlobalTableSettingsRequest,
                const Aws::DynamoDB::Model::UpdateGlobalTableSettingsOutcome &awsUpdateGlobalTableSettingsOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateGlobalTableSettingsOutcome.IsSuccess();
                if (success) {
                    updateGlobalTableSettingsResult.fromAWS(awsUpdateGlobalTableSettingsOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateGlobalTableSettingsOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateGlobalTableSettingsOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateGlobalTableSettings Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateGlobalTableSettings(
    UObject *WorldContextObject,
    bool &success,
    FUpdateGlobalTableSettingsRequest updateGlobalTableSettingsRequest,
    FUpdateGlobalTableSettingsResult &updateGlobalTableSettingsResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateGlobalTableSettingsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateGlobalTableSettingsAction(this->awsDynamoDBClient,
                success,
                updateGlobalTableSettingsRequest,
                updateGlobalTableSettingsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateItemAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateItemRequest updateItemRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateItemAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateItemRequest updateItemRequest,
        FUpdateItemResult &updateItemResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateItemRequest(updateItemRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateItemAsync(
            updateItemRequest.toAWS(),
            [&success, &updateItemResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateItemRequest &awsUpdateItemRequest,
                const Aws::DynamoDB::Model::UpdateItemOutcome &awsUpdateItemOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateItemOutcome.IsSuccess();
                if (success) {
                    updateItemResult.fromAWS(awsUpdateItemOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateItemOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateItemOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateItem Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateItem(
    UObject *WorldContextObject,
    bool &success,
    FUpdateItemRequest updateItemRequest,
    FUpdateItemResult &updateItemResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateItemAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateItemAction(this->awsDynamoDBClient,
                success,
                updateItemRequest,
                updateItemResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateTableAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateTableRequest updateTableRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateTableAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateTableRequest updateTableRequest,
        FUpdateTableResult &updateTableResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateTableRequest(updateTableRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateTableAsync(
            updateTableRequest.toAWS(),
            [&success, &updateTableResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateTableRequest &awsUpdateTableRequest,
                const Aws::DynamoDB::Model::UpdateTableOutcome &awsUpdateTableOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateTableOutcome.IsSuccess();
                if (success) {
                    updateTableResult.fromAWS(awsUpdateTableOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateTableOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateTableOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateTable Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateTable(
    UObject *WorldContextObject,
    bool &success,
    FUpdateTableRequest updateTableRequest,
    FUpdateTableResult &updateTableResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateTableAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateTableAction(this->awsDynamoDBClient,
                success,
                updateTableRequest,
                updateTableResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

class FUpdateTimeToLiveAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::DynamoDB::DynamoDBClient *DynamoDBClient;
    FUpdateTimeToLiveRequest updateTimeToLiveRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateTimeToLiveAction(
        Aws::DynamoDB::DynamoDBClient *DynamoDBClient,
        bool &success,
        FUpdateTimeToLiveRequest updateTimeToLiveRequest,
        FUpdateTimeToLiveResult &updateTimeToLiveResult,
        EDynamoDBError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : DynamoDBClient(DynamoDBClient), updateTimeToLiveRequest(updateTimeToLiveRequest),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        DynamoDBClient->UpdateTimeToLiveAsync(
            updateTimeToLiveRequest.toAWS(),
            [&success, &updateTimeToLiveResult, &errorType, &errorMessage, this](
                const Aws::DynamoDB::DynamoDBClient *awsDynamoDBClient,
                const Aws::DynamoDB::Model::UpdateTimeToLiveRequest &awsUpdateTimeToLiveRequest,
                const Aws::DynamoDB::Model::UpdateTimeToLiveOutcome &awsUpdateTimeToLiveOutcome,
                const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
            ) mutable -> void {
                success = awsUpdateTimeToLiveOutcome.IsSuccess();
                if (success) {
                    updateTimeToLiveResult.fromAWS(awsUpdateTimeToLiveOutcome.GetResult());
                }

                errorType = fromAWS(awsUpdateTimeToLiveOutcome.GetError().GetErrorType());
                errorMessage = awsUpdateTimeToLiveOutcome.GetError().GetMessage().c_str();
                completed = true;
            },
            std::make_shared<Aws::Client::AsyncCallerContext>(std::to_string(LatentInfo.UUID).c_str())
        );
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UpdateTimeToLive Request");
    }

#endif
};

#endif

void
UDynamoDBClientObject::UpdateTimeToLive(
    UObject *WorldContextObject,
    bool &success,
    FUpdateTimeToLiveRequest updateTimeToLiveRequest,
    FUpdateTimeToLiveResult &updateTimeToLiveResult,
    EDynamoDBError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateTimeToLiveAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUpdateTimeToLiveAction(this->awsDynamoDBClient,
                success,
                updateTimeToLiveRequest,
                updateTimeToLiveResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}