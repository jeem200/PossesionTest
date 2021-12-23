// Copyright Epic Games, Inc. All Rights Reserved.

#include "PossesionGameMode.h"
#include "PossesionHUD.h"
#include "PossesionCharacter.h"
#include "UObject/ConstructorHelpers.h"

APossesionGameMode::APossesionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APossesionHUD::StaticClass();
}
