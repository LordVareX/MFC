/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/GameSession.h"

#endif

#include "Model/GameSessionStatus.h"
#include "Model/GameSessionStatusReason.h"
#include "Model/GameProperty.h"
#include "Model/PlayerSessionCreationPolicy.h"

#include "AWSGameSession.generated.h"

USTRUCT(BlueprintType)
struct FAWSGameSession {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for the game session. A game session ARN has the following format: <code>arn:aws:gamelift:&lt;region&gt;::gamesession/&lt;fleet ID&gt;/&lt;custom ID string or idempotency token&gt;</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionId;

    /**
    *  <p>Descriptive label that is associated with a game session. Session names do not need to be unique.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Unique identifier for a fleet that the game session is running on.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

    /**
    *  <p>Time stamp indicating when this data object was created. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime creationTime;

    /**
    *  <p>Time stamp indicating when this data object was terminated. Format is a number expressed in Unix time as milliseconds (for example "1469498468.057").</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FDateTime terminationTime;

    /**
    *  <p>Number of players currently in the game session.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int currentPlayerSessionCount;

    /**
    *  <p>Maximum number of players that can be connected simultaneously to the game session.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int maximumPlayerSessionCount;

    /**
    *  <p>Current status of the game session. A game session must have an <code>ACTIVE</code> status to have player sessions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EGameSessionStatus status;

    /**
    *  <p>Provides additional information about game session status. <code>INTERRUPTED</code> indicates that the game session was hosted on a spot instance that was reclaimed, causing the active game session to be terminated.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EGameSessionStatusReason statusReason;

    /**
    *  <p>Set of custom properties for a game session, formatted as key:value pairs. These properties are passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>). You can search for active game sessions based on this custom data with <a>SearchGameSessions</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FGameProperty> gameProperties;

    /**
    *  <p>IP address of the game session. To connect to a Amazon GameLift game server, an app needs both the IP address and port number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString ipAddress;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString dnsName;

    /**
    *  <p>Port number for the game session. To connect to a Amazon GameLift game server, an app needs both the IP address and port number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int port;

    /**
    *  <p>Indicates whether or not the game session is accepting new players.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EPlayerSessionCreationPolicy playerSessionCreationPolicy;

    /**
    *  <p>Unique identifier for a player. This ID is used to enforce a resource protection policy (if one exists), that limits the number of game sessions a player can create.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString creatorId;

    /**
    *  <p>Set of custom game session properties, formatted as a single string value. This data is passed to a game server process in the <a>GameSession</a> object with a request to start a new game session (see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/gamelift-sdk-server-api.html#gamelift-sdk-server-startsession">Start a Game Session</a>).</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionData;

    /**
    *  <p>Information about the matchmaking process that was used to create the game session. It is in JSON syntax, formatted as a string. In addition the matchmaking configuration used, it contains data on all players assigned to the match, including player attributes and team assignments. For more details on matchmaker data, see <a href="https://docs.aws.amazon.com/gamelift/latest/developerguide/match-server.html#match-server-data">Match Data</a>. Matchmaker data is useful when requesting match backfills, and is updated whenever new players are added during a successful backfill (see <a>StartMatchBackfill</a>). </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString matchmakerData;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FAWSGameSession &fromAWS(const Aws::GameLift::Model::GameSession &awsGameSession) {
        this->gameSessionId = UTF8_TO_TCHAR(awsGameSession.GetGameSessionId().c_str());

        this->name = UTF8_TO_TCHAR(awsGameSession.GetName().c_str());

        this->fleetId = UTF8_TO_TCHAR(awsGameSession.GetFleetId().c_str());

        this->creationTime = FDateTime::FromUnixTimestamp(awsGameSession.GetCreationTime().Millis());

        this->terminationTime = FDateTime::FromUnixTimestamp(awsGameSession.GetTerminationTime().Millis());

        this->currentPlayerSessionCount = awsGameSession.GetCurrentPlayerSessionCount();

        this->maximumPlayerSessionCount = awsGameSession.GetMaximumPlayerSessionCount();

        switch(awsGameSession.GetStatus()) {
            case Aws::GameLift::Model::GameSessionStatus::NOT_SET:
                this->status = EGameSessionStatus::NOT_SET;
                break;
            case Aws::GameLift::Model::GameSessionStatus::ACTIVE:
                this->status = EGameSessionStatus::ACTIVE;
                break;
            case Aws::GameLift::Model::GameSessionStatus::ACTIVATING:
                this->status = EGameSessionStatus::ACTIVATING;
                break;
            case Aws::GameLift::Model::GameSessionStatus::TERMINATED:
                this->status = EGameSessionStatus::TERMINATED;
                break;
            case Aws::GameLift::Model::GameSessionStatus::TERMINATING:
                this->status = EGameSessionStatus::TERMINATING;
                break;
            case Aws::GameLift::Model::GameSessionStatus::ERROR_:
                this->status = EGameSessionStatus::ERROR_;
                break;
            default:
                this->status = EGameSessionStatus::NOT_SET;
                break;
        }

        switch(awsGameSession.GetStatusReason()) {
            case Aws::GameLift::Model::GameSessionStatusReason::NOT_SET:
                this->statusReason = EGameSessionStatusReason::NOT_SET;
                break;
            case Aws::GameLift::Model::GameSessionStatusReason::INTERRUPTED:
                this->statusReason = EGameSessionStatusReason::INTERRUPTED;
                break;
            default:
                this->statusReason = EGameSessionStatusReason::NOT_SET;
                break;
        }

        this->gameProperties.Empty();
        for (const Aws::GameLift::Model::GameProperty& elem : awsGameSession.GetGameProperties()) {
            this->gameProperties.Add(FGameProperty().fromAWS(elem));
        }

        this->ipAddress = UTF8_TO_TCHAR(awsGameSession.GetIpAddress().c_str());

        this->dnsName = UTF8_TO_TCHAR(awsGameSession.GetDnsName().c_str());

        this->port = awsGameSession.GetPort();

        switch(awsGameSession.GetPlayerSessionCreationPolicy()) {
            case Aws::GameLift::Model::PlayerSessionCreationPolicy::NOT_SET:
                this->playerSessionCreationPolicy = EPlayerSessionCreationPolicy::NOT_SET;
                break;
            case Aws::GameLift::Model::PlayerSessionCreationPolicy::ACCEPT_ALL:
                this->playerSessionCreationPolicy = EPlayerSessionCreationPolicy::ACCEPT_ALL;
                break;
            case Aws::GameLift::Model::PlayerSessionCreationPolicy::DENY_ALL:
                this->playerSessionCreationPolicy = EPlayerSessionCreationPolicy::DENY_ALL;
                break;
            default:
                this->playerSessionCreationPolicy = EPlayerSessionCreationPolicy::NOT_SET;
                break;
        }

        this->creatorId = UTF8_TO_TCHAR(awsGameSession.GetCreatorId().c_str());

        this->gameSessionData = UTF8_TO_TCHAR(awsGameSession.GetGameSessionData().c_str());

        this->matchmakerData = UTF8_TO_TCHAR(awsGameSession.GetMatchmakerData().c_str());

        return *this;
    }
#endif
};
