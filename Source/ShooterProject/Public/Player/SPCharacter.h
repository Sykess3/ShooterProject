// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "SPCharacter.generated.h"

class UTextRenderComponent;
class USPHealthComponent;
class ASPBaseWeaponActor;
/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Main = 0,
	Additive = 1
};

UCLASS()
class SHOOTERPROJECT_API ASPCharacter : public AALSBaseCharacter
{
	GENERATED_BODY()

public:
	ASPCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	void StartFire();
	void StopFire();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthTextRenderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	ASPBaseWeaponActor* WeaponInUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName HoldWeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TArray<TSubclassOf<ASPBaseWeaponActor>> WeaponClasses;

	UFUNCTION(BlueprintNativeEvent)
	void ChangeWeaponSlot(const EWeaponSlot WeaponSlot);

	virtual void OnOverlayStateChanged(EALSOverlayState PreviousState) override;

private:
	UFUNCTION()
	void OnHealthChangedHandler(float Amount);
	UFUNCTION()
	void OnDeathHandler();
	void AttachToHand(AActor* ActorToWhichAttach) const;
};
