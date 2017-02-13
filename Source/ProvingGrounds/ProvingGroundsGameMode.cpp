// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ProvingGrounds.h"
#include "ProvingGroundsGameMode.h"
#include "ProvingGroundsHUD.h"
#include "ProvingGroundsCharacter.h"

AProvingGroundsGameMode::AProvingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProvingGroundsHUD::StaticClass();
}
