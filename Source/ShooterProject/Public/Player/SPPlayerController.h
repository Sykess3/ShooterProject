// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSPlayerController.h"
#include "InputActionValue.h"
#include "SPPlayerController.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class SHOOTERPROJECT_API ASPPlayerController : public AALSPlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	void FirstWeaponAction(const FInputActionValue& Value);
	
	UFUNCTION()
	void SecondWeaponAction(const FInputActionValue& Value);
};

