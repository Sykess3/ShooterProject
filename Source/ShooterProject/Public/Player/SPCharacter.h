// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "SPCharacter.generated.h"

class USPWeaponComponent;
class UTextRenderComponent;
class USPHealthComponent;
class ASPBaseWeaponActor;
/**
 * 
 */

UCLASS()
class SHOOTERPROJECT_API ASPCharacter : public AALSBaseCharacter
{
	GENERATED_BODY()

public:
	ASPCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	void Shoot();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthTextRenderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USPHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<ASPBaseWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	ASPBaseWeaponActor* WeaponInUse;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName HoldWeaponSocket;


	virtual void OnOverlayStateChanged(EALSOverlayState PreviousState) override;

private:
	void OnHealthChangedHandler(float Amount);
	void SpawnRifle();
	
};
