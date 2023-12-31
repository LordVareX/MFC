/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/ResolveAliasResult.h"

#endif


#include "ResolveAliasResult.generated.h"

USTRUCT(BlueprintType)
struct FResolveAliasResult {
GENERATED_BODY()

    /**
    *  <p>Fleet identifier that is associated with the requested alias.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString fleetId;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    FResolveAliasResult &fromAWS(const Aws::GameLift::Model::ResolveAliasResult &awsResolveAliasResult) {
        this->fleetId = UTF8_TO_TCHAR(awsResolveAliasResult.GetFleetId().c_str());

        return *this;
    }
#endif
};
