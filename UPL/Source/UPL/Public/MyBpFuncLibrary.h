// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBpFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UPL_API UMyBpFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void CppCallJava(const UObject * WorldContextObject);
};
