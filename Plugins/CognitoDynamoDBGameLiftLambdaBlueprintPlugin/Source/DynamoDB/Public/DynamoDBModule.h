/* Copyright (C) Siqi.Wu - All Rights Reserved

 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

#pragma once

#include "Modules/ModuleManager.h"

class FDynamoDBModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	static void* DynamoDBLibraryHandle;
	static bool LoadDependency(const FString& Dir, const FString& Name, void*& Handle);
	static void FreeDependency(void*& Handle);
};