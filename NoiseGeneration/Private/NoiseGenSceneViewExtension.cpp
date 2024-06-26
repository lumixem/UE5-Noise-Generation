// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenSceneViewExtension.h"
#include "NoiseGenerationLogger.h"
#include "NoiseGenerationShaders.h"

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
		InOutPassCallbacks.Add(FAfterPassCallbackDelegate::CreateRaw(this, &FNoiseGenSceneViewExtension::GenerateNoise));
	}
}

FScreenPassTexture FNoiseGenSceneViewExtension::GenerateNoise(FRDGBuilder& GraphBuilder, const FSceneView& SceneView, const FPostProcessMaterialInputs& Inputs)
{
	const FScreenPassTexture& SceneColor = Inputs.Textures[(uint32)EPostProcessMaterialInput::SceneColor];

	RDG_EVENT_SCOPE(GraphBuilder, "Noise Generation Pass");

	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	// Create the shader
	TShaderMapRef<FGenerateNoiseCS> ComputeShader(GlobalShaderMap);

	return SceneColor;
}