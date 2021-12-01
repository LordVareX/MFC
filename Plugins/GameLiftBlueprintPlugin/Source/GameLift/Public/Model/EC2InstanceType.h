/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2019
*/

#pragma once

#include "CoreMinimal.h"

#include "EC2InstanceType.generated.h"

UENUM(BlueprintType)
enum class EEC2InstanceType : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    t2_micro        UMETA(DisplayName = "t2 micro"),
    t2_small        UMETA(DisplayName = "t2 small"),
    t2_medium        UMETA(DisplayName = "t2 medium"),
    t2_large        UMETA(DisplayName = "t2 large"),
    c3_large        UMETA(DisplayName = "c3 large"),
    c3_xlarge        UMETA(DisplayName = "c3 xlarge"),
    c3_2xlarge        UMETA(DisplayName = "c3 2xlarge"),
    c3_4xlarge        UMETA(DisplayName = "c3 4xlarge"),
    c3_8xlarge        UMETA(DisplayName = "c3 8xlarge"),
    c4_large        UMETA(DisplayName = "c4 large"),
    c4_xlarge        UMETA(DisplayName = "c4 xlarge"),
    c4_2xlarge        UMETA(DisplayName = "c4 2xlarge"),
    c4_4xlarge        UMETA(DisplayName = "c4 4xlarge"),
    c4_8xlarge        UMETA(DisplayName = "c4 8xlarge"),
    r3_large        UMETA(DisplayName = "r3 large"),
    r3_xlarge        UMETA(DisplayName = "r3 xlarge"),
    r3_2xlarge        UMETA(DisplayName = "r3 2xlarge"),
    r3_4xlarge        UMETA(DisplayName = "r3 4xlarge"),
    r3_8xlarge        UMETA(DisplayName = "r3 8xlarge"),
    r4_large        UMETA(DisplayName = "r4 large"),
    r4_xlarge        UMETA(DisplayName = "r4 xlarge"),
    r4_2xlarge        UMETA(DisplayName = "r4 2xlarge"),
    r4_4xlarge        UMETA(DisplayName = "r4 4xlarge"),
    r4_8xlarge        UMETA(DisplayName = "r4 8xlarge"),
    r4_16xlarge        UMETA(DisplayName = "r4 16xlarge"),
    m3_medium        UMETA(DisplayName = "m3 medium"),
    m3_large        UMETA(DisplayName = "m3 large"),
    m3_xlarge        UMETA(DisplayName = "m3 xlarge"),
    m3_2xlarge        UMETA(DisplayName = "m3 2xlarge"),
    m4_large        UMETA(DisplayName = "m4 large"),
    m4_xlarge        UMETA(DisplayName = "m4 xlarge"),
    m4_2xlarge        UMETA(DisplayName = "m4 2xlarge"),
    m4_4xlarge        UMETA(DisplayName = "m4 4xlarge"),
    m4_10xlarge        UMETA(DisplayName = "m4 10xlarge")
};
