// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSPlayerController.h"
#include "InputActionValue.h"
#include "SPPlayerController.generated.h"

class ASPCharacter;
/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class SHOOTERPROJECT_API ASPPlayerController : public AALSPlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UFUNCTION()
	void FirstWeaponAction(const FInputActionValue& Value);

	UFUNCTION()
	void SecondWeaponAction(const FInputActionValue& Value);

	UFUNCTION()
	void FireAction(const FInputActionValue& Value);

	UPROPERTY()
	ASPCharacter* SPCharacter;
	
};
