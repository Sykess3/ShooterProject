// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "SPCharacter.generated.h"

class USPWeaponComponent;
/**
 * 
 */

UCLASS()
class SHOOTERPROJECT_API ASPCharacter : public AALSCharacter
{
	GENERATED_BODY()

public:
	ASPCharacter(const FObjectInitializer& ObjectInitializer);	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USPWeaponComponent* WeaponComponent = nullptr;
	
	
	virtual void OnOverlayStateChanged(const EALSOverlayState PreviousState) override;
};
