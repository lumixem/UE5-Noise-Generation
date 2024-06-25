// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseGenerationShaders.h"

IMPLEMENT_GLOBAL_SHADER(FGenerateNoiseCS, "/Shaders/GenerateNoise.usf", "MainCS", SF_Compute);