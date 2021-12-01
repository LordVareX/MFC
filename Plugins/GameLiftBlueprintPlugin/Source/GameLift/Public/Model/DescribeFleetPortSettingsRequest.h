/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/DescribeFleetPortSettingsRequest.h"

#endif


#include "DescribeFleetPortSettingsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeFleetPortSettingsRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a fleet to retrieve port settings for.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::DescribeFleetPortSettingsRequest toAWS() const {
        Aws::GameLift::Model::DescribeFleetPortSettingsRequest awsDescribeFleetPortSettingsRequest;

        if (!(this->fleetId.IsEmpty())) {
            awsDescribeFleetPortSettingsRequest.SetFleetId(TCHAR_TO_UTF8(*this->fleetId));
        }

        return awsDescribeFleetPortSettingsRequest;
    }

    bool IsEmpty() const {
        return this->fleetId.IsEmpty();
    }
#endif
};
