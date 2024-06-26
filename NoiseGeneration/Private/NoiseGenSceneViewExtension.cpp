// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenSceneViewExtension.h"
#include "NoiseGenerationLogger.h"

#include "PostProcess/PostProcessing.h"
#include "PostProcess/PostProcessMaterial.h"
#include "RenderGraphUtils.h"

FNoiseGenSceneViewExtension::FNoiseGenSceneViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
	UE_LOG(NoiseGenerationInit, Log, TEXT("NoiseGenSceneViewExtension registered"));
}

void FNoiseGenSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	
}

void FNoiseGenSceneViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	if (Pass == EPostProcessingPass::Tonemap)
	{

	}
}

void FNoiseGenSceneViewExtension::GenerateNoise(FRDGBuilder& GraphBuilder, const FSceneView& SceneView, const FPostProcessMaterialInputs& Inputs)
{
	const FScreenPassTexture& SceneColor = Inputs.Textures[(uint32)EPostProcessMaterialInput::SceneColor];
}

void FNoiseGenSceneViewExtension::CreateShader(FRDGBuilder& GraphBuilder)
{
	//RDG_EVENT_SCOPE(GraphBuilder, "Noise Generation Start");
}