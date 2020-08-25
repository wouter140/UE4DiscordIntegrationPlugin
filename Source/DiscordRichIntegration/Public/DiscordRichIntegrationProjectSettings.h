// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "DiscordRichIntegrationProjectSettings.generated.h"


/**
 * 
 */
UCLASS(config = Plugins, defaultconfig)
class DISCORDRICHINTEGRATION_API UDiscordRichIntegrationProjectSettings : public UObject
{
	GENERATED_BODY()

public:

	// Client ID
	UPROPERTY(Config, EditAnywhere, Category = Application, Meta = (ToolTip = "Your application's ClientID. You can get this from the discord developer site, in your application!"))
	FString ClientID = "";
	
	// If discord is required to run the game
	UPROPERTY(Config, EditAnywhere, Category = Application, Meta = (ToolTip = "Does your application require discord to be running in order to work. If set to true and discord is not running, the game will close, start discord and attempt to run the game. As you are using this as plugin, you should most likely keep this false!"))
	bool bRequireDiscordRunning = false;


	// Client ID
	UPROPERTY(Config, EditAnywhere, Category = Launcher, Meta = (ToolTip = "Your games' Steam AppID to register. Discord will use this AppID to start your game from discord through steam! If anything is entered, this is used instead of the application url!"))
	FString SteamAppID = "";
	UPROPERTY(Config, EditAnywhere, Category = Launcher, Meta = (ToolTip = "Start URL of your games' application to register. Discord will use this to start your game application from discord! If the Steam AppID is set, this will be ignored!"))
	FString ApplicationStartUrl = "";


	// Default activity when the application is started
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (ToolTip = "Set an initial activity when the application starts. You can also do this through blueprinting though!"))
	bool bEnableDefaultActivity = false;

	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Set the starttime to show time playing in discord."))
	bool bSetStartTime = true;

	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Initial activity details (Players current activity in game). eg: 'In Lobby' or 'Playing <GameMode> in <Map>'. Can be left empty to now show!"))
	FString Details = "";
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Initial activity state (Player's party status). eg: 'Solo'. Can be left empty to not show!"))
	FString State = "";
	
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Enable an initial large image"))
	bool bEnableLargeImage = false;
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableLargeImage", ToolTip = "The large image key from your application to show."))
	FString LargeImage = "";
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableLargeImage", ToolTip = "Text to show when hovering over the large image. Leave empty to show no text on hover!"))
	FString LargeImageText = "";

	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Enable an initial small image"))
	bool bEnableSmallImage = false;
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableSmallImage", ToolTip = "The small image key from your application to show."))
	FString SmallImage = "";
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableSmallImage", ToolTip = "Text to show when hovering over the small image. Leave empty to show no text on hover!"))
	FString SmallImageText = "";

	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity", ToolTip = "Enable setting an initial party. State is required to be set for this to show up!"))
	bool bEnableInitialParty = false;
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableInitialParty", ToolTip = "Initial party size (Amount of players in the party, usually 1 when first stating the game)"))
	int32 InitialPartySize = 1;
	UPROPERTY(Config, EditAnywhere, Category = DefaultActivity, Meta = (editcondition = "bEnableDefaultActivity && bEnableInitialParty", ToolTip = "Initial max party size (Max amount of players in a party)"))
	int32 MaxPartySize = 4;

	// Note CanEditChange is only available when compiling with the editor. You must add this or your builds might not work!
#if WITH_EDITOR
	virtual bool CanEditChange(const UProperty* InProperty) const override;
#endif
};
