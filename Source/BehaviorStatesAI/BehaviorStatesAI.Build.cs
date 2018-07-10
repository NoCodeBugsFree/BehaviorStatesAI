// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BehaviorStatesAI : ModuleRules
{
	public BehaviorStatesAI(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks" });
	}
}
