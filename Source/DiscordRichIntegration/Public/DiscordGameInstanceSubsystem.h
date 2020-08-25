// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "DiscordPresenceManager.h"

THIRD_PARTY_INCLUDES_START
#include "DiscordGameSDK/discord.h"
THIRD_PARTY_INCLUDES_END

#include "DiscordGameInstanceSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DiscordLog, Log, All);

/**
 * 
 */
UCLASS()
class DISCORDRICHINTEGRATION_API UDiscordGameInstanceSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:

	UDiscordGameInstanceSubsystem();

    /**
    * @brief Setup Discord
    * @return If the setup was successful
    */
    bool Setup();
	
protected:
	
	/**
	* @brief Log callback event from the Discord GameSDK
	* @param DiscordLogLevel Log level
	* @param Message Log message
	*/
	virtual void OnLogMessage(discord::LogLevel DiscordLogLevel, char const* Message);

public:
	
	
	// Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	// Begin FTickableGameObject Interface
	virtual void Tick(float) override;
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface

	/**
	* @brief Get the Discord core object instance.
	* @return The Discord core object
	*/
	discord::Core* GetDiscordCore() const
	{
		return DiscordCore;
	}

	/**
	* @brief Retrieve the Discord Presence Manager Object
	* @return The Discord Presence Manager. You should not store the pointer locally.
	*/
	FDiscordPresenceManager* GetDiscordPresenceManager() const
	{
		return DiscordPresencePtr.Get();
	}

private:
	bool bCreatedWithGameRunning = false;
	
	// The Discord Core object
	discord::Core* DiscordCore = nullptr;

	TSharedPtr< FDiscordPresenceManager > DiscordPresencePtr = nullptr;	
	
};
