/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#include "ExplicitAuthFlowsType.generated.h"

UENUM(BlueprintType)
enum class EExplicitAuthFlowsType : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    ADMIN_NO_SRP_AUTH        UMETA(DisplayName = "admin no srp auth"),
    CUSTOM_AUTH_FLOW_ONLY        UMETA(DisplayName = "custom auth flow only"),
    USER_PASSWORD_AUTH        UMETA(DisplayName = "user password auth")
};
