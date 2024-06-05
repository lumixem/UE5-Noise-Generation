// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NoiseGenerationEditorTarget : TargetRules
{
	public NoiseGenerationEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("NoiseGeneration");
	}
}
