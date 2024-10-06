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

void FNoiseGenSceneViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	if (Pass == EPostProcessingPass::VisualizeDepthOfField)
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

	// Create the output texture. It will be written to in the shader
	FRDGTextureDesc TextureDesc = FRDGTextureDesc::Create2D(
		{ SceneColor.ViewRect.Width(), SceneColor.ViewRect.Height() }, // Size
		SceneColor.Texture->Desc.Format, // Format
		FClearValueBinding::Black, // ClearValue
		TexCreate_ShaderResource | TexCreate_UAV // Flags
	);
	FRDGTextureRef OutputTexture = GraphBuilder.CreateTexture(TextureDesc, TEXT("Output Texture"));

	FIntRect ScreenSize = SceneColor.ViewRect;

	static float Time = 0.0f;
	Time += SceneView.Family->Time.GetDeltaRealTimeSeconds();
	Time = fmod(Time, 1000.0f);

	PassParameters->Color = FVector4f(1.f, 0.f, 0.f, 1.f);
	PassParameters->ScreenDimensions = FVector2f(SceneColor.ViewRect.Width(), SceneColor.ViewRect.Height());
	PassParameters->OutputTexture = GraphBuilder.CreateUAV(OutputTexture);
	PassParameters->Time = Time;

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

	// Copy the written to texture to the scene color texture
	AddCopyTexturePass(GraphBuilder, OutputTexture, SceneColor.Texture);

	return SceneColor;
}