// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenSceneViewExtension.h"
#include "NoiseGenerationLogger.h"

FNoiseGenSceneViewExtension::FNoiseGenSceneViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
	UE_LOG(NoiseGenerationInit, Log, TEXT("NoiseGenSceneViewExtension registered"));
}

void FNoiseGenSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{

}