# UE4 Discord Integration Plugin

This plugin is a wrapper and manager around the Discord GameSDK for easy integration in an UnrealEngine project.


## Installation
To install the plugin from this repository you will have to copy the files into a folder called `DiscordRichIntegration`, in the `Plugins` folder of your project.

### Discord Game SDK
Due to licence restrictions I am not allowed to include the Discord GameSDK into this plugin. 

#### Step 1 - Downloading
So to use the plugin you will also have to [download the GameSDK from Discord](https://discord.com/developers/docs/game-sdk/sdk-starter-guide), the link is in Step 1 - Get the Thing. 

#### Step 2 - Unzipping
Unpack the ZIP file anywhere you can access.

#### Step 3 - Copying Include files
Copy all the files in the `/cpp` folder into the `/Plugins/DiscordRichIntegration/Source/DiscordRichIntegration/ThirdParty/DiscordGameSDK` folder of the plugin.

#### Step 4 - Copying Win32 binaries
Copy all the `.dll` and `.dll.lib` files in the `/lib/x86` folder into the `/Plugins/DiscordRichIntegration/Source/DiscordRichIntegration/ThirdParty/DiscordGameSDK/Redist/Win32` folder of the plugin.

#### Step 5 - Copying Win64 binaries
Copy all the `.dll` and `.dll.lib` files in the `/lib/x86_64` into the `/Plugins/DiscordRichIntegration/Source/DiscordRichIntegration/ThirdParty/DiscordGameSDK/Redist/Win64` folder of the plugin.