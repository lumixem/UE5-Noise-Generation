// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "NoiseGenerationSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UNoiseGenerationSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	TSharedPtr<class FNoiseGenSceneViewExtension, ESPMode::ThreadSafe> m_NoiseGenerationSceneViewExtension;
};