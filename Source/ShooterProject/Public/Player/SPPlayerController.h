// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSPlayerController.h"
#include "InputActionValue.h"
#include "SPPlayerController.generated.h"

class UInputAction;
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
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Input")
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Input")
	UInputAction* DebugTakeDamage;

	UPROPERTY()
	ASPCharacter* SPCharacter;

	UFUNCTION()
	void FirstWeaponAction(const FInputActionValue& Value);

	UFUNCTION()
	void SecondWeaponAction(const FInputActionValue& Value);

	UFUNCTION()
	void OnStartFire();

	UFUNCTION()
	void OnStopFire();

	void OnDebugTakeDamage();
};
