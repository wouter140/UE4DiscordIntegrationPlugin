// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class DiscordRichIntegration : ModuleRules
{
	public DiscordRichIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the include paths for the plugin
			PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "ThirdParty")));
			PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "ThirdParty")));
			
			// Copy discord game sdk dll to binary folder and declare the dll as a runtime dependency
			RuntimeDependencies.Add("$(BinaryOutputDir)/discord_game_sdk.dll", 
				Path.Combine(ModuleDirectory, "ThirdParty", "DiscordGameSDK", "Redist", Target.Platform.ToString(), "discord_game_sdk.dll"));
			
			// Add the discord Lib as additional library
			PublicAdditionalLibraries.Add(
				Path.Combine(ModuleDirectory, "ThirdParty", "DiscordGameSDK", "Redist", Target.Platform.ToString(), "discord_game_sdk.dll.lib"));
		}
		else
		{
			throw new NotImplementedException("This target platform is not configured for GameAnalytics SDK: " + Target.Platform.ToString());
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
				// ... add other public dependencies that you statically link with here ...
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine"
				// ... add private dependencies that you statically link with here ...	
			}
		);
	}
}
