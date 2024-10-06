// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"

class FGenerateNoiseCS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FGenerateNoiseCS)
	SHADER_USE_PARAMETER_STRUCT(FGenerateNoiseCS, FGlobalShader)

		BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)

		SHADER_PARAMETER(FVector4f, Color)
		SHADER_PARAMETER(FVector2f, ScreenDimensions)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float>, OutputTexture)
		SHADER_PARAMETER(float, Time)

		END_SHADER_PARAMETER_STRUCT()
};