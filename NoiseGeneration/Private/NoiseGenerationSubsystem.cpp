// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenerationSubsystem.h"
#include "NoiseGenerationLogger.h"
#include "NoiseGenSceneViewExtension.h"

#include "SceneViewExtension.h"

void UNoiseGenerationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(NoiseGenerationInit, Log, TEXT("NoiseGenerationSubsystem initialized"));

	m_NoiseGenerationSceneViewExtension = FSceneViewExtensions::NewExtension<FNoiseGenSceneViewExtension>();
	UE_LOG(NoiseGenerationInit, Log, TEXT("FNoiseGenSceneViewExtension created"));
	UE_LOG(NoiseGenerationInit, Log, TEXT("NoiseGenerationSubsystem initialized"));
}

void UNoiseGenerationSubsystem::Deinitialize()
{
	// Prevent this SVE from being gathered, in case it is kept alive by a strong reference somewhere else.
	{
		m_NoiseGenerationSceneViewExtension->IsActiveThisFrameFunctions.Empty();

		FSceneViewExtensionIsActiveFunctor IsActiveFunctor;

		IsActiveFunctor.IsActiveFunction = [](const ISceneViewExtension* SceneViewExtension, const FSceneViewExtensionContext& Context)
			{
				return TOptional<bool>(false);
			};

		m_NoiseGenerationSceneViewExtension->IsActiveThisFrameFunctions.Add(IsActiveFunctor);
	}


	m_NoiseGenerationSceneViewExtension.Reset();
	m_NoiseGenerationSceneViewExtension = nullptr;
}