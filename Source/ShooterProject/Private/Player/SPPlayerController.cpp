// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SPCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(SPPlayerControllerLog, All, All)



void ASPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SPCharacter = Cast<ASPCharacter>(PossessedCharacter);
}

void ASPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ASPPlayerController::OnStartFire);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ASPPlayerController::OnStopFire);
	EnhancedInputComponent->BindAction(DebugTakeDamage, ETriggerEvent::Started, this, &ASPPlayerController::OnDebugTakeDamage);
}

void ASPPlayerController::FirstWeaponAction(const FInputActionValue& Value)
{
	PossessedCharacter->SetOverlayState(EALSOverlayState::PistolOneHanded);
}

void ASPPlayerController::SecondWeaponAction(const FInputActionValue& Value)
{
	PossessedCharacter->SetOverlayState(EALSOverlayState::Rifle);
}

void ASPPlayerController::OnStartFire()
{
	SPCharacter->StartFire();
}

void ASPPlayerController::OnStopFire()
{
	SPCharacter->StopFire();
}

void ASPPlayerController::OnDebugTakeDamage()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 10, GetPawn()->GetActorLocation(), 10, {}, {}, this, nullptr, true);
} 


