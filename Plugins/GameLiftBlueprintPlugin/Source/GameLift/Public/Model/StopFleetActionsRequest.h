/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/StopFleetActionsRequest.h"

#endif

#include "Model/FleetAction.h"

#include "StopFleetActionsRequest.generated.h"

USTRUCT(BlueprintType)
struct FStopFleetActionsRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

    /**
    *  <p>List of actions to suspend on the fleet. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<EFleetAction> actions;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::StopFleetActionsRequest toAWS() const {
        Aws::GameLift::Model::StopFleetActionsRequest awsStopFleetActionsRequest;

        if (!(this->fleetId.IsEmpty())) {
            awsStopFleetActionsRequest.SetFleetId(TCHAR_TO_UTF8(*this->fleetId));
        }

        for (const EFleetAction& elem : this->actions) {
            switch(elem) {
                case EFleetAction::NOT_SET:
                    awsStopFleetActionsRequest.AddActions(Aws::GameLift::Model::FleetAction::NOT_SET);
                    break;
                case EFleetAction::AUTO_SCALING:
                    awsStopFleetActionsRequest.AddActions(Aws::GameLift::Model::FleetAction::AUTO_SCALING);
                    break;
                default:
                    awsStopFleetActionsRequest.AddActions(Aws::GameLift::Model::FleetAction::NOT_SET);
                    break;
            };
        }

        return awsStopFleetActionsRequest;
    }

    bool IsEmpty() const {
        return this->fleetId.IsEmpty() && this->actions.Num() == 0;
    }
#endif
};
