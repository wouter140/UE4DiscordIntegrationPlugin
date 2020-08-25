// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordGameInstanceSubsystem.h"

#include "DiscordTypes.h"

#include "Containers/UnrealString.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/ConfigCacheIni.h"

// Log category
DEFINE_LOG_CATEGORY(DiscordLog);

UDiscordGameInstanceSubsystem::UDiscordGameInstanceSubsystem()
{
}

bool UDiscordGameInstanceSubsystem::Setup()
{
	UE_LOG(DiscordLog, Log, TEXT("FDiscordManager::Setup Setting up Discord GameSDK!"));
	
	// Check if config is not null
	if (!GConfig)
	{
		UE_LOG(DiscordLog, Error, TEXT("FDiscordPresenceManager::Setup GConfig was nullptr. Probably meaning you called setup too early during statup!"));
		return false;
	}
	
	bool bRequireDiscord = false;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bRequireDiscordRunning"), bRequireDiscord, GetIniName());
	
	// Get the Discord client id setting
	FString ClientID;
	if (!GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("ClientID"), ClientID, GetIniName()))
	{
		return false;
	}

	// Convert ClientID string to int64. For some reason int64 in settings is not correct when retrieved, that's why its a string.
	int64 Client = 0;
	LexFromString(Client, *ClientID);
	
	// Create the discord instance with the specified game clientID and flags
	const discord::Result Result = discord::Core::Create(Client, bRequireDiscord ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord, &DiscordCore);
	if (Result != discord::Result::Ok)
	{
		UE_LOG(DiscordLog, Error, TEXT("FDiscordPresenceManager::Setup discord::Core::Create did not successfully create the discord instance!"));
		return false;
	}

	// Set the log hook
	DiscordCore->SetLogHook(discord::LogLevel::Debug, std::bind(&UDiscordGameInstanceSubsystem::OnLogMessage, this, std::placeholders::_1, std::placeholders::_2));

	// Register this application to either a steam or url so it can be opened through discord later
	FString SteamAppID = "";
	GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("SteamAppID"), SteamAppID, GetIniName());
	if (SteamAppID.Len() > 0)
	{
		uint32 SteamAppIDNumber = 0;
		LexFromString(SteamAppIDNumber, *SteamAppID);
		DiscordCore->ActivityManager().RegisterSteam(SteamAppIDNumber);
	}
	else
	{
		FString ApplicationStartURL = "";
		GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("ApplicationStartUrl"), ApplicationStartURL, GetIniName());
		if (ApplicationStartURL.Len() > 0)
		{
			DiscordCore->ActivityManager().RegisterCommand(TCHAR_TO_ANSI(*ApplicationStartURL));
		}
	}

	return true;
}

void UDiscordGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    UE_LOG(LogTemp, Log, TEXT("UDiscordGameInstanceSubsystem::Initialize!"));
	
	//bCreatedWithGameRunning = GIsRunning;
	if(!GIsEditor)
	{
		// Setup the discord instance
		if(Setup())
		{
			DiscordPresencePtr = MakeShared<FDiscordPresenceManager>(this);
		}
	}
}

void UDiscordGameInstanceSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("UDiscordGameInstanceSubsystem::Deinitialize!"));

	// Allow one last update before destroying.
	Tick(0.0f);
}

void UDiscordGameInstanceSubsystem::Tick(float)
{	
	if (DiscordCore)
	{
		// Update activity
		if(DiscordPresencePtr)
		{
			DiscordPresencePtr->Update();
		}

		// Run the discord GameSDK callbacks. This is what actually interfaces between us and Discord.
		const discord::Result Result = DiscordCore->RunCallbacks();
		if (Result == discord::Result::NotRunning)
		{
			// Discord stopped running, stop updating presence.
			DiscordCore = nullptr;

			UE_LOG(DiscordLog, Warning, TEXT("FDiscordPresenceManager::Update Discord is no longer running, ending presence updating!"));
		}
	}
}

TStatId UDiscordGameInstanceSubsystem::GetStatId() const
{
    return Super::GetStatID();
}

void UDiscordGameInstanceSubsystem::OnLogMessage(const discord::LogLevel DiscordLogLevel, const char* Message)
{
	switch (DiscordLogLevel)
	{
		case discord::LogLevel::Error:
			UE_LOG(DiscordLog, Error, TEXT("FDiscordPresenceManager::OnLogMessage %s"), UTF8_TO_TCHAR(Message));
			break;
		case discord::LogLevel::Warn:
			UE_LOG(DiscordLog, Warning, TEXT("FDiscordPresenceManager::OnLogMessage %s"), UTF8_TO_TCHAR(Message));
			break;
		default:
		case discord::LogLevel::Info:
			UE_LOG(DiscordLog, Display, TEXT("FDiscordPresenceManager::OnLogMessage %s"), UTF8_TO_TCHAR(Message));
			break;
		case discord::LogLevel::Debug:
			UE_LOG(DiscordLog, Display, TEXT("FDiscordPresenceManager::OnLogMessage %s"), UTF8_TO_TCHAR(Message));
			break;
	}
}