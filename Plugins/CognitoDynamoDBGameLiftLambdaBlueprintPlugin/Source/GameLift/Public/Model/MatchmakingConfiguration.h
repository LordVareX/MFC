/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/MatchmakingConfiguration.h"

#endif

#include "Model/GameProperty.h"
#include "Model/BackfillMode.h"

#include "MatchmakingConfiguration.generated.h"

USTRUCT(BlueprintType)
struct FMatchmakingConfiguration {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a matchmaking configuration. This name is used to identify the configuration associated with a matchmaking request or ticket.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Descriptive label that is associated with matchmaking configuration.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString description;

    /**
    *  <p>Amazon Resource Name (<a href="https://docs.aws.amazon.com/AmazonS3/latest/dev/s3-arn-format.html">ARN</a>) that is assigned to a game session queue and uniquely identifies it. Format is <code>arn:aws:gamelift:&lt;region&gt;:&lt;aws account&gt;:gamesessionqueue/&lt;queue name&gt;</code>. These queues are used when placing game sessions for matches that are created with this matchmaking configuration. Queues can be located in any region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FString> gameSessionQueueArns;

    /**
    *  <p>Maximum duration, in seconds, that a matchmaking ticket can remain in process before timing out. Requests that fail due to timing out can be resubmitted as needed.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int requestTimeoutSeconds;

    /**
    *  <p>Length of time (in seconds) to wait for players to accept a proposed match. If any player rejects the match or fails to accept before the timeout, the ticket continues to look for an acceptable match.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int acceptanceTimeoutSeconds;

    /**
    *  <p>Flag that determines whether a match that was created with this configuration must be accepted by the matched players. To require acceptance, set to TRUE.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    bool acceptanceRequired;

    /**
    *  <p>Unique identifier for a matchmaking rule set to use with this configuration. A matchmaking configuration can only use rule sets that are defined in the same region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString ruleSetName;

    /**
    *  <p>SNS topic ARN that is set up to receive matchmaking notifications.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString notificationTarget;

    /**
    *  <p>Number of player slots in a match to keep open for future players. For example, if the configuration's rule set specifies a match for a single 12-person team, and the additional player count is set to 2, only 10 players are selected for the match.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int additionalPlayerCount;

    /**
    *  <p>Information to attach to all events related to the matchmaking configuration. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString customEventData;

    /**
    *  <p>Time stamp indicating when this data object was created. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime creationTime;

    /**
    *  <p>Set of custom properties for a game session, formatted as key:value pairs. These properties are passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>). This information is added to the new <a>GameSession</a> object that is created for a successful match. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FGameProperty> gameProperties;

    /**
    *  <p>Set of custom game session properties, formatted as a single string value. This data is passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>). This information is added to the new <a>GameSession</a> object that is created for a successful match. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionData;

    /**
    *  <p>Method used to backfill game sessions created with this matchmaking configuration. MANUAL indicates that the game makes backfill requests or does not use the match backfill feature. AUTOMATIC indicates that GameLift creates <a>StartMatchBackfill</a> requests whenever a game session has one or more open slots. Learn more about manual and automatic backfill in <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-backfill.html">Backfill Existing Games with FlexMatch</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EBackfillMode backfillMode;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FMatchmakingConfiguration &fromAWS(const Aws::GameLift::Model::MatchmakingConfiguration &awsMatchmakingConfiguration) {
        this->name = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetName().c_str());

        this->description = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetDescription().c_str());

        this->gameSessionQueueArns.Empty();
        for (const Aws::String& elem : awsMatchmakingConfiguration.GetGameSessionQueueArns()) {
            this->gameSessionQueueArns.Add(elem.c_str());
        }

        this->requestTimeoutSeconds = awsMatchmakingConfiguration.GetRequestTimeoutSeconds();

        this->acceptanceTimeoutSeconds = awsMatchmakingConfiguration.GetAcceptanceTimeoutSeconds();

        this->acceptanceRequired = awsMatchmakingConfiguration.GetAcceptanceRequired();

        this->ruleSetName = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetRuleSetName().c_str());

        this->notificationTarget = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetNotificationTarget().c_str());

        this->additionalPlayerCount = awsMatchmakingConfiguration.GetAdditionalPlayerCount();

        this->customEventData = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetCustomEventData().c_str());

        this->creationTime = FDateTime::FromUnixTimestamp(awsMatchmakingConfiguration.GetCreationTime().Millis());

        this->gameProperties.Empty();
        for (const Aws::GameLift::Model::GameProperty& elem : awsMatchmakingConfiguration.GetGameProperties()) {
            this->gameProperties.Add(FGameProperty().fromAWS(elem));
        }

        this->gameSessionData = UTF8_TO_TCHAR(awsMatchmakingConfiguration.GetGameSessionData().c_str());

        switch(awsMatchmakingConfiguration.GetBackfillMode()) {
            case Aws::GameLift::Model::BackfillMode::NOT_SET:
                this->backfillMode = EBackfillMode::NOT_SET;
                break;
            case Aws::GameLift::Model::BackfillMode::AUTOMATIC:
                this->backfillMode = EBackfillMode::AUTOMATIC;
                break;
            case Aws::GameLift::Model::BackfillMode::MANUAL:
                this->backfillMode = EBackfillMode::MANUAL;
                break;
            default:
                this->backfillMode = EBackfillMode::NOT_SET;
                break;
        }

        return *this;
    }
#endif
};
