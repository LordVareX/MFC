/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/StopFleetActionsResult.h"

#endif


#include "StopFleetActionsResult.generated.h"

USTRUCT(BlueprintType)
struct FStopFleetActionsResult {
GENERATED_BODY()

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FStopFleetActionsResult &fromAWS(const Aws::GameLift::Model::StopFleetActionsResult &awsStopFleetActionsResult) {

        return *this;
    }
#endif
};
