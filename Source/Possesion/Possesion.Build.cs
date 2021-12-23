// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Possesion : ModuleRules
{
	public Possesion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
