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
};