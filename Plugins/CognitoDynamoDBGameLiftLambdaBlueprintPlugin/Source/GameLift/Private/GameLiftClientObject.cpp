/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#include "GameLiftClientObject.h"
#include "GameLiftGlobals.h"
#include "GameLiftPrivatePCH.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "LatentActions.h"

#include "aws/core/utils/Outcome.h"
#include "aws/core/client/AWSError.h"

#endif

#if WITH_GAMELIFTCLIENTSDK

EGameLiftError fromAWS(Aws::GameLift::GameLiftErrors awsErrorType) {
    switch (awsErrorType) {
        case Aws::GameLift::GameLiftErrors::INCOMPLETE_SIGNATURE:
            return EGameLiftError::INCOMPLETE_SIGNATURE;
            break;
        case Aws::GameLift::GameLiftErrors::INTERNAL_FAILURE:
            return EGameLiftError::INTERNAL_FAILURE;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_ACTION:
            return EGameLiftError::INVALID_ACTION;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_CLIENT_TOKEN_ID:
            return EGameLiftError::INVALID_CLIENT_TOKEN_ID;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_PARAMETER_COMBINATION:
            return EGameLiftError::INVALID_PARAMETER_COMBINATION;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_QUERY_PARAMETER:
            return EGameLiftError::INVALID_QUERY_PARAMETER;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_PARAMETER_VALUE:
            return EGameLiftError::INVALID_PARAMETER_VALUE;
            break;
        case Aws::GameLift::GameLiftErrors::MISSING_ACTION:
            return EGameLiftError::MISSING_ACTION;
            break;
        case Aws::GameLift::GameLiftErrors::MISSING_AUTHENTICATION_TOKEN:
            return EGameLiftError::MISSING_AUTHENTICATION_TOKEN;
            break;
        case Aws::GameLift::GameLiftErrors::MISSING_PARAMETER:
            return EGameLiftError::MISSING_PARAMETER;
            break;
        case Aws::GameLift::GameLiftErrors::OPT_IN_REQUIRED:
            return EGameLiftError::OPT_IN_REQUIRED;
            break;
        case Aws::GameLift::GameLiftErrors::REQUEST_EXPIRED:
            return EGameLiftError::REQUEST_EXPIRED;
            break;
        case Aws::GameLift::GameLiftErrors::SERVICE_UNAVAILABLE:
            return EGameLiftError::SERVICE_UNAVAILABLE;
            break;
        case Aws::GameLift::GameLiftErrors::THROTTLING:
            return EGameLiftError::THROTTLING;
            break;
        case Aws::GameLift::GameLiftErrors::VALIDATION:
            return EGameLiftError::VALIDATION;
            break;
        case Aws::GameLift::GameLiftErrors::ACCESS_DENIED:
            return EGameLiftError::ACCESS_DENIED;
            break;
        case Aws::GameLift::GameLiftErrors::RESOURCE_NOT_FOUND:
            return EGameLiftError::RESOURCE_NOT_FOUND;
            break;
        case Aws::GameLift::GameLiftErrors::UNRECOGNIZED_CLIENT:
            return EGameLiftError::UNRECOGNIZED_CLIENT;
            break;
        case Aws::GameLift::GameLiftErrors::MALFORMED_QUERY_STRING:
            return EGameLiftError::MALFORMED_QUERY_STRING;
            break;
        case Aws::GameLift::GameLiftErrors::SLOW_DOWN:
            return EGameLiftError::SLOW_DOWN;
            break;
        case Aws::GameLift::GameLiftErrors::REQUEST_TIME_TOO_SKEWED:
            return EGameLiftError::REQUEST_TIME_TOO_SKEWED;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_SIGNATURE:
            return EGameLiftError::INVALID_SIGNATURE;
            break;
        case Aws::GameLift::GameLiftErrors::SIGNATURE_DOES_NOT_MATCH:
            return EGameLiftError::SIGNATURE_DOES_NOT_MATCH;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_ACCESS_KEY_ID:
            return EGameLiftError::INVALID_ACCESS_KEY_ID;
            break;
        case Aws::GameLift::GameLiftErrors::REQUEST_TIMEOUT:
            return EGameLiftError::REQUEST_TIMEOUT;
            break;
        case Aws::GameLift::GameLiftErrors::NETWORK_CONNECTION:
            return EGameLiftError::NETWORK_CONNECTION;
            break;
        case Aws::GameLift::GameLiftErrors::UNKNOWN:
            return EGameLiftError::UNKNOWN;
            break;
        case Aws::GameLift::GameLiftErrors::CONFLICT:
            return EGameLiftError::CONFLICT;
            break;
        case Aws::GameLift::GameLiftErrors::FLEET_CAPACITY_EXCEEDED:
            return EGameLiftError::FLEET_CAPACITY_EXCEEDED;
            break;
        case Aws::GameLift::GameLiftErrors::GAME_SESSION_FULL:
            return EGameLiftError::GAME_SESSION_FULL;
            break;
        case Aws::GameLift::GameLiftErrors::IDEMPOTENT_PARAMETER_MISMATCH:
            return EGameLiftError::IDEMPOTENT_PARAMETER_MISMATCH;
            break;
        case Aws::GameLift::GameLiftErrors::INTERNAL_SERVICE:
            return EGameLiftError::INTERNAL_SERVICE;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_FLEET_STATUS:
            return EGameLiftError::INVALID_FLEET_STATUS;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_GAME_SESSION_STATUS:
            return EGameLiftError::INVALID_GAME_SESSION_STATUS;
            break;
        case Aws::GameLift::GameLiftErrors::INVALID_REQUEST:
            return EGameLiftError::INVALID_REQUEST;
            break;
        case Aws::GameLift::GameLiftErrors::LIMIT_EXCEEDED:
            return EGameLiftError::LIMIT_EXCEEDED;
            break;
        case Aws::GameLift::GameLiftErrors::NOT_FOUND:
            return EGameLiftError::NOT_FOUND;
            break;
        case Aws::GameLift::GameLiftErrors::TERMINAL_ROUTING_STRATEGY:
            return EGameLiftError::TERMINAL_ROUTING_STRATEGY;
            break;
        case Aws::GameLift::GameLiftErrors::UNAUTHORIZED:
            return EGameLiftError::UNAUTHORIZED;
            break;
        case Aws::GameLift::GameLiftErrors::UNSUPPORTED_REGION:
            return EGameLiftError::UNSUPPORTED_REGION;
            break;
        default:
            return EGameLiftError::UNKNOWN;
            break;
    }
}

#endif

UGameLiftClientObject *UGameLiftClientObject::CreateGameLiftObject(
        const FAWSCredentials &credentials,
        const FAWSClientConfiguration &clientConfiguration
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    UGameLiftClientObject *GameLiftClient = NewObject<UGameLiftClientObject>();
    GameLiftClient->awsGameLiftClient = new Aws::GameLift::GameLiftClient(credentials.toAWS(),
                                                                          clientConfiguration.toAWS());
    return GameLiftClient;
#endif
    return nullptr;
}

