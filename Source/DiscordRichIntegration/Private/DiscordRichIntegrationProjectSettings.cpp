// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordRichIntegrationProjectSettings.h"

#if WITH_EDITOR
bool UDiscordRichIntegrationProjectSettings::CanEditChange(const UProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDiscordRichIntegrationProjectSettings, SteamAppID))
	{
		return ApplicationStartUrl.Len() == 0 || (ApplicationStartUrl.Len() != 0 && SteamAppID.Len() != 0);
	}
	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDiscordRichIntegrationProjectSettings, ApplicationStartUrl))
	{
		return SteamAppID.Len() == 0;
	}


	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDiscordRichIntegrationProjectSettings, bEnableInitialParty))
	{
		return State.Len() > 0;
	}
	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDiscordRichIntegrationProjectSettings, InitialPartySize))
	{
		return State.Len() > 0;
	}
	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDiscordRichIntegrationProjectSettings, MaxPartySize))
	{
		return State.Len() > 0;
	}

	return ParentVal;
}
#endif