// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrickSimGameMode.h"
#include "CrickSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACrickSimGameMode::ACrickSimGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