FString UGameLiftClientObject::GetServiceClientName() const {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    return this->awsGameLiftClient->GetServiceClientName();
#endif
    return FString();
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FAcceptMatchAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FAcceptMatchRequest acceptMatchRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FAcceptMatchAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FAcceptMatchRequest acceptMatchRequest,
            FAcceptMatchResult &acceptMatchResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), acceptMatchRequest(acceptMatchRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->AcceptMatchAsync(
                acceptMatchRequest.toAWS(),
                [&success, &acceptMatchResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::AcceptMatchRequest &awsAcceptMatchRequest,
                        const Aws::GameLift::Model::AcceptMatchOutcome &awsAcceptMatchOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsAcceptMatchOutcome.IsSuccess();
                    if (success) {
                        acceptMatchResult.fromAWS(awsAcceptMatchOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsAcceptMatchOutcome.GetError().GetErrorType());
                    errorMessage = awsAcceptMatchOutcome.GetError().GetMessage().c_str();
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
        return FString("AcceptMatch Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::AcceptMatch(
        UObject *WorldContextObject,
        bool &success,
        FAcceptMatchRequest acceptMatchRequest,
        FAcceptMatchResult &acceptMatchResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FAcceptMatchAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FAcceptMatchAction(this->awsGameLiftClient,
                                                                    success,
                                                                    acceptMatchRequest,
                                                                    acceptMatchResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateAliasAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGameLiftCreateAliasRequest createAliasRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateAliasAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGameLiftCreateAliasRequest createAliasRequest,
            FGameLiftCreateAliasResult &createAliasResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createAliasRequest(createAliasRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateAliasAsync(
                createAliasRequest.toAWS(),
                [&success, &createAliasResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateAliasRequest &awsCreateAliasRequest,
                        const Aws::GameLift::Model::CreateAliasOutcome &awsCreateAliasOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateAliasOutcome.IsSuccess();
                    if (success) {
                        createAliasResult.fromAWS(awsCreateAliasOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateAliasOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateAliasOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateAlias Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateAlias(
        UObject *WorldContextObject,
        bool &success,
        FGameLiftCreateAliasRequest createAliasRequest,
        FGameLiftCreateAliasResult &createAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateAliasAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateAliasAction(this->awsGameLiftClient,
                                                                    success,
                                                                    createAliasRequest,
                                                                    createAliasResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateBuildAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateBuildRequest createBuildRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateBuildAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateBuildRequest createBuildRequest,
            FCreateBuildResult &createBuildResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createBuildRequest(createBuildRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateBuildAsync(
                createBuildRequest.toAWS(),
                [&success, &createBuildResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateBuildRequest &awsCreateBuildRequest,
                        const Aws::GameLift::Model::CreateBuildOutcome &awsCreateBuildOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateBuildOutcome.IsSuccess();
                    if (success) {
                        createBuildResult.fromAWS(awsCreateBuildOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateBuildOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateBuildOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateBuild Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateBuild(
        UObject *WorldContextObject,
        bool &success,
        FCreateBuildRequest createBuildRequest,
        FCreateBuildResult &createBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateBuildAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateBuildAction(this->awsGameLiftClient,
                                                                    success,
                                                                    createBuildRequest,
                                                                    createBuildResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateFleetAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateFleetRequest createFleetRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateFleetAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateFleetRequest createFleetRequest,
            FCreateFleetResult &createFleetResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createFleetRequest(createFleetRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateFleetAsync(
                createFleetRequest.toAWS(),
                [&success, &createFleetResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateFleetRequest &awsCreateFleetRequest,
                        const Aws::GameLift::Model::CreateFleetOutcome &awsCreateFleetOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateFleetOutcome.IsSuccess();
                    if (success) {
                        createFleetResult.fromAWS(awsCreateFleetOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateFleetOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateFleetOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateFleet Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateFleet(
        UObject *WorldContextObject,
        bool &success,
        FCreateFleetRequest createFleetRequest,
        FCreateFleetResult &createFleetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateFleetAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateFleetAction(this->awsGameLiftClient,
                                                                    success,
                                                                    createFleetRequest,
                                                                    createFleetResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateGameSessionAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateGameSessionRequest createGameSessionRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateGameSessionAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateGameSessionRequest createGameSessionRequest,
            FCreateGameSessionResult &createGameSessionResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createGameSessionRequest(createGameSessionRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateGameSessionAsync(
                createGameSessionRequest.toAWS(),
                [&success, &createGameSessionResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateGameSessionRequest &awsCreateGameSessionRequest,
                        const Aws::GameLift::Model::CreateGameSessionOutcome &awsCreateGameSessionOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateGameSessionOutcome.IsSuccess();
                    if (success) {
                        createGameSessionResult.fromAWS(awsCreateGameSessionOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateGameSessionOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateGameSessionOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateGameSession Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateGameSession(
        UObject *WorldContextObject,
        bool &success,
        FCreateGameSessionRequest createGameSessionRequest,
        FCreateGameSessionResult &createGameSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateGameSessionAction>(LatentInfo.CallbackTarget,
                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateGameSessionAction(this->awsGameLiftClient,
                                                                          success,
                                                                          createGameSessionRequest,
                                                                          createGameSessionResult,
                                                                          errorType,
                                                                          errorMessage,
                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateGameSessionQueueAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateGameSessionQueueRequest createGameSessionQueueRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateGameSessionQueueAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateGameSessionQueueRequest createGameSessionQueueRequest,
            FCreateGameSessionQueueResult &createGameSessionQueueResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createGameSessionQueueRequest(createGameSessionQueueRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateGameSessionQueueAsync(
                createGameSessionQueueRequest.toAWS(),
                [&success, &createGameSessionQueueResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateGameSessionQueueRequest &awsCreateGameSessionQueueRequest,
                        const Aws::GameLift::Model::CreateGameSessionQueueOutcome &awsCreateGameSessionQueueOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateGameSessionQueueOutcome.IsSuccess();
                    if (success) {
                        createGameSessionQueueResult.fromAWS(awsCreateGameSessionQueueOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateGameSessionQueueOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateGameSessionQueueOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateGameSessionQueue Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateGameSessionQueue(
        UObject *WorldContextObject,
        bool &success,
        FCreateGameSessionQueueRequest createGameSessionQueueRequest,
        FCreateGameSessionQueueResult &createGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateGameSessionQueueAction>(LatentInfo.CallbackTarget,
                                                                                  LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateGameSessionQueueAction(this->awsGameLiftClient,
                                                                               success,
                                                                               createGameSessionQueueRequest,
                                                                               createGameSessionQueueResult,
                                                                               errorType,
                                                                               errorMessage,
                                                                               LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateMatchmakingConfigurationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateMatchmakingConfigurationRequest createMatchmakingConfigurationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateMatchmakingConfigurationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateMatchmakingConfigurationRequest createMatchmakingConfigurationRequest,
            FCreateMatchmakingConfigurationResult &createMatchmakingConfigurationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              createMatchmakingConfigurationRequest(createMatchmakingConfigurationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateMatchmakingConfigurationAsync(
                createMatchmakingConfigurationRequest.toAWS(),
                [&success, &createMatchmakingConfigurationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateMatchmakingConfigurationRequest &awsCreateMatchmakingConfigurationRequest,
                        const Aws::GameLift::Model::CreateMatchmakingConfigurationOutcome &awsCreateMatchmakingConfigurationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateMatchmakingConfigurationOutcome.IsSuccess();
                    if (success) {
                        createMatchmakingConfigurationResult.fromAWS(awsCreateMatchmakingConfigurationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateMatchmakingConfigurationOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateMatchmakingConfigurationOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateMatchmakingConfiguration Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateMatchmakingConfiguration(
        UObject *WorldContextObject,
        bool &success,
        FCreateMatchmakingConfigurationRequest createMatchmakingConfigurationRequest,
        FCreateMatchmakingConfigurationResult &createMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateMatchmakingConfigurationAction>(LatentInfo.CallbackTarget,
                                                                                          LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateMatchmakingConfigurationAction(this->awsGameLiftClient,
                                                                                       success,
                                                                                       createMatchmakingConfigurationRequest,
                                                                                       createMatchmakingConfigurationResult,
                                                                                       errorType,
                                                                                       errorMessage,
                                                                                       LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateMatchmakingRuleSetAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateMatchmakingRuleSetRequest createMatchmakingRuleSetRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateMatchmakingRuleSetAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateMatchmakingRuleSetRequest createMatchmakingRuleSetRequest,
            FCreateMatchmakingRuleSetResult &createMatchmakingRuleSetResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createMatchmakingRuleSetRequest(createMatchmakingRuleSetRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateMatchmakingRuleSetAsync(
                createMatchmakingRuleSetRequest.toAWS(),
                [&success, &createMatchmakingRuleSetResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateMatchmakingRuleSetRequest &awsCreateMatchmakingRuleSetRequest,
                        const Aws::GameLift::Model::CreateMatchmakingRuleSetOutcome &awsCreateMatchmakingRuleSetOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateMatchmakingRuleSetOutcome.IsSuccess();
                    if (success) {
                        createMatchmakingRuleSetResult.fromAWS(awsCreateMatchmakingRuleSetOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateMatchmakingRuleSetOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateMatchmakingRuleSetOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateMatchmakingRuleSet Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateMatchmakingRuleSet(
        UObject *WorldContextObject,
        bool &success,
        FCreateMatchmakingRuleSetRequest createMatchmakingRuleSetRequest,
        FCreateMatchmakingRuleSetResult &createMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateMatchmakingRuleSetAction>(LatentInfo.CallbackTarget,
                                                                                    LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateMatchmakingRuleSetAction(this->awsGameLiftClient,
                                                                                 success,
                                                                                 createMatchmakingRuleSetRequest,
                                                                                 createMatchmakingRuleSetResult,
                                                                                 errorType,
                                                                                 errorMessage,
                                                                                 LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreatePlayerSessionAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreatePlayerSessionRequest createPlayerSessionRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreatePlayerSessionAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreatePlayerSessionRequest createPlayerSessionRequest,
            FCreatePlayerSessionResult &createPlayerSessionResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createPlayerSessionRequest(createPlayerSessionRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreatePlayerSessionAsync(
                createPlayerSessionRequest.toAWS(),
                [&success, &createPlayerSessionResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreatePlayerSessionRequest &awsCreatePlayerSessionRequest,
                        const Aws::GameLift::Model::CreatePlayerSessionOutcome &awsCreatePlayerSessionOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreatePlayerSessionOutcome.IsSuccess();
                    if (success) {
                        createPlayerSessionResult.fromAWS(awsCreatePlayerSessionOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreatePlayerSessionOutcome.GetError().GetErrorType());
                    errorMessage = awsCreatePlayerSessionOutcome.GetError().GetMessage().c_str();
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
        return FString("CreatePlayerSession Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreatePlayerSession(
        UObject *WorldContextObject,
        bool &success,
        FCreatePlayerSessionRequest createPlayerSessionRequest,
        FCreatePlayerSessionResult &createPlayerSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreatePlayerSessionAction>(LatentInfo.CallbackTarget,
                                                                               LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreatePlayerSessionAction(this->awsGameLiftClient,
                                                                            success,
                                                                            createPlayerSessionRequest,
                                                                            createPlayerSessionResult,
                                                                            errorType,
                                                                            errorMessage,
                                                                            LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreatePlayerSessionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreatePlayerSessionsRequest createPlayerSessionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreatePlayerSessionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreatePlayerSessionsRequest createPlayerSessionsRequest,
            FCreatePlayerSessionsResult &createPlayerSessionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createPlayerSessionsRequest(createPlayerSessionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreatePlayerSessionsAsync(
                createPlayerSessionsRequest.toAWS(),
                [&success, &createPlayerSessionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreatePlayerSessionsRequest &awsCreatePlayerSessionsRequest,
                        const Aws::GameLift::Model::CreatePlayerSessionsOutcome &awsCreatePlayerSessionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreatePlayerSessionsOutcome.IsSuccess();
                    if (success) {
                        createPlayerSessionsResult.fromAWS(awsCreatePlayerSessionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreatePlayerSessionsOutcome.GetError().GetErrorType());
                    errorMessage = awsCreatePlayerSessionsOutcome.GetError().GetMessage().c_str();
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
        return FString("CreatePlayerSessions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreatePlayerSessions(
        UObject *WorldContextObject,
        bool &success,
        FCreatePlayerSessionsRequest createPlayerSessionsRequest,
        FCreatePlayerSessionsResult &createPlayerSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreatePlayerSessionsAction>(LatentInfo.CallbackTarget,
                                                                                LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreatePlayerSessionsAction(this->awsGameLiftClient,
                                                                             success,
                                                                             createPlayerSessionsRequest,
                                                                             createPlayerSessionsResult,
                                                                             errorType,
                                                                             errorMessage,
                                                                             LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateScriptAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateScriptRequest createScriptRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateScriptAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateScriptRequest createScriptRequest,
            FCreateScriptResult &createScriptResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createScriptRequest(createScriptRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateScriptAsync(
                createScriptRequest.toAWS(),
                [&success, &createScriptResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateScriptRequest &awsCreateScriptRequest,
                        const Aws::GameLift::Model::CreateScriptOutcome &awsCreateScriptOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateScriptOutcome.IsSuccess();
                    if (success) {
                        createScriptResult.fromAWS(awsCreateScriptOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateScriptOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateScriptOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateScript Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateScript(
        UObject *WorldContextObject,
        bool &success,
        FCreateScriptRequest createScriptRequest,
        FCreateScriptResult &createScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateScriptAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateScriptAction(this->awsGameLiftClient,
                                                                     success,
                                                                     createScriptRequest,
                                                                     createScriptResult,
                                                                     errorType,
                                                                     errorMessage,
                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateVpcPeeringAuthorizationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateVpcPeeringAuthorizationRequest createVpcPeeringAuthorizationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateVpcPeeringAuthorizationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateVpcPeeringAuthorizationRequest createVpcPeeringAuthorizationRequest,
            FCreateVpcPeeringAuthorizationResult &createVpcPeeringAuthorizationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              createVpcPeeringAuthorizationRequest(createVpcPeeringAuthorizationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateVpcPeeringAuthorizationAsync(
                createVpcPeeringAuthorizationRequest.toAWS(),
                [&success, &createVpcPeeringAuthorizationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateVpcPeeringAuthorizationRequest &awsCreateVpcPeeringAuthorizationRequest,
                        const Aws::GameLift::Model::CreateVpcPeeringAuthorizationOutcome &awsCreateVpcPeeringAuthorizationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateVpcPeeringAuthorizationOutcome.IsSuccess();
                    if (success) {
                        createVpcPeeringAuthorizationResult.fromAWS(awsCreateVpcPeeringAuthorizationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateVpcPeeringAuthorizationOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateVpcPeeringAuthorizationOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateVpcPeeringAuthorization Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateVpcPeeringAuthorization(
        UObject *WorldContextObject,
        bool &success,
        FCreateVpcPeeringAuthorizationRequest createVpcPeeringAuthorizationRequest,
        FCreateVpcPeeringAuthorizationResult &createVpcPeeringAuthorizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateVpcPeeringAuthorizationAction>(LatentInfo.CallbackTarget,
                                                                                         LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateVpcPeeringAuthorizationAction(this->awsGameLiftClient,
                                                                                      success,
                                                                                      createVpcPeeringAuthorizationRequest,
                                                                                      createVpcPeeringAuthorizationResult,
                                                                                      errorType,
                                                                                      errorMessage,
                                                                                      LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FCreateVpcPeeringConnectionAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FCreateVpcPeeringConnectionRequest createVpcPeeringConnectionRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FCreateVpcPeeringConnectionAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FCreateVpcPeeringConnectionRequest createVpcPeeringConnectionRequest,
            FCreateVpcPeeringConnectionResult &createVpcPeeringConnectionResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), createVpcPeeringConnectionRequest(createVpcPeeringConnectionRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->CreateVpcPeeringConnectionAsync(
                createVpcPeeringConnectionRequest.toAWS(),
                [&success, &createVpcPeeringConnectionResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::CreateVpcPeeringConnectionRequest &awsCreateVpcPeeringConnectionRequest,
                        const Aws::GameLift::Model::CreateVpcPeeringConnectionOutcome &awsCreateVpcPeeringConnectionOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsCreateVpcPeeringConnectionOutcome.IsSuccess();
                    if (success) {
                        createVpcPeeringConnectionResult.fromAWS(awsCreateVpcPeeringConnectionOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsCreateVpcPeeringConnectionOutcome.GetError().GetErrorType());
                    errorMessage = awsCreateVpcPeeringConnectionOutcome.GetError().GetMessage().c_str();
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
        return FString("CreateVpcPeeringConnection Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::CreateVpcPeeringConnection(
        UObject *WorldContextObject,
        bool &success,
        FCreateVpcPeeringConnectionRequest createVpcPeeringConnectionRequest,
        FCreateVpcPeeringConnectionResult &createVpcPeeringConnectionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateVpcPeeringConnectionAction>(LatentInfo.CallbackTarget,
                                                                                      LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FCreateVpcPeeringConnectionAction(this->awsGameLiftClient,
                                                                                   success,
                                                                                   createVpcPeeringConnectionRequest,
                                                                                   createVpcPeeringConnectionResult,
                                                                                   errorType,
                                                                                   errorMessage,
                                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteAliasAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGameLiftDeleteAliasRequest deleteAliasRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteAliasAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGameLiftDeleteAliasRequest deleteAliasRequest,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteAliasRequest(deleteAliasRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteAliasAsync(
                deleteAliasRequest.toAWS(),
                [&success, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteAliasRequest &awsDeleteAliasRequest,
                        const Aws::GameLift::Model::DeleteAliasOutcome &awsDeleteAliasOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteAliasOutcome.IsSuccess();
                   
                    errorType = fromAWS(awsDeleteAliasOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteAliasOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteAlias Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteAlias(
        UObject *WorldContextObject,
        bool &success,
        FGameLiftDeleteAliasRequest deleteAliasRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteAliasAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteAliasAction(this->awsGameLiftClient,
                                                                    success,
                                                                    deleteAliasRequest,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteBuildAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteBuildRequest deleteBuildRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteBuildAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteBuildRequest deleteBuildRequest,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteBuildRequest(deleteBuildRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteBuildAsync(
                deleteBuildRequest.toAWS(),
                [&success, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteBuildRequest &awsDeleteBuildRequest,
                        const Aws::GameLift::Model::DeleteBuildOutcome &awsDeleteBuildOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteBuildOutcome.IsSuccess();
                   
                    errorType = fromAWS(awsDeleteBuildOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteBuildOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteBuild Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteBuild(
        UObject *WorldContextObject,
        bool &success,
        FDeleteBuildRequest deleteBuildRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteBuildAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteBuildAction(this->awsGameLiftClient,
                                                                    success,
                                                                    deleteBuildRequest,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteFleetAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteFleetRequest deleteFleetRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteFleetAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteFleetRequest deleteFleetRequest,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteFleetRequest(deleteFleetRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteFleetAsync(
                deleteFleetRequest.toAWS(),
                [&success, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteFleetRequest &awsDeleteFleetRequest,
                        const Aws::GameLift::Model::DeleteFleetOutcome &awsDeleteFleetOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteFleetOutcome.IsSuccess();
                   
                    errorType = fromAWS(awsDeleteFleetOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteFleetOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteFleet Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteFleet(
        UObject *WorldContextObject,
        bool &success,
        FDeleteFleetRequest deleteFleetRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteFleetAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteFleetAction(this->awsGameLiftClient,
                                                                    success,
                                                                    deleteFleetRequest,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteGameSessionQueueAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteGameSessionQueueRequest deleteGameSessionQueueRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteGameSessionQueueAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteGameSessionQueueRequest deleteGameSessionQueueRequest,
            FDeleteGameSessionQueueResult &deleteGameSessionQueueResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteGameSessionQueueRequest(deleteGameSessionQueueRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteGameSessionQueueAsync(
                deleteGameSessionQueueRequest.toAWS(),
                [&success, &deleteGameSessionQueueResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteGameSessionQueueRequest &awsDeleteGameSessionQueueRequest,
                        const Aws::GameLift::Model::DeleteGameSessionQueueOutcome &awsDeleteGameSessionQueueOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteGameSessionQueueOutcome.IsSuccess();
                    if (success) {
                        deleteGameSessionQueueResult.fromAWS(awsDeleteGameSessionQueueOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDeleteGameSessionQueueOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteGameSessionQueueOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteGameSessionQueue Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteGameSessionQueue(
        UObject *WorldContextObject,
        bool &success,
        FDeleteGameSessionQueueRequest deleteGameSessionQueueRequest,
        FDeleteGameSessionQueueResult &deleteGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteGameSessionQueueAction>(LatentInfo.CallbackTarget,
                                                                                  LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteGameSessionQueueAction(this->awsGameLiftClient,
                                                                               success,
                                                                               deleteGameSessionQueueRequest,
                                                                               deleteGameSessionQueueResult,
                                                                               errorType,
                                                                               errorMessage,
                                                                               LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteMatchmakingConfigurationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteMatchmakingConfigurationRequest deleteMatchmakingConfigurationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteMatchmakingConfigurationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteMatchmakingConfigurationRequest deleteMatchmakingConfigurationRequest,
            FDeleteMatchmakingConfigurationResult &deleteMatchmakingConfigurationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              deleteMatchmakingConfigurationRequest(deleteMatchmakingConfigurationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteMatchmakingConfigurationAsync(
                deleteMatchmakingConfigurationRequest.toAWS(),
                [&success, &deleteMatchmakingConfigurationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteMatchmakingConfigurationRequest &awsDeleteMatchmakingConfigurationRequest,
                        const Aws::GameLift::Model::DeleteMatchmakingConfigurationOutcome &awsDeleteMatchmakingConfigurationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteMatchmakingConfigurationOutcome.IsSuccess();
                    if (success) {
                        deleteMatchmakingConfigurationResult.fromAWS(awsDeleteMatchmakingConfigurationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDeleteMatchmakingConfigurationOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteMatchmakingConfigurationOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteMatchmakingConfiguration Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteMatchmakingConfiguration(
        UObject *WorldContextObject,
        bool &success,
        FDeleteMatchmakingConfigurationRequest deleteMatchmakingConfigurationRequest,
        FDeleteMatchmakingConfigurationResult &deleteMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteMatchmakingConfigurationAction>(LatentInfo.CallbackTarget,
                                                                                          LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteMatchmakingConfigurationAction(this->awsGameLiftClient,
                                                                                       success,
                                                                                       deleteMatchmakingConfigurationRequest,
                                                                                       deleteMatchmakingConfigurationResult,
                                                                                       errorType,
                                                                                       errorMessage,
                                                                                       LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteMatchmakingRuleSetAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteMatchmakingRuleSetRequest deleteMatchmakingRuleSetRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteMatchmakingRuleSetAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteMatchmakingRuleSetRequest deleteMatchmakingRuleSetRequest,
            FDeleteMatchmakingRuleSetResult &deleteMatchmakingRuleSetResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteMatchmakingRuleSetRequest(deleteMatchmakingRuleSetRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteMatchmakingRuleSetAsync(
                deleteMatchmakingRuleSetRequest.toAWS(),
                [&success, &deleteMatchmakingRuleSetResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteMatchmakingRuleSetRequest &awsDeleteMatchmakingRuleSetRequest,
                        const Aws::GameLift::Model::DeleteMatchmakingRuleSetOutcome &awsDeleteMatchmakingRuleSetOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteMatchmakingRuleSetOutcome.IsSuccess();
                    if (success) {
                        deleteMatchmakingRuleSetResult.fromAWS(awsDeleteMatchmakingRuleSetOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDeleteMatchmakingRuleSetOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteMatchmakingRuleSetOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteMatchmakingRuleSet Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteMatchmakingRuleSet(
        UObject *WorldContextObject,
        bool &success,
        FDeleteMatchmakingRuleSetRequest deleteMatchmakingRuleSetRequest,
        FDeleteMatchmakingRuleSetResult &deleteMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteMatchmakingRuleSetAction>(LatentInfo.CallbackTarget,
                                                                                    LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteMatchmakingRuleSetAction(this->awsGameLiftClient,
                                                                                 success,
                                                                                 deleteMatchmakingRuleSetRequest,
                                                                                 deleteMatchmakingRuleSetResult,
                                                                                 errorType,
                                                                                 errorMessage,
                                                                                 LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteScalingPolicyAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteScalingPolicyRequest deleteScalingPolicyRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteScalingPolicyAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteScalingPolicyRequest deleteScalingPolicyRequest,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteScalingPolicyRequest(deleteScalingPolicyRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteScalingPolicyAsync(
                deleteScalingPolicyRequest.toAWS(),
                [&success, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteScalingPolicyRequest &awsDeleteScalingPolicyRequest,
                        const Aws::GameLift::Model::DeleteScalingPolicyOutcome &awsDeleteScalingPolicyOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteScalingPolicyOutcome.IsSuccess();
                   
                    errorType = fromAWS(awsDeleteScalingPolicyOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteScalingPolicyOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteScalingPolicy Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteScalingPolicy(
        UObject *WorldContextObject,
        bool &success,
        FDeleteScalingPolicyRequest deleteScalingPolicyRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteScalingPolicyAction>(LatentInfo.CallbackTarget,
                                                                               LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteScalingPolicyAction(this->awsGameLiftClient,
                                                                            success,
                                                                            deleteScalingPolicyRequest,
                                                                            errorType,
                                                                            errorMessage,
                                                                            LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteScriptAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteScriptRequest deleteScriptRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteScriptAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteScriptRequest deleteScriptRequest,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteScriptRequest(deleteScriptRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteScriptAsync(
                deleteScriptRequest.toAWS(),
                [&success, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteScriptRequest &awsDeleteScriptRequest,
                        const Aws::GameLift::Model::DeleteScriptOutcome &awsDeleteScriptOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteScriptOutcome.IsSuccess();
                   
                    errorType = fromAWS(awsDeleteScriptOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteScriptOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteScript Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteScript(
        UObject *WorldContextObject,
        bool &success,
        FDeleteScriptRequest deleteScriptRequest,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteScriptAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteScriptAction(this->awsGameLiftClient,
                                                                     success,
                                                                     deleteScriptRequest,
                                                                     errorType,
                                                                     errorMessage,
                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteVpcPeeringAuthorizationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteVpcPeeringAuthorizationRequest deleteVpcPeeringAuthorizationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteVpcPeeringAuthorizationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteVpcPeeringAuthorizationRequest deleteVpcPeeringAuthorizationRequest,
            FDeleteVpcPeeringAuthorizationResult &deleteVpcPeeringAuthorizationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              deleteVpcPeeringAuthorizationRequest(deleteVpcPeeringAuthorizationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteVpcPeeringAuthorizationAsync(
                deleteVpcPeeringAuthorizationRequest.toAWS(),
                [&success, &deleteVpcPeeringAuthorizationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteVpcPeeringAuthorizationRequest &awsDeleteVpcPeeringAuthorizationRequest,
                        const Aws::GameLift::Model::DeleteVpcPeeringAuthorizationOutcome &awsDeleteVpcPeeringAuthorizationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteVpcPeeringAuthorizationOutcome.IsSuccess();
                    if (success) {
                        deleteVpcPeeringAuthorizationResult.fromAWS(awsDeleteVpcPeeringAuthorizationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDeleteVpcPeeringAuthorizationOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteVpcPeeringAuthorizationOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteVpcPeeringAuthorization Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteVpcPeeringAuthorization(
        UObject *WorldContextObject,
        bool &success,
        FDeleteVpcPeeringAuthorizationRequest deleteVpcPeeringAuthorizationRequest,
        FDeleteVpcPeeringAuthorizationResult &deleteVpcPeeringAuthorizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteVpcPeeringAuthorizationAction>(LatentInfo.CallbackTarget,
                                                                                         LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteVpcPeeringAuthorizationAction(this->awsGameLiftClient,
                                                                                      success,
                                                                                      deleteVpcPeeringAuthorizationRequest,
                                                                                      deleteVpcPeeringAuthorizationResult,
                                                                                      errorType,
                                                                                      errorMessage,
                                                                                      LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDeleteVpcPeeringConnectionAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDeleteVpcPeeringConnectionRequest deleteVpcPeeringConnectionRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDeleteVpcPeeringConnectionAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDeleteVpcPeeringConnectionRequest deleteVpcPeeringConnectionRequest,
            FDeleteVpcPeeringConnectionResult &deleteVpcPeeringConnectionResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), deleteVpcPeeringConnectionRequest(deleteVpcPeeringConnectionRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DeleteVpcPeeringConnectionAsync(
                deleteVpcPeeringConnectionRequest.toAWS(),
                [&success, &deleteVpcPeeringConnectionResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DeleteVpcPeeringConnectionRequest &awsDeleteVpcPeeringConnectionRequest,
                        const Aws::GameLift::Model::DeleteVpcPeeringConnectionOutcome &awsDeleteVpcPeeringConnectionOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDeleteVpcPeeringConnectionOutcome.IsSuccess();
                    if (success) {
                        deleteVpcPeeringConnectionResult.fromAWS(awsDeleteVpcPeeringConnectionOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDeleteVpcPeeringConnectionOutcome.GetError().GetErrorType());
                    errorMessage = awsDeleteVpcPeeringConnectionOutcome.GetError().GetMessage().c_str();
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
        return FString("DeleteVpcPeeringConnection Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DeleteVpcPeeringConnection(
        UObject *WorldContextObject,
        bool &success,
        FDeleteVpcPeeringConnectionRequest deleteVpcPeeringConnectionRequest,
        FDeleteVpcPeeringConnectionResult &deleteVpcPeeringConnectionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteVpcPeeringConnectionAction>(LatentInfo.CallbackTarget,
                                                                                      LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDeleteVpcPeeringConnectionAction(this->awsGameLiftClient,
                                                                                   success,
                                                                                   deleteVpcPeeringConnectionRequest,
                                                                                   deleteVpcPeeringConnectionResult,
                                                                                   errorType,
                                                                                   errorMessage,
                                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeAliasAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeAliasRequest describeAliasRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeAliasAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeAliasRequest describeAliasRequest,
            FDescribeAliasResult &describeAliasResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeAliasRequest(describeAliasRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeAliasAsync(
                describeAliasRequest.toAWS(),
                [&success, &describeAliasResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeAliasRequest &awsDescribeAliasRequest,
                        const Aws::GameLift::Model::DescribeAliasOutcome &awsDescribeAliasOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeAliasOutcome.IsSuccess();
                    if (success) {
                        describeAliasResult.fromAWS(awsDescribeAliasOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeAliasOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeAliasOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeAlias Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeAlias(
        UObject *WorldContextObject,
        bool &success,
        FDescribeAliasRequest describeAliasRequest,
        FDescribeAliasResult &describeAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeAliasAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeAliasAction(this->awsGameLiftClient,
                                                                      success,
                                                                      describeAliasRequest,
                                                                      describeAliasResult,
                                                                      errorType,
                                                                      errorMessage,
                                                                      LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeBuildAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeBuildRequest describeBuildRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeBuildAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeBuildRequest describeBuildRequest,
            FDescribeBuildResult &describeBuildResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeBuildRequest(describeBuildRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeBuildAsync(
                describeBuildRequest.toAWS(),
                [&success, &describeBuildResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeBuildRequest &awsDescribeBuildRequest,
                        const Aws::GameLift::Model::DescribeBuildOutcome &awsDescribeBuildOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeBuildOutcome.IsSuccess();
                    if (success) {
                        describeBuildResult.fromAWS(awsDescribeBuildOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeBuildOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeBuildOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeBuild Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeBuild(
        UObject *WorldContextObject,
        bool &success,
        FDescribeBuildRequest describeBuildRequest,
        FDescribeBuildResult &describeBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeBuildAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeBuildAction(this->awsGameLiftClient,
                                                                      success,
                                                                      describeBuildRequest,
                                                                      describeBuildResult,
                                                                      errorType,
                                                                      errorMessage,
                                                                      LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeEC2InstanceLimitsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeEC2InstanceLimitsRequest describeEC2InstanceLimitsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeEC2InstanceLimitsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeEC2InstanceLimitsRequest describeEC2InstanceLimitsRequest,
            FDescribeEC2InstanceLimitsResult &describeEC2InstanceLimitsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeEC2InstanceLimitsRequest(describeEC2InstanceLimitsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeEC2InstanceLimitsAsync(
                describeEC2InstanceLimitsRequest.toAWS(),
                [&success, &describeEC2InstanceLimitsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeEC2InstanceLimitsRequest &awsDescribeEC2InstanceLimitsRequest,
                        const Aws::GameLift::Model::DescribeEC2InstanceLimitsOutcome &awsDescribeEC2InstanceLimitsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeEC2InstanceLimitsOutcome.IsSuccess();
                    if (success) {
                        describeEC2InstanceLimitsResult.fromAWS(awsDescribeEC2InstanceLimitsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeEC2InstanceLimitsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeEC2InstanceLimitsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeEC2InstanceLimits Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeEC2InstanceLimits(
        UObject *WorldContextObject,
        bool &success,
        FDescribeEC2InstanceLimitsRequest describeEC2InstanceLimitsRequest,
        FDescribeEC2InstanceLimitsResult &describeEC2InstanceLimitsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeEC2InstanceLimitsAction>(LatentInfo.CallbackTarget,
                                                                                     LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeEC2InstanceLimitsAction(this->awsGameLiftClient,
                                                                                  success,
                                                                                  describeEC2InstanceLimitsRequest,
                                                                                  describeEC2InstanceLimitsResult,
                                                                                  errorType,
                                                                                  errorMessage,
                                                                                  LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeFleetAttributesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeFleetAttributesRequest describeFleetAttributesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeFleetAttributesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeFleetAttributesRequest describeFleetAttributesRequest,
            FDescribeFleetAttributesResult &describeFleetAttributesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeFleetAttributesRequest(describeFleetAttributesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeFleetAttributesAsync(
                describeFleetAttributesRequest.toAWS(),
                [&success, &describeFleetAttributesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeFleetAttributesRequest &awsDescribeFleetAttributesRequest,
                        const Aws::GameLift::Model::DescribeFleetAttributesOutcome &awsDescribeFleetAttributesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeFleetAttributesOutcome.IsSuccess();
                    if (success) {
                        describeFleetAttributesResult.fromAWS(awsDescribeFleetAttributesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeFleetAttributesOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeFleetAttributesOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeFleetAttributes Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeFleetAttributes(
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetAttributesRequest describeFleetAttributesRequest,
        FDescribeFleetAttributesResult &describeFleetAttributesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeFleetAttributesAction>(LatentInfo.CallbackTarget,
                                                                                   LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeFleetAttributesAction(this->awsGameLiftClient,
                                                                                success,
                                                                                describeFleetAttributesRequest,
                                                                                describeFleetAttributesResult,
                                                                                errorType,
                                                                                errorMessage,
                                                                                LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeFleetCapacityAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeFleetCapacityRequest describeFleetCapacityRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeFleetCapacityAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeFleetCapacityRequest describeFleetCapacityRequest,
            FDescribeFleetCapacityResult &describeFleetCapacityResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeFleetCapacityRequest(describeFleetCapacityRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeFleetCapacityAsync(
                describeFleetCapacityRequest.toAWS(),
                [&success, &describeFleetCapacityResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeFleetCapacityRequest &awsDescribeFleetCapacityRequest,
                        const Aws::GameLift::Model::DescribeFleetCapacityOutcome &awsDescribeFleetCapacityOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeFleetCapacityOutcome.IsSuccess();
                    if (success) {
                        describeFleetCapacityResult.fromAWS(awsDescribeFleetCapacityOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeFleetCapacityOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeFleetCapacityOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeFleetCapacity Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeFleetCapacity(
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetCapacityRequest describeFleetCapacityRequest,
        FDescribeFleetCapacityResult &describeFleetCapacityResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeFleetCapacityAction>(LatentInfo.CallbackTarget,
                                                                                 LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeFleetCapacityAction(this->awsGameLiftClient,
                                                                              success,
                                                                              describeFleetCapacityRequest,
                                                                              describeFleetCapacityResult,
                                                                              errorType,
                                                                              errorMessage,
                                                                              LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeFleetEventsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeFleetEventsRequest describeFleetEventsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeFleetEventsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeFleetEventsRequest describeFleetEventsRequest,
            FDescribeFleetEventsResult &describeFleetEventsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeFleetEventsRequest(describeFleetEventsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeFleetEventsAsync(
                describeFleetEventsRequest.toAWS(),
                [&success, &describeFleetEventsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeFleetEventsRequest &awsDescribeFleetEventsRequest,
                        const Aws::GameLift::Model::DescribeFleetEventsOutcome &awsDescribeFleetEventsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeFleetEventsOutcome.IsSuccess();
                    if (success) {
                        describeFleetEventsResult.fromAWS(awsDescribeFleetEventsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeFleetEventsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeFleetEventsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeFleetEvents Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeFleetEvents(
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetEventsRequest describeFleetEventsRequest,
        FDescribeFleetEventsResult &describeFleetEventsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeFleetEventsAction>(LatentInfo.CallbackTarget,
                                                                               LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeFleetEventsAction(this->awsGameLiftClient,
                                                                            success,
                                                                            describeFleetEventsRequest,
                                                                            describeFleetEventsResult,
                                                                            errorType,
                                                                            errorMessage,
                                                                            LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeFleetPortSettingsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeFleetPortSettingsRequest describeFleetPortSettingsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeFleetPortSettingsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeFleetPortSettingsRequest describeFleetPortSettingsRequest,
            FDescribeFleetPortSettingsResult &describeFleetPortSettingsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeFleetPortSettingsRequest(describeFleetPortSettingsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeFleetPortSettingsAsync(
                describeFleetPortSettingsRequest.toAWS(),
                [&success, &describeFleetPortSettingsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeFleetPortSettingsRequest &awsDescribeFleetPortSettingsRequest,
                        const Aws::GameLift::Model::DescribeFleetPortSettingsOutcome &awsDescribeFleetPortSettingsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeFleetPortSettingsOutcome.IsSuccess();
                    if (success) {
                        describeFleetPortSettingsResult.fromAWS(awsDescribeFleetPortSettingsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeFleetPortSettingsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeFleetPortSettingsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeFleetPortSettings Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeFleetPortSettings(
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetPortSettingsRequest describeFleetPortSettingsRequest,
        FDescribeFleetPortSettingsResult &describeFleetPortSettingsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeFleetPortSettingsAction>(LatentInfo.CallbackTarget,
                                                                                     LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeFleetPortSettingsAction(this->awsGameLiftClient,
                                                                                  success,
                                                                                  describeFleetPortSettingsRequest,
                                                                                  describeFleetPortSettingsResult,
                                                                                  errorType,
                                                                                  errorMessage,
                                                                                  LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeFleetUtilizationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeFleetUtilizationRequest describeFleetUtilizationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeFleetUtilizationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeFleetUtilizationRequest describeFleetUtilizationRequest,
            FDescribeFleetUtilizationResult &describeFleetUtilizationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeFleetUtilizationRequest(describeFleetUtilizationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeFleetUtilizationAsync(
                describeFleetUtilizationRequest.toAWS(),
                [&success, &describeFleetUtilizationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeFleetUtilizationRequest &awsDescribeFleetUtilizationRequest,
                        const Aws::GameLift::Model::DescribeFleetUtilizationOutcome &awsDescribeFleetUtilizationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeFleetUtilizationOutcome.IsSuccess();
                    if (success) {
                        describeFleetUtilizationResult.fromAWS(awsDescribeFleetUtilizationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeFleetUtilizationOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeFleetUtilizationOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeFleetUtilization Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeFleetUtilization(
        UObject *WorldContextObject,
        bool &success,
        FDescribeFleetUtilizationRequest describeFleetUtilizationRequest,
        FDescribeFleetUtilizationResult &describeFleetUtilizationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeFleetUtilizationAction>(LatentInfo.CallbackTarget,
                                                                                    LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeFleetUtilizationAction(this->awsGameLiftClient,
                                                                                 success,
                                                                                 describeFleetUtilizationRequest,
                                                                                 describeFleetUtilizationResult,
                                                                                 errorType,
                                                                                 errorMessage,
                                                                                 LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeGameSessionDetailsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeGameSessionDetailsRequest describeGameSessionDetailsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGameSessionDetailsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeGameSessionDetailsRequest describeGameSessionDetailsRequest,
            FDescribeGameSessionDetailsResult &describeGameSessionDetailsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeGameSessionDetailsRequest(describeGameSessionDetailsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeGameSessionDetailsAsync(
                describeGameSessionDetailsRequest.toAWS(),
                [&success, &describeGameSessionDetailsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeGameSessionDetailsRequest &awsDescribeGameSessionDetailsRequest,
                        const Aws::GameLift::Model::DescribeGameSessionDetailsOutcome &awsDescribeGameSessionDetailsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeGameSessionDetailsOutcome.IsSuccess();
                    if (success) {
                        describeGameSessionDetailsResult.fromAWS(awsDescribeGameSessionDetailsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeGameSessionDetailsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeGameSessionDetailsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeGameSessionDetails Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeGameSessionDetails(
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionDetailsRequest describeGameSessionDetailsRequest,
        FDescribeGameSessionDetailsResult &describeGameSessionDetailsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGameSessionDetailsAction>(LatentInfo.CallbackTarget,
                                                                                      LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeGameSessionDetailsAction(this->awsGameLiftClient,
                                                                                   success,
                                                                                   describeGameSessionDetailsRequest,
                                                                                   describeGameSessionDetailsResult,
                                                                                   errorType,
                                                                                   errorMessage,
                                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeGameSessionPlacementAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeGameSessionPlacementRequest describeGameSessionPlacementRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGameSessionPlacementAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeGameSessionPlacementRequest describeGameSessionPlacementRequest,
            FDescribeGameSessionPlacementResult &describeGameSessionPlacementResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeGameSessionPlacementRequest(describeGameSessionPlacementRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeGameSessionPlacementAsync(
                describeGameSessionPlacementRequest.toAWS(),
                [&success, &describeGameSessionPlacementResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeGameSessionPlacementRequest &awsDescribeGameSessionPlacementRequest,
                        const Aws::GameLift::Model::DescribeGameSessionPlacementOutcome &awsDescribeGameSessionPlacementOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeGameSessionPlacementOutcome.IsSuccess();
                    if (success) {
                        describeGameSessionPlacementResult.fromAWS(awsDescribeGameSessionPlacementOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeGameSessionPlacementOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeGameSessionPlacementOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeGameSessionPlacement Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeGameSessionPlacement(
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionPlacementRequest describeGameSessionPlacementRequest,
        FDescribeGameSessionPlacementResult &describeGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGameSessionPlacementAction>(LatentInfo.CallbackTarget,
                                                                                        LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeGameSessionPlacementAction(this->awsGameLiftClient,
                                                                                     success,
                                                                                     describeGameSessionPlacementRequest,
                                                                                     describeGameSessionPlacementResult,
                                                                                     errorType,
                                                                                     errorMessage,
                                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeGameSessionQueuesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeGameSessionQueuesRequest describeGameSessionQueuesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGameSessionQueuesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeGameSessionQueuesRequest describeGameSessionQueuesRequest,
            FDescribeGameSessionQueuesResult &describeGameSessionQueuesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeGameSessionQueuesRequest(describeGameSessionQueuesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeGameSessionQueuesAsync(
                describeGameSessionQueuesRequest.toAWS(),
                [&success, &describeGameSessionQueuesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeGameSessionQueuesRequest &awsDescribeGameSessionQueuesRequest,
                        const Aws::GameLift::Model::DescribeGameSessionQueuesOutcome &awsDescribeGameSessionQueuesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeGameSessionQueuesOutcome.IsSuccess();
                    if (success) {
                        describeGameSessionQueuesResult.fromAWS(awsDescribeGameSessionQueuesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeGameSessionQueuesOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeGameSessionQueuesOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeGameSessionQueues Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeGameSessionQueues(
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionQueuesRequest describeGameSessionQueuesRequest,
        FDescribeGameSessionQueuesResult &describeGameSessionQueuesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGameSessionQueuesAction>(LatentInfo.CallbackTarget,
                                                                                     LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeGameSessionQueuesAction(this->awsGameLiftClient,
                                                                                  success,
                                                                                  describeGameSessionQueuesRequest,
                                                                                  describeGameSessionQueuesResult,
                                                                                  errorType,
                                                                                  errorMessage,
                                                                                  LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeGameSessionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeGameSessionsRequest describeGameSessionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeGameSessionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeGameSessionsRequest describeGameSessionsRequest,
            FDescribeGameSessionsResult &describeGameSessionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeGameSessionsRequest(describeGameSessionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeGameSessionsAsync(
                describeGameSessionsRequest.toAWS(),
                [&success, &describeGameSessionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeGameSessionsRequest &awsDescribeGameSessionsRequest,
                        const Aws::GameLift::Model::DescribeGameSessionsOutcome &awsDescribeGameSessionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeGameSessionsOutcome.IsSuccess();
                    if (success) {
                        describeGameSessionsResult.fromAWS(awsDescribeGameSessionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeGameSessionsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeGameSessionsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeGameSessions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeGameSessions(
        UObject *WorldContextObject,
        bool &success,
        FDescribeGameSessionsRequest describeGameSessionsRequest,
        FDescribeGameSessionsResult &describeGameSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeGameSessionsAction>(LatentInfo.CallbackTarget,
                                                                                LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeGameSessionsAction(this->awsGameLiftClient,
                                                                             success,
                                                                             describeGameSessionsRequest,
                                                                             describeGameSessionsResult,
                                                                             errorType,
                                                                             errorMessage,
                                                                             LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeInstancesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeInstancesRequest describeInstancesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeInstancesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeInstancesRequest describeInstancesRequest,
            FDescribeInstancesResult &describeInstancesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeInstancesRequest(describeInstancesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeInstancesAsync(
                describeInstancesRequest.toAWS(),
                [&success, &describeInstancesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeInstancesRequest &awsDescribeInstancesRequest,
                        const Aws::GameLift::Model::DescribeInstancesOutcome &awsDescribeInstancesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeInstancesOutcome.IsSuccess();
                    if (success) {
                        describeInstancesResult.fromAWS(awsDescribeInstancesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeInstancesOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeInstancesOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeInstances Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeInstances(
        UObject *WorldContextObject,
        bool &success,
        FDescribeInstancesRequest describeInstancesRequest,
        FDescribeInstancesResult &describeInstancesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeInstancesAction>(LatentInfo.CallbackTarget,
                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeInstancesAction(this->awsGameLiftClient,
                                                                          success,
                                                                          describeInstancesRequest,
                                                                          describeInstancesResult,
                                                                          errorType,
                                                                          errorMessage,
                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeMatchmakingAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeMatchmakingRequest describeMatchmakingRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeMatchmakingAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeMatchmakingRequest describeMatchmakingRequest,
            FDescribeMatchmakingResult &describeMatchmakingResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeMatchmakingRequest(describeMatchmakingRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeMatchmakingAsync(
                describeMatchmakingRequest.toAWS(),
                [&success, &describeMatchmakingResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeMatchmakingRequest &awsDescribeMatchmakingRequest,
                        const Aws::GameLift::Model::DescribeMatchmakingOutcome &awsDescribeMatchmakingOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeMatchmakingOutcome.IsSuccess();
                    if (success) {
                        describeMatchmakingResult.fromAWS(awsDescribeMatchmakingOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeMatchmakingOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeMatchmakingOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeMatchmaking Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeMatchmaking(
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingRequest describeMatchmakingRequest,
        FDescribeMatchmakingResult &describeMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeMatchmakingAction>(LatentInfo.CallbackTarget,
                                                                               LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeMatchmakingAction(this->awsGameLiftClient,
                                                                            success,
                                                                            describeMatchmakingRequest,
                                                                            describeMatchmakingResult,
                                                                            errorType,
                                                                            errorMessage,
                                                                            LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeMatchmakingConfigurationsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeMatchmakingConfigurationsRequest describeMatchmakingConfigurationsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeMatchmakingConfigurationsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeMatchmakingConfigurationsRequest describeMatchmakingConfigurationsRequest,
            FDescribeMatchmakingConfigurationsResult &describeMatchmakingConfigurationsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              describeMatchmakingConfigurationsRequest(describeMatchmakingConfigurationsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeMatchmakingConfigurationsAsync(
                describeMatchmakingConfigurationsRequest.toAWS(),
                [&success, &describeMatchmakingConfigurationsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeMatchmakingConfigurationsRequest &awsDescribeMatchmakingConfigurationsRequest,
                        const Aws::GameLift::Model::DescribeMatchmakingConfigurationsOutcome &awsDescribeMatchmakingConfigurationsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeMatchmakingConfigurationsOutcome.IsSuccess();
                    if (success) {
                        describeMatchmakingConfigurationsResult.fromAWS(
                                awsDescribeMatchmakingConfigurationsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeMatchmakingConfigurationsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeMatchmakingConfigurationsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeMatchmakingConfigurations Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeMatchmakingConfigurations(
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingConfigurationsRequest describeMatchmakingConfigurationsRequest,
        FDescribeMatchmakingConfigurationsResult &describeMatchmakingConfigurationsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeMatchmakingConfigurationsAction>(LatentInfo.CallbackTarget,
                                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeMatchmakingConfigurationsAction(this->awsGameLiftClient,
                                                                                          success,
                                                                                          describeMatchmakingConfigurationsRequest,
                                                                                          describeMatchmakingConfigurationsResult,
                                                                                          errorType,
                                                                                          errorMessage,
                                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeMatchmakingRuleSetsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeMatchmakingRuleSetsRequest describeMatchmakingRuleSetsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeMatchmakingRuleSetsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeMatchmakingRuleSetsRequest describeMatchmakingRuleSetsRequest,
            FDescribeMatchmakingRuleSetsResult &describeMatchmakingRuleSetsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeMatchmakingRuleSetsRequest(describeMatchmakingRuleSetsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeMatchmakingRuleSetsAsync(
                describeMatchmakingRuleSetsRequest.toAWS(),
                [&success, &describeMatchmakingRuleSetsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeMatchmakingRuleSetsRequest &awsDescribeMatchmakingRuleSetsRequest,
                        const Aws::GameLift::Model::DescribeMatchmakingRuleSetsOutcome &awsDescribeMatchmakingRuleSetsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeMatchmakingRuleSetsOutcome.IsSuccess();
                    if (success) {
                        describeMatchmakingRuleSetsResult.fromAWS(awsDescribeMatchmakingRuleSetsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeMatchmakingRuleSetsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeMatchmakingRuleSetsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeMatchmakingRuleSets Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeMatchmakingRuleSets(
        UObject *WorldContextObject,
        bool &success,
        FDescribeMatchmakingRuleSetsRequest describeMatchmakingRuleSetsRequest,
        FDescribeMatchmakingRuleSetsResult &describeMatchmakingRuleSetsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeMatchmakingRuleSetsAction>(LatentInfo.CallbackTarget,
                                                                                       LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeMatchmakingRuleSetsAction(this->awsGameLiftClient,
                                                                                    success,
                                                                                    describeMatchmakingRuleSetsRequest,
                                                                                    describeMatchmakingRuleSetsResult,
                                                                                    errorType,
                                                                                    errorMessage,
                                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribePlayerSessionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribePlayerSessionsRequest describePlayerSessionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribePlayerSessionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribePlayerSessionsRequest describePlayerSessionsRequest,
            FDescribePlayerSessionsResult &describePlayerSessionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describePlayerSessionsRequest(describePlayerSessionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribePlayerSessionsAsync(
                describePlayerSessionsRequest.toAWS(),
                [&success, &describePlayerSessionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribePlayerSessionsRequest &awsDescribePlayerSessionsRequest,
                        const Aws::GameLift::Model::DescribePlayerSessionsOutcome &awsDescribePlayerSessionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribePlayerSessionsOutcome.IsSuccess();
                    if (success) {
                        describePlayerSessionsResult.fromAWS(awsDescribePlayerSessionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribePlayerSessionsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribePlayerSessionsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribePlayerSessions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribePlayerSessions(
        UObject *WorldContextObject,
        bool &success,
        FDescribePlayerSessionsRequest describePlayerSessionsRequest,
        FDescribePlayerSessionsResult &describePlayerSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribePlayerSessionsAction>(LatentInfo.CallbackTarget,
                                                                                  LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribePlayerSessionsAction(this->awsGameLiftClient,
                                                                               success,
                                                                               describePlayerSessionsRequest,
                                                                               describePlayerSessionsResult,
                                                                               errorType,
                                                                               errorMessage,
                                                                               LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeRuntimeConfigurationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeRuntimeConfigurationRequest describeRuntimeConfigurationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeRuntimeConfigurationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeRuntimeConfigurationRequest describeRuntimeConfigurationRequest,
            FDescribeRuntimeConfigurationResult &describeRuntimeConfigurationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeRuntimeConfigurationRequest(describeRuntimeConfigurationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeRuntimeConfigurationAsync(
                describeRuntimeConfigurationRequest.toAWS(),
                [&success, &describeRuntimeConfigurationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeRuntimeConfigurationRequest &awsDescribeRuntimeConfigurationRequest,
                        const Aws::GameLift::Model::DescribeRuntimeConfigurationOutcome &awsDescribeRuntimeConfigurationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeRuntimeConfigurationOutcome.IsSuccess();
                    if (success) {
                        describeRuntimeConfigurationResult.fromAWS(awsDescribeRuntimeConfigurationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeRuntimeConfigurationOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeRuntimeConfigurationOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeRuntimeConfiguration Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeRuntimeConfiguration(
        UObject *WorldContextObject,
        bool &success,
        FDescribeRuntimeConfigurationRequest describeRuntimeConfigurationRequest,
        FDescribeRuntimeConfigurationResult &describeRuntimeConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeRuntimeConfigurationAction>(LatentInfo.CallbackTarget,
                                                                                        LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeRuntimeConfigurationAction(this->awsGameLiftClient,
                                                                                     success,
                                                                                     describeRuntimeConfigurationRequest,
                                                                                     describeRuntimeConfigurationResult,
                                                                                     errorType,
                                                                                     errorMessage,
                                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeScalingPoliciesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeScalingPoliciesRequest describeScalingPoliciesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeScalingPoliciesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeScalingPoliciesRequest describeScalingPoliciesRequest,
            FDescribeScalingPoliciesResult &describeScalingPoliciesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeScalingPoliciesRequest(describeScalingPoliciesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeScalingPoliciesAsync(
                describeScalingPoliciesRequest.toAWS(),
                [&success, &describeScalingPoliciesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeScalingPoliciesRequest &awsDescribeScalingPoliciesRequest,
                        const Aws::GameLift::Model::DescribeScalingPoliciesOutcome &awsDescribeScalingPoliciesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeScalingPoliciesOutcome.IsSuccess();
                    if (success) {
                        describeScalingPoliciesResult.fromAWS(awsDescribeScalingPoliciesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeScalingPoliciesOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeScalingPoliciesOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeScalingPolicies Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeScalingPolicies(
        UObject *WorldContextObject,
        bool &success,
        FDescribeScalingPoliciesRequest describeScalingPoliciesRequest,
        FDescribeScalingPoliciesResult &describeScalingPoliciesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeScalingPoliciesAction>(LatentInfo.CallbackTarget,
                                                                                   LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeScalingPoliciesAction(this->awsGameLiftClient,
                                                                                success,
                                                                                describeScalingPoliciesRequest,
                                                                                describeScalingPoliciesResult,
                                                                                errorType,
                                                                                errorMessage,
                                                                                LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeScriptAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeScriptRequest describeScriptRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeScriptAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeScriptRequest describeScriptRequest,
            FDescribeScriptResult &describeScriptResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), describeScriptRequest(describeScriptRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeScriptAsync(
                describeScriptRequest.toAWS(),
                [&success, &describeScriptResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeScriptRequest &awsDescribeScriptRequest,
                        const Aws::GameLift::Model::DescribeScriptOutcome &awsDescribeScriptOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeScriptOutcome.IsSuccess();
                    if (success) {
                        describeScriptResult.fromAWS(awsDescribeScriptOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeScriptOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeScriptOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeScript Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeScript(
        UObject *WorldContextObject,
        bool &success,
        FDescribeScriptRequest describeScriptRequest,
        FDescribeScriptResult &describeScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeScriptAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeScriptAction(this->awsGameLiftClient,
                                                                       success,
                                                                       describeScriptRequest,
                                                                       describeScriptResult,
                                                                       errorType,
                                                                       errorMessage,
                                                                       LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeVpcPeeringAuthorizationsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeVpcPeeringAuthorizationsRequest describeVpcPeeringAuthorizationsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeVpcPeeringAuthorizationsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeVpcPeeringAuthorizationsRequest describeVpcPeeringAuthorizationsRequest,
            FDescribeVpcPeeringAuthorizationsResult &describeVpcPeeringAuthorizationsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              describeVpcPeeringAuthorizationsRequest(describeVpcPeeringAuthorizationsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeVpcPeeringAuthorizationsAsync(
                describeVpcPeeringAuthorizationsRequest.toAWS(),
                [&success, &describeVpcPeeringAuthorizationsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsRequest &awsDescribeVpcPeeringAuthorizationsRequest,
                        const Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsOutcome &awsDescribeVpcPeeringAuthorizationsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeVpcPeeringAuthorizationsOutcome.IsSuccess();
                    if (success) {
                        describeVpcPeeringAuthorizationsResult.fromAWS(
                                awsDescribeVpcPeeringAuthorizationsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeVpcPeeringAuthorizationsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeVpcPeeringAuthorizationsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeVpcPeeringAuthorizations Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeVpcPeeringAuthorizations(
        UObject *WorldContextObject,
        bool &success,
        FDescribeVpcPeeringAuthorizationsRequest describeVpcPeeringAuthorizationsRequest,
        FDescribeVpcPeeringAuthorizationsResult &describeVpcPeeringAuthorizationsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeVpcPeeringAuthorizationsAction>(LatentInfo.CallbackTarget,
                                                                                            LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeVpcPeeringAuthorizationsAction(this->awsGameLiftClient,
                                                                                         success,
                                                                                         describeVpcPeeringAuthorizationsRequest,
                                                                                         describeVpcPeeringAuthorizationsResult,
                                                                                         errorType,
                                                                                         errorMessage,
                                                                                         LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FDescribeVpcPeeringConnectionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FDescribeVpcPeeringConnectionsRequest describeVpcPeeringConnectionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FDescribeVpcPeeringConnectionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FDescribeVpcPeeringConnectionsRequest describeVpcPeeringConnectionsRequest,
            FDescribeVpcPeeringConnectionsResult &describeVpcPeeringConnectionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              describeVpcPeeringConnectionsRequest(describeVpcPeeringConnectionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->DescribeVpcPeeringConnectionsAsync(
                describeVpcPeeringConnectionsRequest.toAWS(),
                [&success, &describeVpcPeeringConnectionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::DescribeVpcPeeringConnectionsRequest &awsDescribeVpcPeeringConnectionsRequest,
                        const Aws::GameLift::Model::DescribeVpcPeeringConnectionsOutcome &awsDescribeVpcPeeringConnectionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsDescribeVpcPeeringConnectionsOutcome.IsSuccess();
                    if (success) {
                        describeVpcPeeringConnectionsResult.fromAWS(awsDescribeVpcPeeringConnectionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsDescribeVpcPeeringConnectionsOutcome.GetError().GetErrorType());
                    errorMessage = awsDescribeVpcPeeringConnectionsOutcome.GetError().GetMessage().c_str();
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
        return FString("DescribeVpcPeeringConnections Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::DescribeVpcPeeringConnections(
        UObject *WorldContextObject,
        bool &success,
        FDescribeVpcPeeringConnectionsRequest describeVpcPeeringConnectionsRequest,
        FDescribeVpcPeeringConnectionsResult &describeVpcPeeringConnectionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeVpcPeeringConnectionsAction>(LatentInfo.CallbackTarget,
                                                                                         LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FDescribeVpcPeeringConnectionsAction(this->awsGameLiftClient,
                                                                                      success,
                                                                                      describeVpcPeeringConnectionsRequest,
                                                                                      describeVpcPeeringConnectionsResult,
                                                                                      errorType,
                                                                                      errorMessage,
                                                                                      LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FGetGameSessionLogUrlAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGetGameSessionLogUrlRequest getGameSessionLogUrlRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FGetGameSessionLogUrlAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGetGameSessionLogUrlRequest getGameSessionLogUrlRequest,
            FGetGameSessionLogUrlResult &getGameSessionLogUrlResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), getGameSessionLogUrlRequest(getGameSessionLogUrlRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->GetGameSessionLogUrlAsync(
                getGameSessionLogUrlRequest.toAWS(),
                [&success, &getGameSessionLogUrlResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::GetGameSessionLogUrlRequest &awsGetGameSessionLogUrlRequest,
                        const Aws::GameLift::Model::GetGameSessionLogUrlOutcome &awsGetGameSessionLogUrlOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsGetGameSessionLogUrlOutcome.IsSuccess();
                    if (success) {
                        getGameSessionLogUrlResult.fromAWS(awsGetGameSessionLogUrlOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsGetGameSessionLogUrlOutcome.GetError().GetErrorType());
                    errorMessage = awsGetGameSessionLogUrlOutcome.GetError().GetMessage().c_str();
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
        return FString("GetGameSessionLogUrl Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::GetGameSessionLogUrl(
        UObject *WorldContextObject,
        bool &success,
        FGetGameSessionLogUrlRequest getGameSessionLogUrlRequest,
        FGetGameSessionLogUrlResult &getGameSessionLogUrlResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetGameSessionLogUrlAction>(LatentInfo.CallbackTarget,
                                                                                LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FGetGameSessionLogUrlAction(this->awsGameLiftClient,
                                                                             success,
                                                                             getGameSessionLogUrlRequest,
                                                                             getGameSessionLogUrlResult,
                                                                             errorType,
                                                                             errorMessage,
                                                                             LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FGetInstanceAccessAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGetInstanceAccessRequest getInstanceAccessRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FGetInstanceAccessAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGetInstanceAccessRequest getInstanceAccessRequest,
            FGetInstanceAccessResult &getInstanceAccessResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), getInstanceAccessRequest(getInstanceAccessRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->GetInstanceAccessAsync(
                getInstanceAccessRequest.toAWS(),
                [&success, &getInstanceAccessResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::GetInstanceAccessRequest &awsGetInstanceAccessRequest,
                        const Aws::GameLift::Model::GetInstanceAccessOutcome &awsGetInstanceAccessOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsGetInstanceAccessOutcome.IsSuccess();
                    if (success) {
                        getInstanceAccessResult.fromAWS(awsGetInstanceAccessOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsGetInstanceAccessOutcome.GetError().GetErrorType());
                    errorMessage = awsGetInstanceAccessOutcome.GetError().GetMessage().c_str();
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
        return FString("GetInstanceAccess Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::GetInstanceAccess(
        UObject *WorldContextObject,
        bool &success,
        FGetInstanceAccessRequest getInstanceAccessRequest,
        FGetInstanceAccessResult &getInstanceAccessResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetInstanceAccessAction>(LatentInfo.CallbackTarget,
                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FGetInstanceAccessAction(this->awsGameLiftClient,
                                                                          success,
                                                                          getInstanceAccessRequest,
                                                                          getInstanceAccessResult,
                                                                          errorType,
                                                                          errorMessage,
                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FListAliasesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGameLiftListAliasesRequest listAliasesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListAliasesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGameLiftListAliasesRequest listAliasesRequest,
            FGameLiftListAliasesResult &listAliasesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), listAliasesRequest(listAliasesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ListAliasesAsync(
                listAliasesRequest.toAWS(),
                [&success, &listAliasesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ListAliasesRequest &awsListAliasesRequest,
                        const Aws::GameLift::Model::ListAliasesOutcome &awsListAliasesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsListAliasesOutcome.IsSuccess();
                    if (success) {
                        listAliasesResult.fromAWS(awsListAliasesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsListAliasesOutcome.GetError().GetErrorType());
                    errorMessage = awsListAliasesOutcome.GetError().GetMessage().c_str();
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
        return FString("ListAliases Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ListAliases(
        UObject *WorldContextObject,
        bool &success,
        FGameLiftListAliasesRequest listAliasesRequest,
        FGameLiftListAliasesResult &listAliasesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListAliasesAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FListAliasesAction(this->awsGameLiftClient,
                                                                    success,
                                                                    listAliasesRequest,
                                                                    listAliasesResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FListBuildsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FListBuildsRequest listBuildsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListBuildsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FListBuildsRequest listBuildsRequest,
            FListBuildsResult &listBuildsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), listBuildsRequest(listBuildsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ListBuildsAsync(
                listBuildsRequest.toAWS(),
                [&success, &listBuildsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ListBuildsRequest &awsListBuildsRequest,
                        const Aws::GameLift::Model::ListBuildsOutcome &awsListBuildsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsListBuildsOutcome.IsSuccess();
                    if (success) {
                        listBuildsResult.fromAWS(awsListBuildsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsListBuildsOutcome.GetError().GetErrorType());
                    errorMessage = awsListBuildsOutcome.GetError().GetMessage().c_str();
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
        return FString("ListBuilds Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ListBuilds(
        UObject *WorldContextObject,
        bool &success,
        FListBuildsRequest listBuildsRequest,
        FListBuildsResult &listBuildsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListBuildsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FListBuildsAction(this->awsGameLiftClient,
                                                                   success,
                                                                   listBuildsRequest,
                                                                   listBuildsResult,
                                                                   errorType,
                                                                   errorMessage,
                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FListFleetsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FListFleetsRequest listFleetsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListFleetsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FListFleetsRequest listFleetsRequest,
            FListFleetsResult &listFleetsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), listFleetsRequest(listFleetsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ListFleetsAsync(
                listFleetsRequest.toAWS(),
                [&success, &listFleetsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ListFleetsRequest &awsListFleetsRequest,
                        const Aws::GameLift::Model::ListFleetsOutcome &awsListFleetsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsListFleetsOutcome.IsSuccess();
                    if (success) {
                        listFleetsResult.fromAWS(awsListFleetsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsListFleetsOutcome.GetError().GetErrorType());
                    errorMessage = awsListFleetsOutcome.GetError().GetMessage().c_str();
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
        return FString("ListFleets Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ListFleets(
        UObject *WorldContextObject,
        bool &success,
        FListFleetsRequest listFleetsRequest,
        FListFleetsResult &listFleetsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListFleetsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FListFleetsAction(this->awsGameLiftClient,
                                                                   success,
                                                                   listFleetsRequest,
                                                                   listFleetsResult,
                                                                   errorType,
                                                                   errorMessage,
                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FListScriptsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FListScriptsRequest listScriptsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FListScriptsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FListScriptsRequest listScriptsRequest,
            FListScriptsResult &listScriptsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), listScriptsRequest(listScriptsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ListScriptsAsync(
                listScriptsRequest.toAWS(),
                [&success, &listScriptsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ListScriptsRequest &awsListScriptsRequest,
                        const Aws::GameLift::Model::ListScriptsOutcome &awsListScriptsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsListScriptsOutcome.IsSuccess();
                    if (success) {
                        listScriptsResult.fromAWS(awsListScriptsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsListScriptsOutcome.GetError().GetErrorType());
                    errorMessage = awsListScriptsOutcome.GetError().GetMessage().c_str();
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
        return FString("ListScripts Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ListScripts(
        UObject *WorldContextObject,
        bool &success,
        FListScriptsRequest listScriptsRequest,
        FListScriptsResult &listScriptsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListScriptsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FListScriptsAction(this->awsGameLiftClient,
                                                                    success,
                                                                    listScriptsRequest,
                                                                    listScriptsResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FPutScalingPolicyAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FPutScalingPolicyRequest putScalingPolicyRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FPutScalingPolicyAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FPutScalingPolicyRequest putScalingPolicyRequest,
            FPutScalingPolicyResult &putScalingPolicyResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), putScalingPolicyRequest(putScalingPolicyRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->PutScalingPolicyAsync(
                putScalingPolicyRequest.toAWS(),
                [&success, &putScalingPolicyResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::PutScalingPolicyRequest &awsPutScalingPolicyRequest,
                        const Aws::GameLift::Model::PutScalingPolicyOutcome &awsPutScalingPolicyOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsPutScalingPolicyOutcome.IsSuccess();
                    if (success) {
                        putScalingPolicyResult.fromAWS(awsPutScalingPolicyOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsPutScalingPolicyOutcome.GetError().GetErrorType());
                    errorMessage = awsPutScalingPolicyOutcome.GetError().GetMessage().c_str();
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
        return FString("PutScalingPolicy Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::PutScalingPolicy(
        UObject *WorldContextObject,
        bool &success,
        FPutScalingPolicyRequest putScalingPolicyRequest,
        FPutScalingPolicyResult &putScalingPolicyResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutScalingPolicyAction>(LatentInfo.CallbackTarget,
                                                                            LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FPutScalingPolicyAction(this->awsGameLiftClient,
                                                                         success,
                                                                         putScalingPolicyRequest,
                                                                         putScalingPolicyResult,
                                                                         errorType,
                                                                         errorMessage,
                                                                         LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FRequestUploadCredentialsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FRequestUploadCredentialsRequest requestUploadCredentialsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FRequestUploadCredentialsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FRequestUploadCredentialsRequest requestUploadCredentialsRequest,
            FRequestUploadCredentialsResult &requestUploadCredentialsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), requestUploadCredentialsRequest(requestUploadCredentialsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->RequestUploadCredentialsAsync(
                requestUploadCredentialsRequest.toAWS(),
                [&success, &requestUploadCredentialsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::RequestUploadCredentialsRequest &awsRequestUploadCredentialsRequest,
                        const Aws::GameLift::Model::RequestUploadCredentialsOutcome &awsRequestUploadCredentialsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsRequestUploadCredentialsOutcome.IsSuccess();
                    if (success) {
                        requestUploadCredentialsResult.fromAWS(awsRequestUploadCredentialsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsRequestUploadCredentialsOutcome.GetError().GetErrorType());
                    errorMessage = awsRequestUploadCredentialsOutcome.GetError().GetMessage().c_str();
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
        return FString("RequestUploadCredentials Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::RequestUploadCredentials(
        UObject *WorldContextObject,
        bool &success,
        FRequestUploadCredentialsRequest requestUploadCredentialsRequest,
        FRequestUploadCredentialsResult &requestUploadCredentialsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FRequestUploadCredentialsAction>(LatentInfo.CallbackTarget,
                                                                                    LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FRequestUploadCredentialsAction(this->awsGameLiftClient,
                                                                                 success,
                                                                                 requestUploadCredentialsRequest,
                                                                                 requestUploadCredentialsResult,
                                                                                 errorType,
                                                                                 errorMessage,
                                                                                 LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FResolveAliasAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FResolveAliasRequest resolveAliasRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FResolveAliasAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FResolveAliasRequest resolveAliasRequest,
            FResolveAliasResult &resolveAliasResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), resolveAliasRequest(resolveAliasRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ResolveAliasAsync(
                resolveAliasRequest.toAWS(),
                [&success, &resolveAliasResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ResolveAliasRequest &awsResolveAliasRequest,
                        const Aws::GameLift::Model::ResolveAliasOutcome &awsResolveAliasOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsResolveAliasOutcome.IsSuccess();
                    if (success) {
                        resolveAliasResult.fromAWS(awsResolveAliasOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsResolveAliasOutcome.GetError().GetErrorType());
                    errorMessage = awsResolveAliasOutcome.GetError().GetMessage().c_str();
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
        return FString("ResolveAlias Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ResolveAlias(
        UObject *WorldContextObject,
        bool &success,
        FResolveAliasRequest resolveAliasRequest,
        FResolveAliasResult &resolveAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FResolveAliasAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FResolveAliasAction(this->awsGameLiftClient,
                                                                     success,
                                                                     resolveAliasRequest,
                                                                     resolveAliasResult,
                                                                     errorType,
                                                                     errorMessage,
                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FSearchGameSessionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FSearchGameSessionsRequest searchGameSessionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FSearchGameSessionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FSearchGameSessionsRequest searchGameSessionsRequest,
            FSearchGameSessionsResult &searchGameSessionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), searchGameSessionsRequest(searchGameSessionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->SearchGameSessionsAsync(
                searchGameSessionsRequest.toAWS(),
                [&success, &searchGameSessionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::SearchGameSessionsRequest &awsSearchGameSessionsRequest,
                        const Aws::GameLift::Model::SearchGameSessionsOutcome &awsSearchGameSessionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsSearchGameSessionsOutcome.IsSuccess();
                    if (success) {
                        searchGameSessionsResult.fromAWS(awsSearchGameSessionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsSearchGameSessionsOutcome.GetError().GetErrorType());
                    errorMessage = awsSearchGameSessionsOutcome.GetError().GetMessage().c_str();
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
        return FString("SearchGameSessions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::SearchGameSessions(
        UObject *WorldContextObject,
        bool &success,
        FSearchGameSessionsRequest searchGameSessionsRequest,
        FSearchGameSessionsResult &searchGameSessionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FSearchGameSessionsAction>(LatentInfo.CallbackTarget,
                                                                              LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FSearchGameSessionsAction(this->awsGameLiftClient,
                                                                           success,
                                                                           searchGameSessionsRequest,
                                                                           searchGameSessionsResult,
                                                                           errorType,
                                                                           errorMessage,
                                                                           LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStartFleetActionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStartFleetActionsRequest startFleetActionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStartFleetActionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStartFleetActionsRequest startFleetActionsRequest,
            FStartFleetActionsResult &startFleetActionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), startFleetActionsRequest(startFleetActionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StartFleetActionsAsync(
                startFleetActionsRequest.toAWS(),
                [&success, &startFleetActionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StartFleetActionsRequest &awsStartFleetActionsRequest,
                        const Aws::GameLift::Model::StartFleetActionsOutcome &awsStartFleetActionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStartFleetActionsOutcome.IsSuccess();
                    if (success) {
                        startFleetActionsResult.fromAWS(awsStartFleetActionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStartFleetActionsOutcome.GetError().GetErrorType());
                    errorMessage = awsStartFleetActionsOutcome.GetError().GetMessage().c_str();
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
        return FString("StartFleetActions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StartFleetActions(
        UObject *WorldContextObject,
        bool &success,
        FStartFleetActionsRequest startFleetActionsRequest,
        FStartFleetActionsResult &startFleetActionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStartFleetActionsAction>(LatentInfo.CallbackTarget,
                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStartFleetActionsAction(this->awsGameLiftClient,
                                                                          success,
                                                                          startFleetActionsRequest,
                                                                          startFleetActionsResult,
                                                                          errorType,
                                                                          errorMessage,
                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStartGameSessionPlacementAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStartGameSessionPlacementRequest startGameSessionPlacementRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStartGameSessionPlacementAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStartGameSessionPlacementRequest startGameSessionPlacementRequest,
            FStartGameSessionPlacementResult &startGameSessionPlacementResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), startGameSessionPlacementRequest(startGameSessionPlacementRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StartGameSessionPlacementAsync(
                startGameSessionPlacementRequest.toAWS(),
                [&success, &startGameSessionPlacementResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StartGameSessionPlacementRequest &awsStartGameSessionPlacementRequest,
                        const Aws::GameLift::Model::StartGameSessionPlacementOutcome &awsStartGameSessionPlacementOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStartGameSessionPlacementOutcome.IsSuccess();
                    if (success) {
                        startGameSessionPlacementResult.fromAWS(awsStartGameSessionPlacementOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStartGameSessionPlacementOutcome.GetError().GetErrorType());
                    errorMessage = awsStartGameSessionPlacementOutcome.GetError().GetMessage().c_str();
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
        return FString("StartGameSessionPlacement Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StartGameSessionPlacement(
        UObject *WorldContextObject,
        bool &success,
        FStartGameSessionPlacementRequest startGameSessionPlacementRequest,
        FStartGameSessionPlacementResult &startGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStartGameSessionPlacementAction>(LatentInfo.CallbackTarget,
                                                                                     LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStartGameSessionPlacementAction(this->awsGameLiftClient,
                                                                                  success,
                                                                                  startGameSessionPlacementRequest,
                                                                                  startGameSessionPlacementResult,
                                                                                  errorType,
                                                                                  errorMessage,
                                                                                  LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStartMatchBackfillAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStartMatchBackfillRequest startMatchBackfillRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStartMatchBackfillAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStartMatchBackfillRequest startMatchBackfillRequest,
            FStartMatchBackfillResult &startMatchBackfillResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), startMatchBackfillRequest(startMatchBackfillRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StartMatchBackfillAsync(
                startMatchBackfillRequest.toAWS(),
                [&success, &startMatchBackfillResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StartMatchBackfillRequest &awsStartMatchBackfillRequest,
                        const Aws::GameLift::Model::StartMatchBackfillOutcome &awsStartMatchBackfillOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStartMatchBackfillOutcome.IsSuccess();
                    if (success) {
                        startMatchBackfillResult.fromAWS(awsStartMatchBackfillOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStartMatchBackfillOutcome.GetError().GetErrorType());
                    errorMessage = awsStartMatchBackfillOutcome.GetError().GetMessage().c_str();
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
        return FString("StartMatchBackfill Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StartMatchBackfill(
        UObject *WorldContextObject,
        bool &success,
        FStartMatchBackfillRequest startMatchBackfillRequest,
        FStartMatchBackfillResult &startMatchBackfillResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStartMatchBackfillAction>(LatentInfo.CallbackTarget,
                                                                              LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStartMatchBackfillAction(this->awsGameLiftClient,
                                                                           success,
                                                                           startMatchBackfillRequest,
                                                                           startMatchBackfillResult,
                                                                           errorType,
                                                                           errorMessage,
                                                                           LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStartMatchmakingAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStartMatchmakingRequest startMatchmakingRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStartMatchmakingAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStartMatchmakingRequest startMatchmakingRequest,
            FStartMatchmakingResult &startMatchmakingResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), startMatchmakingRequest(startMatchmakingRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StartMatchmakingAsync(
                startMatchmakingRequest.toAWS(),
                [&success, &startMatchmakingResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StartMatchmakingRequest &awsStartMatchmakingRequest,
                        const Aws::GameLift::Model::StartMatchmakingOutcome &awsStartMatchmakingOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStartMatchmakingOutcome.IsSuccess();
                    if (success) {
                        startMatchmakingResult.fromAWS(awsStartMatchmakingOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStartMatchmakingOutcome.GetError().GetErrorType());
                    errorMessage = awsStartMatchmakingOutcome.GetError().GetMessage().c_str();
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
        return FString("StartMatchmaking Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StartMatchmaking(
        UObject *WorldContextObject,
        bool &success,
        FStartMatchmakingRequest startMatchmakingRequest,
        FStartMatchmakingResult &startMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStartMatchmakingAction>(LatentInfo.CallbackTarget,
                                                                            LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStartMatchmakingAction(this->awsGameLiftClient,
                                                                         success,
                                                                         startMatchmakingRequest,
                                                                         startMatchmakingResult,
                                                                         errorType,
                                                                         errorMessage,
                                                                         LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStopFleetActionsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStopFleetActionsRequest stopFleetActionsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStopFleetActionsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStopFleetActionsRequest stopFleetActionsRequest,
            FStopFleetActionsResult &stopFleetActionsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), stopFleetActionsRequest(stopFleetActionsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StopFleetActionsAsync(
                stopFleetActionsRequest.toAWS(),
                [&success, &stopFleetActionsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StopFleetActionsRequest &awsStopFleetActionsRequest,
                        const Aws::GameLift::Model::StopFleetActionsOutcome &awsStopFleetActionsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStopFleetActionsOutcome.IsSuccess();
                    if (success) {
                        stopFleetActionsResult.fromAWS(awsStopFleetActionsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStopFleetActionsOutcome.GetError().GetErrorType());
                    errorMessage = awsStopFleetActionsOutcome.GetError().GetMessage().c_str();
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
        return FString("StopFleetActions Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StopFleetActions(
        UObject *WorldContextObject,
        bool &success,
        FStopFleetActionsRequest stopFleetActionsRequest,
        FStopFleetActionsResult &stopFleetActionsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStopFleetActionsAction>(LatentInfo.CallbackTarget,
                                                                            LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStopFleetActionsAction(this->awsGameLiftClient,
                                                                         success,
                                                                         stopFleetActionsRequest,
                                                                         stopFleetActionsResult,
                                                                         errorType,
                                                                         errorMessage,
                                                                         LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStopGameSessionPlacementAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStopGameSessionPlacementRequest stopGameSessionPlacementRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStopGameSessionPlacementAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStopGameSessionPlacementRequest stopGameSessionPlacementRequest,
            FStopGameSessionPlacementResult &stopGameSessionPlacementResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), stopGameSessionPlacementRequest(stopGameSessionPlacementRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StopGameSessionPlacementAsync(
                stopGameSessionPlacementRequest.toAWS(),
                [&success, &stopGameSessionPlacementResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StopGameSessionPlacementRequest &awsStopGameSessionPlacementRequest,
                        const Aws::GameLift::Model::StopGameSessionPlacementOutcome &awsStopGameSessionPlacementOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStopGameSessionPlacementOutcome.IsSuccess();
                    if (success) {
                        stopGameSessionPlacementResult.fromAWS(awsStopGameSessionPlacementOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStopGameSessionPlacementOutcome.GetError().GetErrorType());
                    errorMessage = awsStopGameSessionPlacementOutcome.GetError().GetMessage().c_str();
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
        return FString("StopGameSessionPlacement Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StopGameSessionPlacement(
        UObject *WorldContextObject,
        bool &success,
        FStopGameSessionPlacementRequest stopGameSessionPlacementRequest,
        FStopGameSessionPlacementResult &stopGameSessionPlacementResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStopGameSessionPlacementAction>(LatentInfo.CallbackTarget,
                                                                                    LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStopGameSessionPlacementAction(this->awsGameLiftClient,
                                                                                 success,
                                                                                 stopGameSessionPlacementRequest,
                                                                                 stopGameSessionPlacementResult,
                                                                                 errorType,
                                                                                 errorMessage,
                                                                                 LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FStopMatchmakingAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FStopMatchmakingRequest stopMatchmakingRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FStopMatchmakingAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FStopMatchmakingRequest stopMatchmakingRequest,
            FStopMatchmakingResult &stopMatchmakingResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), stopMatchmakingRequest(stopMatchmakingRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->StopMatchmakingAsync(
                stopMatchmakingRequest.toAWS(),
                [&success, &stopMatchmakingResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::StopMatchmakingRequest &awsStopMatchmakingRequest,
                        const Aws::GameLift::Model::StopMatchmakingOutcome &awsStopMatchmakingOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsStopMatchmakingOutcome.IsSuccess();
                    if (success) {
                        stopMatchmakingResult.fromAWS(awsStopMatchmakingOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsStopMatchmakingOutcome.GetError().GetErrorType());
                    errorMessage = awsStopMatchmakingOutcome.GetError().GetMessage().c_str();
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
        return FString("StopMatchmaking Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::StopMatchmaking(
        UObject *WorldContextObject,
        bool &success,
        FStopMatchmakingRequest stopMatchmakingRequest,
        FStopMatchmakingResult &stopMatchmakingResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStopMatchmakingAction>(LatentInfo.CallbackTarget,
                                                                           LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FStopMatchmakingAction(this->awsGameLiftClient,
                                                                        success,
                                                                        stopMatchmakingRequest,
                                                                        stopMatchmakingResult,
                                                                        errorType,
                                                                        errorMessage,
                                                                        LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateAliasAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FGameLiftUpdateAliasRequest updateAliasRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateAliasAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FGameLiftUpdateAliasRequest updateAliasRequest,
            FGameLiftUpdateAliasResult &updateAliasResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateAliasRequest(updateAliasRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateAliasAsync(
                updateAliasRequest.toAWS(),
                [&success, &updateAliasResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateAliasRequest &awsUpdateAliasRequest,
                        const Aws::GameLift::Model::UpdateAliasOutcome &awsUpdateAliasOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateAliasOutcome.IsSuccess();
                    if (success) {
                        updateAliasResult.fromAWS(awsUpdateAliasOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateAliasOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateAliasOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateAlias Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateAlias(
        UObject *WorldContextObject,
        bool &success,
        FGameLiftUpdateAliasRequest updateAliasRequest,
        FGameLiftUpdateAliasResult &updateAliasResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateAliasAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateAliasAction(this->awsGameLiftClient,
                                                                    success,
                                                                    updateAliasRequest,
                                                                    updateAliasResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateBuildAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateBuildRequest updateBuildRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateBuildAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateBuildRequest updateBuildRequest,
            FUpdateBuildResult &updateBuildResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateBuildRequest(updateBuildRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateBuildAsync(
                updateBuildRequest.toAWS(),
                [&success, &updateBuildResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateBuildRequest &awsUpdateBuildRequest,
                        const Aws::GameLift::Model::UpdateBuildOutcome &awsUpdateBuildOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateBuildOutcome.IsSuccess();
                    if (success) {
                        updateBuildResult.fromAWS(awsUpdateBuildOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateBuildOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateBuildOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateBuild Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateBuild(
        UObject *WorldContextObject,
        bool &success,
        FUpdateBuildRequest updateBuildRequest,
        FUpdateBuildResult &updateBuildResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateBuildAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateBuildAction(this->awsGameLiftClient,
                                                                    success,
                                                                    updateBuildRequest,
                                                                    updateBuildResult,
                                                                    errorType,
                                                                    errorMessage,
                                                                    LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateFleetAttributesAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateFleetAttributesRequest updateFleetAttributesRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateFleetAttributesAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateFleetAttributesRequest updateFleetAttributesRequest,
            FUpdateFleetAttributesResult &updateFleetAttributesResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateFleetAttributesRequest(updateFleetAttributesRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateFleetAttributesAsync(
                updateFleetAttributesRequest.toAWS(),
                [&success, &updateFleetAttributesResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateFleetAttributesRequest &awsUpdateFleetAttributesRequest,
                        const Aws::GameLift::Model::UpdateFleetAttributesOutcome &awsUpdateFleetAttributesOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateFleetAttributesOutcome.IsSuccess();
                    if (success) {
                        updateFleetAttributesResult.fromAWS(awsUpdateFleetAttributesOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateFleetAttributesOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateFleetAttributesOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateFleetAttributes Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateFleetAttributes(
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetAttributesRequest updateFleetAttributesRequest,
        FUpdateFleetAttributesResult &updateFleetAttributesResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateFleetAttributesAction>(LatentInfo.CallbackTarget,
                                                                                 LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateFleetAttributesAction(this->awsGameLiftClient,
                                                                              success,
                                                                              updateFleetAttributesRequest,
                                                                              updateFleetAttributesResult,
                                                                              errorType,
                                                                              errorMessage,
                                                                              LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateFleetCapacityAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateFleetCapacityRequest updateFleetCapacityRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateFleetCapacityAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateFleetCapacityRequest updateFleetCapacityRequest,
            FUpdateFleetCapacityResult &updateFleetCapacityResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateFleetCapacityRequest(updateFleetCapacityRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateFleetCapacityAsync(
                updateFleetCapacityRequest.toAWS(),
                [&success, &updateFleetCapacityResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateFleetCapacityRequest &awsUpdateFleetCapacityRequest,
                        const Aws::GameLift::Model::UpdateFleetCapacityOutcome &awsUpdateFleetCapacityOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateFleetCapacityOutcome.IsSuccess();
                    if (success) {
                        updateFleetCapacityResult.fromAWS(awsUpdateFleetCapacityOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateFleetCapacityOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateFleetCapacityOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateFleetCapacity Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateFleetCapacity(
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetCapacityRequest updateFleetCapacityRequest,
        FUpdateFleetCapacityResult &updateFleetCapacityResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateFleetCapacityAction>(LatentInfo.CallbackTarget,
                                                                               LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateFleetCapacityAction(this->awsGameLiftClient,
                                                                            success,
                                                                            updateFleetCapacityRequest,
                                                                            updateFleetCapacityResult,
                                                                            errorType,
                                                                            errorMessage,
                                                                            LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateFleetPortSettingsAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateFleetPortSettingsRequest updateFleetPortSettingsRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateFleetPortSettingsAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateFleetPortSettingsRequest updateFleetPortSettingsRequest,
            FUpdateFleetPortSettingsResult &updateFleetPortSettingsResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateFleetPortSettingsRequest(updateFleetPortSettingsRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateFleetPortSettingsAsync(
                updateFleetPortSettingsRequest.toAWS(),
                [&success, &updateFleetPortSettingsResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateFleetPortSettingsRequest &awsUpdateFleetPortSettingsRequest,
                        const Aws::GameLift::Model::UpdateFleetPortSettingsOutcome &awsUpdateFleetPortSettingsOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateFleetPortSettingsOutcome.IsSuccess();
                    if (success) {
                        updateFleetPortSettingsResult.fromAWS(awsUpdateFleetPortSettingsOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateFleetPortSettingsOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateFleetPortSettingsOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateFleetPortSettings Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateFleetPortSettings(
        UObject *WorldContextObject,
        bool &success,
        FUpdateFleetPortSettingsRequest updateFleetPortSettingsRequest,
        FUpdateFleetPortSettingsResult &updateFleetPortSettingsResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateFleetPortSettingsAction>(LatentInfo.CallbackTarget,
                                                                                   LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateFleetPortSettingsAction(this->awsGameLiftClient,
                                                                                success,
                                                                                updateFleetPortSettingsRequest,
                                                                                updateFleetPortSettingsResult,
                                                                                errorType,
                                                                                errorMessage,
                                                                                LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateGameSessionAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateGameSessionRequest updateGameSessionRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateGameSessionAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateGameSessionRequest updateGameSessionRequest,
            FUpdateGameSessionResult &updateGameSessionResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateGameSessionRequest(updateGameSessionRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateGameSessionAsync(
                updateGameSessionRequest.toAWS(),
                [&success, &updateGameSessionResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateGameSessionRequest &awsUpdateGameSessionRequest,
                        const Aws::GameLift::Model::UpdateGameSessionOutcome &awsUpdateGameSessionOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateGameSessionOutcome.IsSuccess();
                    if (success) {
                        updateGameSessionResult.fromAWS(awsUpdateGameSessionOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateGameSessionOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateGameSessionOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateGameSession Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateGameSession(
        UObject *WorldContextObject,
        bool &success,
        FUpdateGameSessionRequest updateGameSessionRequest,
        FUpdateGameSessionResult &updateGameSessionResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateGameSessionAction>(LatentInfo.CallbackTarget,
                                                                             LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateGameSessionAction(this->awsGameLiftClient,
                                                                          success,
                                                                          updateGameSessionRequest,
                                                                          updateGameSessionResult,
                                                                          errorType,
                                                                          errorMessage,
                                                                          LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateGameSessionQueueAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateGameSessionQueueRequest updateGameSessionQueueRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateGameSessionQueueAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateGameSessionQueueRequest updateGameSessionQueueRequest,
            FUpdateGameSessionQueueResult &updateGameSessionQueueResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateGameSessionQueueRequest(updateGameSessionQueueRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateGameSessionQueueAsync(
                updateGameSessionQueueRequest.toAWS(),
                [&success, &updateGameSessionQueueResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateGameSessionQueueRequest &awsUpdateGameSessionQueueRequest,
                        const Aws::GameLift::Model::UpdateGameSessionQueueOutcome &awsUpdateGameSessionQueueOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateGameSessionQueueOutcome.IsSuccess();
                    if (success) {
                        updateGameSessionQueueResult.fromAWS(awsUpdateGameSessionQueueOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateGameSessionQueueOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateGameSessionQueueOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateGameSessionQueue Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateGameSessionQueue(
        UObject *WorldContextObject,
        bool &success,
        FUpdateGameSessionQueueRequest updateGameSessionQueueRequest,
        FUpdateGameSessionQueueResult &updateGameSessionQueueResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateGameSessionQueueAction>(LatentInfo.CallbackTarget,
                                                                                  LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateGameSessionQueueAction(this->awsGameLiftClient,
                                                                               success,
                                                                               updateGameSessionQueueRequest,
                                                                               updateGameSessionQueueResult,
                                                                               errorType,
                                                                               errorMessage,
                                                                               LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateMatchmakingConfigurationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateMatchmakingConfigurationRequest updateMatchmakingConfigurationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateMatchmakingConfigurationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateMatchmakingConfigurationRequest updateMatchmakingConfigurationRequest,
            FUpdateMatchmakingConfigurationResult &updateMatchmakingConfigurationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient),
              updateMatchmakingConfigurationRequest(updateMatchmakingConfigurationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateMatchmakingConfigurationAsync(
                updateMatchmakingConfigurationRequest.toAWS(),
                [&success, &updateMatchmakingConfigurationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateMatchmakingConfigurationRequest &awsUpdateMatchmakingConfigurationRequest,
                        const Aws::GameLift::Model::UpdateMatchmakingConfigurationOutcome &awsUpdateMatchmakingConfigurationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateMatchmakingConfigurationOutcome.IsSuccess();
                    if (success) {
                        updateMatchmakingConfigurationResult.fromAWS(awsUpdateMatchmakingConfigurationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateMatchmakingConfigurationOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateMatchmakingConfigurationOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateMatchmakingConfiguration Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateMatchmakingConfiguration(
        UObject *WorldContextObject,
        bool &success,
        FUpdateMatchmakingConfigurationRequest updateMatchmakingConfigurationRequest,
        FUpdateMatchmakingConfigurationResult &updateMatchmakingConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateMatchmakingConfigurationAction>(LatentInfo.CallbackTarget,
                                                                                          LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateMatchmakingConfigurationAction(this->awsGameLiftClient,
                                                                                       success,
                                                                                       updateMatchmakingConfigurationRequest,
                                                                                       updateMatchmakingConfigurationResult,
                                                                                       errorType,
                                                                                       errorMessage,
                                                                                       LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateRuntimeConfigurationAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateRuntimeConfigurationRequest updateRuntimeConfigurationRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateRuntimeConfigurationAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateRuntimeConfigurationRequest updateRuntimeConfigurationRequest,
            FUpdateRuntimeConfigurationResult &updateRuntimeConfigurationResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateRuntimeConfigurationRequest(updateRuntimeConfigurationRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateRuntimeConfigurationAsync(
                updateRuntimeConfigurationRequest.toAWS(),
                [&success, &updateRuntimeConfigurationResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateRuntimeConfigurationRequest &awsUpdateRuntimeConfigurationRequest,
                        const Aws::GameLift::Model::UpdateRuntimeConfigurationOutcome &awsUpdateRuntimeConfigurationOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateRuntimeConfigurationOutcome.IsSuccess();
                    if (success) {
                        updateRuntimeConfigurationResult.fromAWS(awsUpdateRuntimeConfigurationOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateRuntimeConfigurationOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateRuntimeConfigurationOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateRuntimeConfiguration Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateRuntimeConfiguration(
        UObject *WorldContextObject,
        bool &success,
        FUpdateRuntimeConfigurationRequest updateRuntimeConfigurationRequest,
        FUpdateRuntimeConfigurationResult &updateRuntimeConfigurationResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateRuntimeConfigurationAction>(LatentInfo.CallbackTarget,
                                                                                      LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateRuntimeConfigurationAction(this->awsGameLiftClient,
                                                                                   success,
                                                                                   updateRuntimeConfigurationRequest,
                                                                                   updateRuntimeConfigurationResult,
                                                                                   errorType,
                                                                                   errorMessage,
                                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FUpdateScriptAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FUpdateScriptRequest updateScriptRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FUpdateScriptAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FUpdateScriptRequest updateScriptRequest,
            FUpdateScriptResult &updateScriptResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), updateScriptRequest(updateScriptRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->UpdateScriptAsync(
                updateScriptRequest.toAWS(),
                [&success, &updateScriptResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::UpdateScriptRequest &awsUpdateScriptRequest,
                        const Aws::GameLift::Model::UpdateScriptOutcome &awsUpdateScriptOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsUpdateScriptOutcome.IsSuccess();
                    if (success) {
                        updateScriptResult.fromAWS(awsUpdateScriptOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsUpdateScriptOutcome.GetError().GetErrorType());
                    errorMessage = awsUpdateScriptOutcome.GetError().GetMessage().c_str();
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
        return FString("UpdateScript Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::UpdateScript(
        UObject *WorldContextObject,
        bool &success,
        FUpdateScriptRequest updateScriptRequest,
        FUpdateScriptResult &updateScriptResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUpdateScriptAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) ==
            NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FUpdateScriptAction(this->awsGameLiftClient,
                                                                     success,
                                                                     updateScriptRequest,
                                                                     updateScriptResult,
                                                                     errorType,
                                                                     errorMessage,
                                                                     LatentInfo));
        }
    }
    return;
#endif
    return;
}

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

class FValidateMatchmakingRuleSetAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    Aws::GameLift::GameLiftClient *GameLiftClient;
    FValidateMatchmakingRuleSetRequest validateMatchmakingRuleSetRequest;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FValidateMatchmakingRuleSetAction(
            Aws::GameLift::GameLiftClient *GameLiftClient,
            bool &success,
            FValidateMatchmakingRuleSetRequest validateMatchmakingRuleSetRequest,
            FValidateMatchmakingRuleSetResult &validateMatchmakingRuleSetResult,
            EGameLiftError &errorType,
            FString &errorMessage,
            const FLatentActionInfo &LatentInfo
    )
            : GameLiftClient(GameLiftClient), validateMatchmakingRuleSetRequest(validateMatchmakingRuleSetRequest),
              ExecutionFunction(LatentInfo.ExecutionFunction),
              OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        GameLiftClient->ValidateMatchmakingRuleSetAsync(
                validateMatchmakingRuleSetRequest.toAWS(),
                [&success, &validateMatchmakingRuleSetResult, &errorType, &errorMessage, this](
                        const Aws::GameLift::GameLiftClient *awsGameLiftClient,
                        const Aws::GameLift::Model::ValidateMatchmakingRuleSetRequest &awsValidateMatchmakingRuleSetRequest,
                        const Aws::GameLift::Model::ValidateMatchmakingRuleSetOutcome &awsValidateMatchmakingRuleSetOutcome,
                        const std::shared_ptr<const Aws::Client::AsyncCallerContext> &awsAsyncCallerContext
                ) mutable -> void {
                    success = awsValidateMatchmakingRuleSetOutcome.IsSuccess();
                    if (success) {
                        validateMatchmakingRuleSetResult.fromAWS(awsValidateMatchmakingRuleSetOutcome.GetResult());
                    }
                   
                    errorType = fromAWS(awsValidateMatchmakingRuleSetOutcome.GetError().GetErrorType());
                    errorMessage = awsValidateMatchmakingRuleSetOutcome.GetError().GetMessage().c_str();
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
        return FString("ValidateMatchmakingRuleSet Request");
    }

#endif
};

#endif

void
UGameLiftClientObject::ValidateMatchmakingRuleSet(
        UObject *WorldContextObject,
        bool &success,
        FValidateMatchmakingRuleSetRequest validateMatchmakingRuleSetRequest,
        FValidateMatchmakingRuleSetResult &validateMatchmakingRuleSetResult,
        EGameLiftError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FValidateMatchmakingRuleSetAction>(LatentInfo.CallbackTarget,
                                                                                      LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                                             new FValidateMatchmakingRuleSetAction(this->awsGameLiftClient,
                                                                                   success,
                                                                                   validateMatchmakingRuleSetRequest,
                                                                                   validateMatchmakingRuleSetResult,
                                                                                   errorType,
                                                                                   errorMessage,
                                                                                   LatentInfo));
        }
    }
    return;
#endif
    return;
}
