// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordPresenceManager.h"

#include "DiscordTypes.h"
#include "DiscordGameInstanceSubsystem.h"

#include "Containers/UnrealString.h"
#include "Misc/ConfigCacheIni.h"

FDiscordPresenceManager::FDiscordPresenceManager(UDiscordGameInstanceSubsystem* InDiscordGameInstanceSubsystem)
	: DiscordGameInstanceSubsystemPtr(InDiscordGameInstanceSubsystem)
{
	// Create initial, default activity
	bool bSetupDefaultActivity = false;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bEnableDefaultActivity"), bSetupDefaultActivity, GetIniName());
	if (bSetupDefaultActivity)
	{
		UE_LOG(DiscordLog, Log, TEXT("FDiscordPresenceManager::Setup Setting up discord presence!"));
		
		SetupInitialPresence();
	}
}

void FDiscordPresenceManager::SetupInitialPresence()
{
	FString State = "";
	GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("State"), State, GetIniName());
	SetState(State);

	FString Details = "";
	GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("Details"), Details, GetIniName());
	SetDetails(Details);

	bool bSetStartingTime = true;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bSetStartTime"), bSetStartingTime, GetIniName());
	if (bSetStartingTime)
	{
		SetTimeDuration(FDateTime::UtcNow().ToUnixTimestamp());
	}

	bool bSetLargeImage = false;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bEnableLargeImage"), bSetLargeImage, GetIniName());
	if (bSetLargeImage)
	{
		FString LargeImageKey = "";
		GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("LargeImage"), LargeImageKey, GetIniName());

		FString LargeImageText = "";
		GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("LargeImageText"), LargeImageText, GetIniName());

		SetLargeImage(LargeImageKey, LargeImageText);
	}

	bool bSetSmallImage = false;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bEnableSmallImage"), bSetSmallImage, GetIniName());
	if (bSetSmallImage)
	{
		FString SmallImageKey = "";
		GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("SmallImage"), SmallImageKey, GetIniName());

		FString SmallImageText = "";
		GConfig->GetString(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("SmallImageText"), SmallImageText, GetIniName());

		SetSmallImage(SmallImageKey, SmallImageText);
	}

	bool bSetInitialParty = false;
	GConfig->GetBool(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("bEnableInitialParty"), bSetInitialParty, GetIniName());
	if (bSetInitialParty && State.Len() > 0)
	{
		int32 InitialPartySize = 1;
		GConfig->GetInt(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("InitialPartySize"), InitialPartySize, GetIniName());
		CachedActivity.GetParty().GetSize().SetCurrentSize(InitialPartySize); // Current amount of people in party

		int32 MaxPartySize = 4;
		GConfig->GetInt(TEXT("/Script/DiscordRichIntegration.DiscordRichIntegrationProjectSettings"), TEXT("MaxPartySize"), MaxPartySize, GetIniName());

		SetParty("", InitialPartySize, MaxPartySize);
	}

	Update();
}


void FDiscordPresenceManager::Update()
{	
	if(DiscordGameInstanceSubsystemPtr && DiscordGameInstanceSubsystemPtr->GetDiscordCore())
	{
		// Update activity if it has changed
		if (bActivityDirty)
		{
			// Check if the time between now and the previous update is within Discord's rate limit
			const time_t CurrentTime = time(nullptr);
			const int BetweenRateLimitTime = 4; // Rate limit of 5 messages every 20 sec, so: 20 / 5
			if (CurrentTime - PreviousActivityUpdateTime >= BetweenRateLimitTime)
			{
				UE_LOG(DiscordLog, Log, TEXT("FDiscordPresenceManager::Update!"));
				
				DiscordGameInstanceSubsystemPtr->GetDiscordCore()->ActivityManager().UpdateActivity(CachedActivity, [&](const discord::Result Result) {
					OnActivityUpdated.Broadcast(Result);
					UE_LOG(DiscordLog, Log, TEXT("FDiscordPresenceManager::Update UpdateActivity result %d"), Result);
				});
				
				time(&PreviousActivityUpdateTime);
				bActivityDirty = false;
			}
		}
	}
}

