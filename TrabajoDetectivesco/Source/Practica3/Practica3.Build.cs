// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practica3 : ModuleRules
{
	public Practica3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
