// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Character/ALSCharacter.h"
#include "SPCharacter.generated.h"

class UTextRenderComponent;
class USPHealthComponent;
class ASPBaseWeaponActor;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponChanged);

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Main = 0,
	Additive = 1
};

UENUM(BlueprintType)
enum class ETeamId : uint8
{
	Player = 0,
	Monster = 1
};


UCLASS()
class SHOOTERPROJECT_API ASPCharacter : public AALSBaseCharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ASPCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	void StartFire();
	void StopFire();

	USPHealthComponent* GetHealthComponent() const;

	virtual FGenericTeamId GetGenericTeamId() const override;

	UFUNCTION(BlueprintCallable)
	ASPBaseWeaponActor* GetWeaponInUse() const { return WeaponInUse; };

	UPROPERTY(BlueprintAssignable)
	FOnWeaponChanged OnWeaponChanged;

protected:
	TMap<EWeaponSlot, ASPBaseWeaponActor*> WeaponsCache;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	ASPBaseWeaponActor* WeaponInUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName HoldWeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TArray<TSubclassOf<ASPBaseWeaponActor>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Team")
	ETeamId TeamId;

	UFUNCTION(BlueprintNativeEvent)
	void ChangeWeaponSlot(const EWeaponSlot WeaponSlot);

	virtual void OnOverlayStateChanged(EALSOverlayState PreviousState) override;

private:
	UFUNCTION()
	void OnDeathHandler(AActor* Killer, AActor* Victim);
	void AttachToHand(AActor* ActorToWhichAttach) const;
};
