#pragma once

#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#include "DiscordGameSDK/types.h"
THIRD_PARTY_INCLUDES_END

#include "DiscordUser.generated.h"

USTRUCT(BlueprintType)
struct FDiscordUser
{
    GENERATED_BODY()

    FDiscordUser()
        : Id(0)
    {}

    explicit FDiscordUser(const discord::User User)
        : Id(User.GetId())
        , Username(User.GetUsername())
        , Discriminator(User.GetDiscriminator())
        , Avatar(User.GetAvatar())
    {}

    // TODO: make blueprint type
    FString GetAvatarURL(const int32 Size = 128) const
    {
        return FString(TEXT("https://cdn.discordapp.com/avatars/") + FString::FromInt(Id) + TEXT("/") + Avatar + TEXT(".png?size=") + FString::FromInt(Size));
    }

    /* Id of the user, aka Snowflake. */
    UPROPERTY(BlueprintReadOnly, Category=Discord)
    INT64 Id;

    /* Username of the user, not unique across the platform. */
    UPROPERTY(BlueprintReadOnly, Category=Discord)
    FString Username;

    /* The user's 4-digit discord-tag. */
    UPROPERTY(BlueprintReadOnly, Category=Discord)
    FString Discriminator;

    /* The user's avatar hash. https://discordapp.com/developers/docs/reference#image-formatting */
    UPROPERTY(BlueprintReadOnly, Category=Discord)
    FString Avatar;

};