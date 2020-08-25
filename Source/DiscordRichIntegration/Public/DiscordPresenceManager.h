// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <ctime>

#include "DiscordUser.h"

// Event callback for a discord callback, we get the passed discord result from the callback.
DECLARE_EVENT_OneParam(FDiscordPresenceManager, FDiscordResultCallback, discord::Result const&)

class UDiscordGameInstanceSubsystem;

/**
 * Manager class for Discord Presence related work
 */
class DISCORDRICHINTEGRATION_API FDiscordPresenceManager
{
public:
	FDiscordPresenceManager(UDiscordGameInstanceSubsystem* InDiscordGameInstanceSubsystem);
	virtual ~FDiscordPresenceManager() {};

protected:

	/**
	 * @brief Setup the initial presence that is set in the project settings 
	 */
	void SetupInitialPresence();	

public:

	/** 
	 * @brief Update the activity if something has changed.
	 */
	void Update();

public:

	/** 
	 * @brief Update the state in the discord activity.
	 * @param State Current user state (player's current party status).
	 */
	void SetState(const FString State);
	/** 
	 * @brief Update the details in the discord activity.
	 * @param Details Details of the users state (what the player is currently doing).
	 */
	void SetDetails(const FString Details);

	/** 
	 * @brief Update the large image in the discord activity.
	 * @param ImageKey key of the image that is uploaded on the discord management site.
	 * @param ImageHoverText Optional text when hovering the image in discord
	 */
	void SetLargeImage(const FString ImageKey, const FString ImageHoverText = "");
	/** 
	 * @brief Update the small image in the discord activity.
	 * @param ImageKey key of the image that is uploaded on the discord management site.
	 * @param ImageHoverText Optional text when hovering the image in discord
	 */
	void SetSmallImage(const FString ImageKey, const FString ImageHoverText = "");

	/** 
	 * @brief Update the duration in the discord activity. 
	 * @param Time Time in UTC Unix. 
	 * @param IsStartTime If set to true it will show up as duration played, otherwise in duration left. Default is true.
	 */
	void SetTimeDuration(const int64 Time, const bool IsStartTime = true);

	/** 
	 * @brief Update the party in the discord activity. If no state has been set, this will not show up!
	 * @param PartyID A unique identifier for this party 
	 * @param CurrentPartySize The current amount of users in this party
	 * @param MaxPartySize The maximum size of this party
	 */
	void SetParty(const FString PartyID, const int32 CurrentPartySize, const int32 MaxPartySize = 0);

	/**
	 * @brief Set the unique party identifier in the discord activity.
	 * @param PartyID A unique identifier for this party 
	 */
	void SetPartyIdentifier(const FString PartyID);
	/**
	 * @brief Set the current party size in the discord activity.
	 * @param CurrentPartySize The current amount of users in this party
	 */
	void SetCurrentPartySize(const int32 CurrentPartySize);
	/**
	 * @brief Set the maximum party size in the discord activity.
	 * @param MaxPartySize The maximum size of this party
	 */
	void SetMaxPartySize(const int32 MaxPartySize);

	/** 
	 * @brief Update the instanced state in the discord activity.
	 * @param bIsInstanced if the user is currently in a instanced context, like a match.
	 */
	void SetInstanced(const bool bIsInstanced);

	//TODO: Getters


	/** 
	 * @brief Clear the discord activity.\n Note: You will have to set everything separate again!
	 */
	void ClearActivity();

	/** 
	 * @brief Clear the discord presence.
	 */
	void ClearPresence() const;

public:

	/**
	 * @brief Callback when the Discord activity has been updated. The update result value is returned. 
	 */
	FDiscordResultCallback OnActivityUpdated;
	/**
	 * @brief Callback when the Discord activity has been cleared. The result value of the clear call is given as a parameter.
	 */
	FDiscordResultCallback OnActivityCleared;

protected:

	// Cached Discord activity that is reused
    discord::Activity CachedActivity{};
	bool bActivityDirty = false;

	friend class FDiscordSessionManager;

private:

	// Activity update optimization
	time_t PreviousActivityUpdateTime = 0;

	// Handle to the Discord Manager
    UDiscordGameInstanceSubsystem* DiscordGameInstanceSubsystemPtr = nullptr;
};
