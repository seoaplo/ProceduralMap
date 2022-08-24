// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralMapGameMode.h"
#include "ProceduralMapCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProceduralMapGameMode::AProceduralMapGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
