// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordBPLibrary.h"

#include "DiscordPresenceManager.h"
#include "DiscordGameInstanceSubsystem.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

bool UDiscordBPLibrary::SetupDiscordIntegration(const UObject* WorldContextObject)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager)
	{
		return GameInstanceSubsystem->Setup();
	}
	return false;
}

void UDiscordBPLibrary::SetDiscordState(const UObject* WorldContextObject, FString State)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetState(State);
	}
}

void UDiscordBPLibrary::SetDiscordDetails(const UObject* WorldContextObject, FString Details)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetDetails(Details);
    }
}

void UDiscordBPLibrary::SetDiscordLargeImage(const UObject* WorldContextObject, FString ImageKey, FString ImageHoverText /*= ""*/)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetLargeImage(ImageKey, ImageHoverText);
    }
}

void UDiscordBPLibrary::SetDiscordSmallImage(const UObject* WorldContextObject, FString ImageKey, FString ImageHoverText /*= ""*/)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetSmallImage(ImageKey, ImageHoverText);
    }
}

void UDiscordBPLibrary::SetDiscordTimeDuration(const UObject* WorldContextObject, int64 Time, bool bIsStartTime /*= true*/)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetTimeDuration(Time, bIsStartTime);
    }
}

void UDiscordBPLibrary::SetDiscordParty(const UObject* WorldContextObject, FString PartyID, int32 CurrentPartySize, int32 MaxPartySize /*= -1*/)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetParty(PartyID, CurrentPartySize, MaxPartySize);
    }
}

void UDiscordBPLibrary::SetDiscordInstance(const UObject* WorldContextObject, bool bIsInstance)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->SetInstanced(bIsInstance);
    }
}

void UDiscordBPLibrary::ClearDiscordActivity(const UObject* WorldContextObject)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->ClearActivity();
    }
}

void UDiscordBPLibrary::ClearDiscordPresence(const UObject* WorldContextObject)
{
	UDiscordGameInstanceSubsystem* GameInstanceSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
	FDiscordPresenceManager* DiscordPresenceManager = GameInstanceSubsystem->GetDiscordPresenceManager();
	if(DiscordPresenceManager) {
		DiscordPresenceManager->ClearPresence();
    }
}
