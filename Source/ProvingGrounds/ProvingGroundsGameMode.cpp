// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ProvingGrounds.h"
#include "ProvingGroundsGameMode.h"
#include "Player/PlayerHUD.h"
#include "Player/FirstPersonCharacter.h"

AProvingGroundsGameMode::AProvingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Blueprints/ProvingGroundsCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// use our custom HUD class
	HUDClass = APlayerHUD::StaticClass();
}