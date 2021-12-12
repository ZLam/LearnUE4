// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPLGameMode.h"
#include "UPLCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUPLGameMode::AUPLGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
