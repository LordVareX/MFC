/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

#include "ServerHelper.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

void UServerHelper::ServerIPAndPort(UObject * WorldContextObject, FString &ip, int &port) {
    UWorld *world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
    if (world->IsServer()) {
        ip = world->URL.Host;
        port = world->URL.Port;
    }
    return;
}

void UServerHelper::QuitServer(bool force)
{
	FGenericPlatformMisc::RequestExit(force);
}
