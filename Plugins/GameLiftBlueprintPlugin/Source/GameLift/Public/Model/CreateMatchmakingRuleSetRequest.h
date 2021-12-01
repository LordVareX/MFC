/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE

#include "aws/gamelift/model/CreateMatchmakingRuleSetRequest.h"

#endif


#include "CreateMatchmakingRuleSetRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateMatchmakingRuleSetRequest {
GENERATED_BODY()

    /**
    *  <p>Unique identifier for a matchmaking rule set. A matchmaking configuration identifies the rule set it uses by this name value. (Note: The rule set name is different from the optional "name" field in the rule set body.) </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString name;

    /**
    *  <p>Collection of matchmaking rules, formatted as a JSON string. Comments are not allowed in JSON, but most elements support a description field.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
    FString ruleSetBody;

#if WITH_GAMELIFTCLIENTSDK && WITH_CORE
public:
    Aws::GameLift::Model::CreateMatchmakingRuleSetRequest toAWS() const {
        Aws::GameLift::Model::CreateMatchmakingRuleSetRequest awsCreateMatchmakingRuleSetRequest;

        if (!(this->name.IsEmpty())) {
            awsCreateMatchmakingRuleSetRequest.SetName(TCHAR_TO_UTF8(*this->name));
        }

        if (!(this->ruleSetBody.IsEmpty())) {
            awsCreateMatchmakingRuleSetRequest.SetRuleSetBody(TCHAR_TO_UTF8(*this->ruleSetBody));
        }

        return awsCreateMatchmakingRuleSetRequest;
    }

    bool IsEmpty() const {
        return this->name.IsEmpty() && this->ruleSetBody.IsEmpty();
    }
#endif
};
