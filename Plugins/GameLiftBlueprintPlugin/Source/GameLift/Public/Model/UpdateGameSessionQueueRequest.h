/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/UpdateGameSessionQueueRequest.h"

#endif

#include "Model/PlayerLatencyPolicy.h"
#include "Model/GameSessionQueueDestination.h"

#include "UpdateGameSessionQueueRequest.generated.h"

USTRUCT(BlueprintType)
struct FUpdateGameSessionQueueRequest {
GENERATED_BODY()

    /**
    *  <p>Descriptive label that is associated with game session queue. Queue names must be unique within each region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Maximum time, in seconds, that a new game session placement request remains in the queue. When a request exceeds this time, the game session placement changes to a <code>TIMED_OUT</code> status.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int timeoutInSeconds;

    /**
    *  <p>Collection of latency policies to apply when processing game sessions placement requests with player latency information. Multiple policies are evaluated in order of the maximum latency value, starting with the lowest latency values. With just one policy, it is enforced at the start of the game session placement for the duration period. With multiple policies, each policy is enforced consecutively for its duration period. For example, a queue might enforce a 60-second policy followed by a 120-second policy, and then no policy for the remainder of the placement. When updating policies, provide a complete collection of policies.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FPlayerLatencyPolicy> playerLatencyPolicies;

    /**
    *  <p>List of fleets that can be used to fulfill game session placement requests in the queue. Fleets are identified by either a fleet ARN or a fleet alias ARN. Destinations are listed in default preference order. When updating this list, provide a complete list of destinations.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FGameSessionQueueDestination> destinations;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::UpdateGameSessionQueueRequest toAWS() const {
        Aws::GameLift::Model::UpdateGameSessionQueueRequest awsUpdateGameSessionQueueRequest;

        if (!(this->name.IsEmpty())) {
            awsUpdateGameSessionQueueRequest.SetName(TCHAR_TO_UTF8(*this->name));
        }

        if (this->timeoutInSeconds != 0) {
            awsUpdateGameSessionQueueRequest.SetTimeoutInSeconds(this->timeoutInSeconds);
        }

        for (const FPlayerLatencyPolicy& elem : this->playerLatencyPolicies) {
            awsUpdateGameSessionQueueRequest.AddPlayerLatencyPolicies(elem.toAWS());
        }

        for (const FGameSessionQueueDestination& elem : this->destinations) {
            awsUpdateGameSessionQueueRequest.AddDestinations(elem.toAWS());
        }

        return awsUpdateGameSessionQueueRequest;
    }

    bool IsEmpty() const {
        return this->name.IsEmpty() && this->timeoutInSeconds == 0 && this->playerLatencyPolicies.Num() == 0 && this->destinations.Num() == 0;
    }
#endif
};