void FDiscordPresenceManager::SetState(const FString State)
{
	if(ANSI_TO_TCHAR(CachedActivity.GetState()) != State)
	{
		CachedActivity.SetState(TCHAR_TO_ANSI(*State)); // Player's Party Status
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetDetails(const FString Details)
{
	if(ANSI_TO_TCHAR(CachedActivity.GetDetails()) != Details)
	{
		CachedActivity.SetDetails(TCHAR_TO_ANSI(*Details)); // Player's Current Activity
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetLargeImage(const FString ImageKey, const FString ImageHoverText)
{
	if(ANSI_TO_TCHAR(CachedActivity.GetAssets().GetLargeImage()) != ImageKey)
	{
		CachedActivity.GetAssets().SetLargeImage(TCHAR_TO_ANSI(*ImageKey)); // Game logo
		bActivityDirty = true;
	}
	if(ANSI_TO_TCHAR(CachedActivity.GetAssets().GetLargeText()) != ImageHoverText)
	{
		CachedActivity.GetAssets().SetLargeText(TCHAR_TO_ANSI(*ImageHoverText)); // Text when hovering large image
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetSmallImage(const FString ImageKey, const FString ImageHoverText)
{
	if(ANSI_TO_TCHAR(CachedActivity.GetAssets().GetSmallImage()) != ImageKey)
	{
		CachedActivity.GetAssets().SetSmallImage(TCHAR_TO_ANSI(*ImageKey)); // Small logo at bottom right of large logo
		bActivityDirty = true;
	}
	if(ANSI_TO_TCHAR(CachedActivity.GetAssets().GetSmallText()) != ImageHoverText)
	{
		CachedActivity.GetAssets().SetSmallText(TCHAR_TO_ANSI(*ImageHoverText)); // Text when hovering small image
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetTimeDuration(const int64 Time, const bool IsStartTime)
{
	UE_LOG(DiscordLog, Log, TEXT("FDiscordPresenceManager::SetTimeDuration %lld"), Time);

	if (IsStartTime)
	{
		if(CachedActivity.GetTimestamps().GetStart() != Time)
		{
			CachedActivity.GetTimestamps().SetStart(Time); // Start time, with start it will show the play duration.
			bActivityDirty = true;
		}
	}
	else
	{
		if(CachedActivity.GetTimestamps().GetEnd() != Time)
		{
			CachedActivity.GetTimestamps().SetEnd(Time); // End time, with end it will show the time left.
			bActivityDirty = true;
		}
	}
}
void FDiscordPresenceManager::SetParty(const FString PartyID, const int32 CurrentPartySize, const int32 MaxPartySize)
{
	SetPartyIdentifier(PartyID);
	SetCurrentPartySize(CurrentPartySize);
	SetMaxPartySize(MaxPartySize);
}
void FDiscordPresenceManager::SetPartyIdentifier(const FString PartyID)
{
	if(ANSI_TO_TCHAR(CachedActivity.GetParty().GetId()) != PartyID)
	{
		CachedActivity.GetParty().SetId(TCHAR_TO_ANSI(*PartyID));
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetCurrentPartySize(const int32 CurrentPartySize)
{
	if(CachedActivity.GetParty().GetSize().GetCurrentSize() != CurrentPartySize)
	{
		CachedActivity.GetParty().GetSize().SetCurrentSize(CurrentPartySize); // Current amount of people in party
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetMaxPartySize(const int32 MaxPartySize)
{
	if(CachedActivity.GetParty().GetSize().GetMaxSize() != MaxPartySize)
	{
		CachedActivity.GetParty().GetSize().SetMaxSize(MaxPartySize); // Max amount of people in lobby
		bActivityDirty = true;
	}
}
void FDiscordPresenceManager::SetInstanced(const bool bIsInstanced)
{
	if(CachedActivity.GetInstance() != bIsInstanced)
	{
		CachedActivity.SetInstance(bIsInstanced); // If the user is currently in a instances context, like a match.
		bActivityDirty = true;
	}
}

void FDiscordPresenceManager::ClearActivity()
{
	CachedActivity = discord::Activity{};
	bActivityDirty = true;
}
void FDiscordPresenceManager::ClearPresence() const
{
	if(DiscordGameInstanceSubsystemPtr && DiscordGameInstanceSubsystemPtr->GetDiscordCore())
	{
		DiscordGameInstanceSubsystemPtr->GetDiscordCore()->ActivityManager().ClearActivity([&](const discord::Result Result) {
	        OnActivityCleared.Broadcast(Result);
	        UE_LOG(DiscordLog, Log, TEXT("UDiscordRPCBPLibrary::ClearDiscordActivity result %d"), Result);
	    });
	}
}
