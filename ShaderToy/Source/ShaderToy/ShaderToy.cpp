// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderToy.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FShaderToyModule"

void FShaderToyModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FString ShadersDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Shaders"), ShadersDir);		// 加上搜索目录，不然材质节点include不到
}

void FShaderToyModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE(FShaderToyModule, ShaderToy, "ShaderToy");
