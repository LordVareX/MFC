/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/DescribeFleetPortSettingsResult.h"

#endif

#include "Model/IpPermission.h"

#include "DescribeFleetPortSettingsResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeFleetPortSettingsResult {
GENERATED_BODY()

    /**
    *  <p>Object that contains port settings for the requested fleet ID.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    TArray<FIpPermission> inboundPermissions;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FDescribeFleetPortSettingsResult &fromAWS(const Aws::GameLift::Model::DescribeFleetPortSettingsResult &awsDescribeFleetPortSettingsResult) {
        this->inboundPermissions.Empty();
        for (const Aws::GameLift::Model::IpPermission& elem : awsDescribeFleetPortSettingsResult.GetInboundPermissions()) {
            this->inboundPermissions.Add(FIpPermission().fromAWS(elem));
        }

        return *this;
    }
#endif
};
