/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/GameSessionQueue.h"

#endif

#include "Model/PlayerLatencyPolicy.h"
#include "Model/GameSessionQueueDestination.h"

#include "GameSessionQueue.generated.h"

USTRUCT(BlueprintType)
struct FGameSessionQueue {
GENERATED_BODY()

    /**
    *  <p>Descriptive label that is associated with game session queue. Queue names must be unique within each region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Amazon Resource Name (<a href="https://docs.aws.amazon.com/AmazonS3/latest/dev/s3-arn-format.html">ARN</a>) that is assigned to a game session queue and uniquely identifies it. Format is <code>arn:aws:gamelift:&lt;region&gt;:&lt;aws account&gt;:gamesessionqueue/&lt;queue name&gt;</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionQueueArn;

    /**
    *  <p>Maximum time, in seconds, that a new game session placement request remains in the queue. When a request exceeds this time, the game session placement changes to a <code>TIMED_OUT</code> status.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int timeoutInSeconds;

    /**
    *  <p>Collection of latency policies to apply when processing game sessions placement requests with player latency information. Multiple policies are evaluated in order of the maximum latency value, starting with the lowest latency values. With just one policy, it is enforced at the start of the game session placement for the duration period. With multiple policies, each policy is enforced consecutively for its duration period. For example, a queue might enforce a 60-second policy followed by a 120-second policy, and then no policy for the remainder of the placement. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FPlayerLatencyPolicy> playerLatencyPolicies;

    /**
    *  <p>List of fleets that can be used to fulfill game session placement requests in the queue. Fleets are identified by either a fleet ARN or a fleet alias ARN. Destinations are listed in default preference order.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FGameSessionQueueDestination> destinations;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FGameSessionQueue &fromAWS(const Aws::GameLift::Model::GameSessionQueue &awsGameSessionQueue) {
        this->name = awsGameSessionQueue.GetName().c_str();

        this->gameSessionQueueArn = awsGameSessionQueue.GetGameSessionQueueArn().c_str();

        this->timeoutInSeconds = awsGameSessionQueue.GetTimeoutInSeconds();

        this->playerLatencyPolicies.Empty();
        for (const Aws::GameLift::Model::PlayerLatencyPolicy& elem : awsGameSessionQueue.GetPlayerLatencyPolicies()) {
            this->playerLatencyPolicies.Add(FPlayerLatencyPolicy().fromAWS(elem));
        }

        this->destinations.Empty();
        for (const Aws::GameLift::Model::GameSessionQueueDestination& elem : awsGameSessionQueue.GetDestinations()) {
            this->destinations.Add(FGameSessionQueueDestination().fromAWS(elem));
        }

        return *this;
    }
#endif
};
