// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DiscordRichIntegration.h"

#include "DiscordRichIntegrationProjectSettings.h"

#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FDiscordRichIntegrationModule"

void FDiscordRichIntegrationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule)
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("DiscordRichIntegrationSettings",
            LOCTEXT("RuntimeWDCategoryName", "DiscordRichIntegrationSettings"),
            LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the DiscordRichIntegration plugin"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "DiscordRichIntegration",
            LOCTEXT("RuntimeGeneralSettingsName", "DiscordRichIntegration"),
            LOCTEXT("RuntimeGeneralSettingsDescription", "DiscordRichIntegration Settings"),
            GetMutableDefault<UDiscordRichIntegrationProjectSettings>()
        );

		// Register the save handler to the settings
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FDiscordRichIntegrationModule::HandleSettingsSaved);
		}
	}
}

void FDiscordRichIntegrationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module
	if (UObjectInitialized())
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "DiscordRichIntegration");
		}
	}
}

// Callback for when the settings were saved.
bool FDiscordRichIntegrationModule::HandleSettingsSaved() const
{
	UDiscordRichIntegrationProjectSettings* Settings = GetMutableDefault<UDiscordRichIntegrationProjectSettings>();
	const bool bResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (bResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDiscordRichIntegrationModule, DiscordRichIntegration)
