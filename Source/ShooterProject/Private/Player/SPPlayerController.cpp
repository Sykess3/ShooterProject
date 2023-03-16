// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

#include "Components/SPWeaponComponent.h"
#include "Player/SPCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(SPPlayerControllerLog, All, All)


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
	UActorComponent* Src = PossessedCharacter->GetComponentByClass(USPWeaponComponent::StaticClass());
	USPWeaponComponent* UspWeaponComponent = Cast<USPWeaponComponent>(Src);
	UspWeaponComponent->Shoot();
	
}


