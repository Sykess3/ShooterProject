// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(SPPlayerControllerLog, All, All)

void ASPPlayerController::FirstWeaponAction(const FInputActionValue& Value)
{
	UE_LOG(SPPlayerControllerLog, Error, TEXT("From FirstWeaponAction"))
}

void ASPPlayerController::SecondWeaponAction(const FInputActionValue& Value)
{
	UE_LOG(SPPlayerControllerLog, Error, TEXT("From SecondWeaponAction"))

}
