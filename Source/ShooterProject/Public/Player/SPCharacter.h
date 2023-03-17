// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "SPCharacter.generated.h"

class USPWeaponComponent;
class UTextRenderComponent;
class USPHealthComponent;
/**
 * 
 */

UCLASS()
class SHOOTERPROJECT_API ASPCharacter : public AALSCharacter
{
	GENERATED_BODY()

public:
	ASPCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USPWeaponComponent* WeaponComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthTextRenderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USPHealthComponent* HealthComponent;
	
	void OnHealthChangedHandler(float Amount);
};
