/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/CreateMatchmakingConfigurationRequest.h"

#endif

#include "Model/GameProperty.h"
#include "Model/BackfillMode.h"

#include "CreateMatchmakingConfigurationRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateMatchmakingConfigurationRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a matchmaking configuration. This name is used to identify the configuration associated with a matchmaking request or ticket.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Meaningful description of the matchmaking configuration. </p>
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
    *  <p>Information to be added to all events related to this matchmaking configuration. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString customEventData;

    /**
    *  <p>Set of custom properties for a game session, formatted as key:value pairs. These properties are passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>). This information is added to the new <a>GameSession</a> object that is created for a successful match. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FGameProperty> gameProperties;

    /**
    *  <p>Set of custom game session properties, formatted as a single string value. This data is passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>). This information is added to the new <a>GameSession</a> object that is created for a successful match.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionData;

    /**
    *  <p>Method used to backfill game sessions created with this matchmaking configuration. Specify MANUAL when your game manages backfill requests manually or does not use the match backfill feature. Specify AUTOMATIC to have GameLift create a <a>StartMatchBackfill</a> request whenever a game session has one or more open slots. Learn more about manual and automatic backfill in <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-backfill.html"> Backfill Existing Games with FlexMatch</a>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EBackfillMode backfillMode;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::CreateMatchmakingConfigurationRequest toAWS() const {
        Aws::GameLift::Model::CreateMatchmakingConfigurationRequest awsCreateMatchmakingConfigurationRequest;

        if (!(this->name.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetName(TCHAR_TO_UTF8(*this->name));
        }

        if (!(this->description.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetDescription(TCHAR_TO_UTF8(*this->description));
        }

        for (const FString& elem : this->gameSessionQueueArns) {
            awsCreateMatchmakingConfigurationRequest.AddGameSessionQueueArns(TCHAR_TO_UTF8(*elem));
        }

        if (this->requestTimeoutSeconds != 0) {
            awsCreateMatchmakingConfigurationRequest.SetRequestTimeoutSeconds(this->requestTimeoutSeconds);
        }

        if (this->acceptanceTimeoutSeconds != 0) {
            awsCreateMatchmakingConfigurationRequest.SetAcceptanceTimeoutSeconds(this->acceptanceTimeoutSeconds);
        }

        awsCreateMatchmakingConfigurationRequest.SetAcceptanceRequired(this->acceptanceRequired);

        if (!(this->ruleSetName.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetRuleSetName(TCHAR_TO_UTF8(*this->ruleSetName));
        }

        if (!(this->notificationTarget.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetNotificationTarget(TCHAR_TO_UTF8(*this->notificationTarget));
        }

        if (this->additionalPlayerCount != 0) {
            awsCreateMatchmakingConfigurationRequest.SetAdditionalPlayerCount(this->additionalPlayerCount);
        }

        if (!(this->customEventData.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetCustomEventData(TCHAR_TO_UTF8(*this->customEventData));
        }

        for (const FGameProperty& elem : this->gameProperties) {
            awsCreateMatchmakingConfigurationRequest.AddGameProperties(elem.toAWS());
        }

        if (!(this->gameSessionData.IsEmpty())) {
            awsCreateMatchmakingConfigurationRequest.SetGameSessionData(TCHAR_TO_UTF8(*this->gameSessionData));
        }

        switch(this->backfillMode) {
            case EBackfillMode::NOT_SET:
                awsCreateMatchmakingConfigurationRequest.SetBackfillMode(Aws::GameLift::Model::BackfillMode::NOT_SET);
                break;
            case EBackfillMode::AUTOMATIC:
                awsCreateMatchmakingConfigurationRequest.SetBackfillMode(Aws::GameLift::Model::BackfillMode::AUTOMATIC);
                break;
            case EBackfillMode::MANUAL:
                awsCreateMatchmakingConfigurationRequest.SetBackfillMode(Aws::GameLift::Model::BackfillMode::MANUAL);
                break;
            default:
                awsCreateMatchmakingConfigurationRequest.SetBackfillMode(Aws::GameLift::Model::BackfillMode::NOT_SET);
                break;
        }

        return awsCreateMatchmakingConfigurationRequest;
    }

    bool IsEmpty() const {
        return this->name.IsEmpty() && this->description.IsEmpty() && this->gameSessionQueueArns.Num() == 0 && this->requestTimeoutSeconds == 0 && this->acceptanceTimeoutSeconds == 0 && false && this->ruleSetName.IsEmpty() && this->notificationTarget.IsEmpty() && this->additionalPlayerCount == 0 && this->customEventData.IsEmpty() && this->gameProperties.Num() == 0 && this->gameSessionData.IsEmpty() && this->backfillMode == EBackfillMode::NOT_SET;
    }
#endif
};
