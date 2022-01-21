/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/UpdateFleetCapacityResult.h"

#endif


#include "UpdateFleetCapacityResult.generated.h"

USTRUCT(BlueprintType)
struct FUpdateFleetCapacityResult {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet that was updated.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FUpdateFleetCapacityResult &fromAWS(const Aws::GameLift::Model::UpdateFleetCapacityResult &awsUpdateFleetCapacityResult) {
        this->fleetId = UTF8_TO_TCHAR(awsUpdateFleetCapacityResult.GetFleetId().c_str());

        return *this;
    }
#endif
};
