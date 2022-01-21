/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/UpdateFleetCapacityRequest.h"

#endif


#include "UpdateFleetCapacityRequest.generated.h"

USTRUCT(BlueprintType)
struct FUpdateFleetCapacityRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet to update capacity for.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

    /**
    *  <p>Number of EC2 instances you want this fleet to host.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int desiredInstances;

    /**
    *  <p>Minimum value allowed for the fleet's instance count. Default if not set is 0.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int minSize;

    /**
    *  <p>Maximum value allowed for the fleet's instance count. Default if not set is 1.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    int maxSize;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::UpdateFleetCapacityRequest toAWS() const {
        Aws::GameLift::Model::UpdateFleetCapacityRequest awsUpdateFleetCapacityRequest;

        if (!(this->fleetId.IsEmpty())) {
            awsUpdateFleetCapacityRequest.SetFleetId(TCHAR_TO_UTF8(*this->fleetId));
        }

        if (this->desiredInstances != 0) {
            awsUpdateFleetCapacityRequest.SetDesiredInstances(this->desiredInstances);
        }

        if (this->minSize != 0) {
            awsUpdateFleetCapacityRequest.SetMinSize(this->minSize);
        }

        if (this->maxSize != 0) {
            awsUpdateFleetCapacityRequest.SetMaxSize(this->maxSize);
        }

        return awsUpdateFleetCapacityRequest;
    }

    bool IsEmpty() const {
        return this->fleetId.IsEmpty() && this->desiredInstances == 0 && this->minSize == 0 && this->maxSize == 0;
    }
#endif
};
