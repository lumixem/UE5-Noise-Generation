// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenerationModule.h"
#include "NoiseGenerationLogger.h"

#include "Misc/Paths.h"
#include "GlobalShader.h"

IMPLEMENT_MODULE(FNoiseGenerationModule, NoiseGeneration);

void FNoiseGenerationModule::StartupModule()
{
	const FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));

	AddShaderSourceDirectoryMapping(FString("/Shaders"), ShaderDirectory);

	UE_LOG(NoiseGenerationInit, Log, TEXT("FNoiseGenerationModule started"));
}

void FNoiseGenerationModule::ShutdownModule() {};