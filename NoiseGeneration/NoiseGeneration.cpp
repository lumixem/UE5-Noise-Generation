// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseGeneration.h"

#include "Misc/Paths.h"
#include "GlobalShader.h"

IMPLEMENT_MODULE(FNoiseGenerationModule, NoiseGeneration);

void FNoiseGenerationModule::StartupModule()
{
	const FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));

	AddShaderSourceDirectoryMapping(FString("/Shaders"), ShaderDirectory);
}

void FNoiseGenerationModule::ShutdownModule() {};