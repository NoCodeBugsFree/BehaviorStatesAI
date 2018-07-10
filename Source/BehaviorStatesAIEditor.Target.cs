// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BehaviorStatesAIEditorTarget : TargetRules
{
	public BehaviorStatesAIEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("BehaviorStatesAI");
	}
}
