// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Demo : ModuleRules
{
	public Demo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"AnimGraphRuntime",
			"MotionWarping"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Demo",
			"Demo/Variant_Platforming",
			"Demo/Variant_Platforming/Animation",
			"Demo/Variant_Combat",
			"Demo/Variant_Combat/AI",
			"Demo/Variant_Combat/Animation",
			"Demo/Variant_Combat/Gameplay",
			"Demo/Variant_Combat/Interfaces",
			"Demo/Variant_Combat/UI",
			"Demo/Variant_SideScrolling",
			"Demo/Variant_SideScrolling/AI",
			"Demo/Variant_SideScrolling/Gameplay",
			"Demo/Variant_SideScrolling/Interfaces",
			"Demo/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
