// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"

/**
 *
 */
class FNoiseGenSceneViewExtension : public FSceneViewExtensionBase
{
public:
	FNoiseGenSceneViewExtension(const FAutoRegister& AutoRegister);
	~FNoiseGenSceneViewExtension() = default;

	// Overriden FSceneViewExtensionBase functions
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override; 	//TODO perhaps PostRenderBasePassDeferred_RenderThread will make more sense
	virtual void SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled);

	// Custom function which adds the render pass
	void GenerateNoise(FRDGBuilder& GraphBuilder, const FSceneView& SceneView, const FPostProcessMaterialInputs& Inputs);
	void CreateShader(FRDGBuilder& GraphBuilder);
};