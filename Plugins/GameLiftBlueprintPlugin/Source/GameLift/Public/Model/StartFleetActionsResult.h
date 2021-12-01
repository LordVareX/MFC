/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/StartFleetActionsResult.h"

#endif


#include "StartFleetActionsResult.generated.h"

USTRUCT(BlueprintType)
struct FStartFleetActionsResult {
GENERATED_BODY()

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FStartFleetActionsResult &fromAWS(const Aws::GameLift::Model::StartFleetActionsResult &awsStartFleetActionsResult) {

        return *this;
    }
#endif
};
