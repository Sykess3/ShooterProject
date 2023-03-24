// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterProjectGameModeBase.h"
#include "Player/SPCharacter.h"
#include "Player/SPPlayerController.h"

AShooterProjectGameModeBase::AShooterProjectGameModeBase()
{
	DefaultPawnClass = ASPCharacter::StaticClass();
	PlayerControllerClass = ASPPlayerController::StaticClass();
}

