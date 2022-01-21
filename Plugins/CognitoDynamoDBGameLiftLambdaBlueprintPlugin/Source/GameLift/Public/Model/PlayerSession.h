/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/PlayerSession.h"

#endif

#include "Model/PlayerSessionStatus.h"

#include "PlayerSession.generated.h"

USTRUCT(BlueprintType)
struct FAWSPlayerSession {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a player session.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString playerSessionId;

    /**
    *  <p>Unique identifier for a player that is associated with this player session.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString playerId;

    /**
    *  <p>Unique identifier for the game session that the player session is connected to.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString gameSessionId;

    /**
    *  <p>Unique identifier for a fleet that the player's game session is running on.</p>
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
    *  <p>Current status of the player session.</p> <p>Possible player session statuses include the following:</p> <ul> <li> <p> <b>RESERVED</b> -- The player session request has been received, but the player has not yet connected to the server process and/or been validated. </p> </li> <li> <p> <b>ACTIVE</b> -- The player has been validated by the server process and is currently connected.</p> </li> <li> <p> <b>COMPLETED</b> -- The player connection has been dropped.</p> </li> <li> <p> <b>TIMEDOUT</b> -- A player session request was received, but the player did not connect and/or was not validated within the timeout limit (60 seconds).</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    EPlayerSessionStatus status;

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
    *  <p>Port number for the game session. To connect to a Amazon GameLift server process, an app needs both the IP address and port number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int port;

    /**
    *  <p>Developer-defined information related to a player. Amazon GameLift does not use this data, so it can be formatted as needed for use in the game. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString playerData;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FAWSPlayerSession &fromAWS(const Aws::GameLift::Model::PlayerSession &awsPlayerSession) {
        this->playerSessionId = UTF8_TO_TCHAR(awsPlayerSession.GetPlayerSessionId().c_str());

        this->playerId = UTF8_TO_TCHAR(awsPlayerSession.GetPlayerId().c_str());

        this->gameSessionId = UTF8_TO_TCHAR(awsPlayerSession.GetGameSessionId().c_str());

        this->fleetId = UTF8_TO_TCHAR(awsPlayerSession.GetFleetId().c_str());

        this->creationTime = FDateTime::FromUnixTimestamp(awsPlayerSession.GetCreationTime().Millis());

        this->terminationTime = FDateTime::FromUnixTimestamp(awsPlayerSession.GetTerminationTime().Millis());

        switch(awsPlayerSession.GetStatus()) {
            case Aws::GameLift::Model::PlayerSessionStatus::NOT_SET:
                this->status = EPlayerSessionStatus::NOT_SET;
                break;
            case Aws::GameLift::Model::PlayerSessionStatus::RESERVED:
                this->status = EPlayerSessionStatus::RESERVED;
                break;
            case Aws::GameLift::Model::PlayerSessionStatus::ACTIVE:
                this->status = EPlayerSessionStatus::ACTIVE;
                break;
            case Aws::GameLift::Model::PlayerSessionStatus::COMPLETED:
                this->status = EPlayerSessionStatus::COMPLETED;
                break;
            case Aws::GameLift::Model::PlayerSessionStatus::TIMEDOUT:
                this->status = EPlayerSessionStatus::TIMEDOUT;
                break;
            default:
                this->status = EPlayerSessionStatus::NOT_SET;
                break;
        }

        this->ipAddress = UTF8_TO_TCHAR(awsPlayerSession.GetIpAddress().c_str());

        this->dnsName = UTF8_TO_TCHAR(awsPlayerSession.GetDnsName().c_str());

        this->port = awsPlayerSession.GetPort();

        this->playerData = UTF8_TO_TCHAR(awsPlayerSession.GetPlayerData().c_str());

        return *this;
    }
#endif
};
