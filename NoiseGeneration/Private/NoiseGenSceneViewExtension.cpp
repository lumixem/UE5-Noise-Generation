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

	// Retrieve the FGenerateNoiseCS shader parameters
	FGenerateNoiseCS::FParameters* PassParameters = GraphBuilder.AllocParameters<FGenerateNoiseCS::FParameters>();

	PassParameters->Color = FVector4f(1.f, 0.f, 0.f, 1.f);

	FIntRect ScreenSize = SceneColor.ViewRect;

	const int32 DefaultGroupSize = 8;
	FIntPoint GroupSize(DefaultGroupSize, DefaultGroupSize);
	FIntVector GroupCount = FComputeShaderUtils::GetGroupCount(ScreenSize.Size(), GroupSize);

	// Create the shader
	TShaderMapRef<FGenerateNoiseCS> ComputeShader(GlobalShaderMap);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("Noise Generatio CS"),
		ComputeShader,
		PassParameters,
		GroupCount);

	return SceneColor;
}