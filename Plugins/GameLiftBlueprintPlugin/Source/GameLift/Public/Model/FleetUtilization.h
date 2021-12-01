/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/FleetUtilization.h"

#endif


#include "FleetUtilization.generated.h"

USTRUCT(BlueprintType)
struct FFleetUtilization {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

    /**
    *  <p>Number of server processes in an <code>ACTIVE</code> status currently running across all instances in the fleet</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int activeServerProcessCount;

    /**
    *  <p>Number of active game sessions currently being hosted on all instances in the fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int activeGameSessionCount;

    /**
    *  <p>Number of active player sessions currently being hosted on all instances in the fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int currentPlayerSessionCount;

    /**
    *  <p>Maximum players allowed across all game sessions currently being hosted on all instances in the fleet.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int maximumPlayerSessionCount;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FFleetUtilization &fromAWS(const Aws::GameLift::Model::FleetUtilization &awsFleetUtilization) {
        this->fleetId = awsFleetUtilization.GetFleetId().c_str();

        this->activeServerProcessCount = awsFleetUtilization.GetActiveServerProcessCount();

        this->activeGameSessionCount = awsFleetUtilization.GetActiveGameSessionCount();

        this->currentPlayerSessionCount = awsFleetUtilization.GetCurrentPlayerSessionCount();

        this->maximumPlayerSessionCount = awsFleetUtilization.GetMaximumPlayerSessionCount();

        return *this;
    }
#endif
};
