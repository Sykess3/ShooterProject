// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

#include "Player/SPCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(SPPlayerControllerLog, All, All)


void ASPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SPCharacter = Cast<ASPCharacter>(PossessedCharacter);
}

void ASPPlayerController::FirstWeaponAction(const FInputActionValue& Value)
{
	PossessedCharacter->SetOverlayState(EALSOverlayState::PistolOneHanded);
}

void ASPPlayerController::SecondWeaponAction(const FInputActionValue& Value)
{
	PossessedCharacter->SetOverlayState(EALSOverlayState::Rifle);
}

void ASPPlayerController::FireAction(const FInputActionValue& Value)
{
	SPCharacter->Shoot();
}


