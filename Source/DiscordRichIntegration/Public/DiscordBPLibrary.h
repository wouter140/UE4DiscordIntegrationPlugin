// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DiscordBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DISCORDRICHINTEGRATION_API UDiscordBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	/**
	 * @brief Setup the discord integration.\n
	 * Should be called on startup and will set the initial discord presence activity in discord from the settings.
	 * @return True if the initialization was successful and connection was made to the Discord client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static bool SetupDiscordIntegration(const UObject* WorldContextObject);

	/**
	 * @brief Update the state in the discord activity. 
	 * @param State Current user state (player's current party status).
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordState(const UObject* WorldContextObject, FString State);

	/**
	 * @brief Update the details in the discord activity.
	 * @param Details Details of the users state (what the player is currently doing).
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordDetails(const UObject* WorldContextObject, FString Details);

	/**
	 * @brief Update the large image in the discord activity.
	 * @param ImageKey Key of the large image that is uploaded to Discord.
	 * @param ImageHoverText Text to show when hovering over the large image. (Optional)
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordLargeImage(const UObject* WorldContextObject, FString ImageKey, FString ImageHoverText = "");
	/**
	 * @brief Update the small image in the discord activity.
	 * @param ImageKey Key of the small image that is uploaded to Discord.
	 * @param ImageHoverText Text to show when hovering over the small image. (Optional)
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordSmallImage(const UObject* WorldContextObject, FString ImageKey, FString ImageHoverText = "");

	/**
	 * @brief Update the duration in the discord activity. time is in UTC Unix. if isStartTime is set true, it will
	 * show up as duration played, otherwise in duration left. 
	 * @param Time Time to set in discord
	 * @param bIsStartTime True if the time is when the session started (will show as time playing). False will mean
	 * time left (count down)
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordTimeDuration(const UObject* WorldContextObject, int64 Time, bool bIsStartTime = true);

	/**
	 * @brief Update the party in the discord activity. If no state has been set, this will not show up! Minimum value
	 * is also 1!
	 * @param PartyID String representation of the party identifier
	 * @param CurrentPartySize Current size of the party (players that are in the party)
	 * @param MaxPartySize Maximum party size
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordParty(const UObject* WorldContextObject, FString PartyID, int32 CurrentPartySize, int32 MaxPartySize = 0);
		
	/**
	 * @brief Change session being instanced (playing)
	 * @param bIsInstance if the session is instanced (playing)
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void SetDiscordInstance(const UObject* WorldContextObject, bool bIsInstance);

	/**
	 * @brief Clear the discord activity. You will have to set everything separate again!
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void ClearDiscordActivity(const UObject* WorldContextObject);

	/**
	 * @brief Clear the discord presence.
	 */
	UFUNCTION(BlueprintCallable, Category = "Discord", meta=(WorldContext="WorldContextObject"))
	static void ClearDiscordPresence(const UObject* WorldContextObject);

};
