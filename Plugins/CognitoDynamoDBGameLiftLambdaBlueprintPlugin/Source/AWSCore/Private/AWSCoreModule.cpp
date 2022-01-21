/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, May 2019
 */

#include "AWSCoreModule.h"
#include "AWSCoreModulePrivatePCH.h"
#include "AWSCoreGlobals.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformProcess.h"

#define LOCTEXT_NAMESPACE "FAWSCoreModule"

void* FAWSCoreModule::AWSCCommonLibraryHandle = nullptr;
void* FAWSCoreModule::AWSChecksumsLibraryHandle = nullptr;
void* FAWSCoreModule::AWSCEventStreamLibraryHandle = nullptr;
void* FAWSCoreModule::AWSCoreLibraryHandle = nullptr;

void FAWSCoreModule::StartupModule()
{
#if WITH_CORE
#if PLATFORM_WINDOWS && PLATFORM_64BITS
	LOG_AWSCORE_NORMAL("Starting AWSCore Module...");

	const FString BaseDir = IPluginManager::Get().FindPlugin("CognitoDynamoDBGameLiftLambdaSDK")->GetBaseDir();
	LOG_AWSCORE_NORMAL(FString::Printf(TEXT("Base directory is %s"), *BaseDir));

	const FString ThirdPartyDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AWSCoreLibrary"), TEXT("Win64"));
	LOG_AWSCORE_NORMAL(FString::Printf(TEXT("ThirdParty directory is %s"), *ThirdPartyDir));

	{
		static const FString CoreDLLName = "aws-c-common";
		const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCCommonLibraryHandle);
		if (bDependencyLoaded == false)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
			FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
			FreeDependency(AWSCCommonLibraryHandle);
			return;
		}
	}

	{
		static const FString CoreDLLName = "aws-checksums";
		const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSChecksumsLibraryHandle);
		if (bDependencyLoaded == false)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
			FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
			FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
			return;
		}
	}

	{
		static const FString CoreDLLName = "aws-c-event-stream";
		const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCEventStreamLibraryHandle);
		if (bDependencyLoaded == false)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
			FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
			FreeDependency(AWSCEventStreamLibraryHandle);
			FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
			return;
		}
	}

	{
		static const FString CoreDLLName = "aws-cpp-sdk-core";
		const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCoreLibraryHandle);
		if (bDependencyLoaded == false)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
			FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
			FreeDependency(AWSCoreLibraryHandle);
			FreeDependency(AWSCEventStreamLibraryHandle);
			FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
			return;
		}
	}
#elif PLATFORM_MAC
    LOG_AWSCORE_NORMAL("Starting AWSCore Module...");
    
    const FString BaseDir = IPluginManager::Get().FindPlugin("CognitoDynamoDBGameLiftLambdaSDK")->GetBaseDir();
    LOG_AWSCORE_NORMAL(FString::Printf(TEXT("Base directory is %s"), *BaseDir));
    
    const FString ThirdPartyDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AWSCoreLibrary"), TEXT("Mac"));
    LOG_AWSCORE_NORMAL(FString::Printf(TEXT("ThirdParty directory is %s"), *ThirdPartyDir));
    
    {
        static const FString CoreDLLName = "libaws-c-common";
        const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCCommonLibraryHandle);
        if (bDependencyLoaded == false)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
            FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
            FreeDependency(AWSCCommonLibraryHandle);
            return;
        }
    }
    
    {
        static const FString CoreDLLName = "libaws-checksums";
        const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSChecksumsLibraryHandle);
        if (bDependencyLoaded == false)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
            FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
            FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
            return;
        }
    }
    
    {
        static const FString CoreDLLName = "libaws-c-event-stream";
        const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCEventStreamLibraryHandle);
        if (bDependencyLoaded == false)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
            FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
            FreeDependency(AWSCEventStreamLibraryHandle);
			FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
            return;
        }
    }
    
    {
        static const FString CoreDLLName = "libaws-cpp-sdk-core";
        const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CoreDLLName, AWSCoreLibraryHandle);
        if (bDependencyLoaded == false)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("Name"), FText::FromString(CoreDLLName));
            FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}. Plugin will not be functional"), Arguments));
            FreeDependency(AWSCoreLibraryHandle);
			FreeDependency(AWSCEventStreamLibraryHandle);
			FreeDependency(AWSChecksumsLibraryHandle);
			FreeDependency(AWSCCommonLibraryHandle);
            return;
        }
    }
#elif PLATFORM_IOS
	LOG_AWSCORE_NORMAL("Starting AWSCore Module...");
#endif
	Aws::InitAPI(options);
	LOG_AWSCORE_NORMAL("Aws::InitAPI called.");
#endif
}

void FAWSCoreModule::ShutdownModule()
{
#if WITH_CORE
	Aws::ShutdownAPI(options);
	LOG_AWSCORE_NORMAL("Aws::ShutdownAPI called.");
#endif
	FreeDependency(AWSCoreLibraryHandle);
	FreeDependency(AWSCEventStreamLibraryHandle);
	FreeDependency(AWSChecksumsLibraryHandle);
	FreeDependency(AWSCCommonLibraryHandle);
	LOG_AWSCORE_NORMAL("Shutting down AWSCore Module...");
}

bool FAWSCoreModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{
		LOG_AWSCORE_ERROR(FString::Printf(TEXT("Dependency %s failed to load in directory %s"), *Lib, *Dir));
		return false;
	}

	LOG_AWSCORE_NORMAL(FString::Printf(TEXT("Dependency %s successfully loaded from directory %s"), *Lib, *Dir));
	return true;
}

void FAWSCoreModule::FreeDependency(void*& Handle)
{
#if !PLATFORM_LINUX && !PLATFORM_ANDROID && !PLATFORM_IOS
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAWSCoreModule, AWSCore);
