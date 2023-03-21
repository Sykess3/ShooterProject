// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUps/SPPickUpAmmoBaseActor.h"
#include "SPBaseWeaponActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoDataChanged);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AmountInBag = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ClipCapacity = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxOverallAmount;
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentClipAmount = 0;
	
};


UCLASS()
class SHOOTERPROJECT_API ASPBaseWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	ASPBaseWeaponActor();
	void StartFire();
	void StopFire();
	void OnDeathHandler();
	void AccrueAmmo(float AmmoAmount);

	bool IsNoAmmo() const;
	bool IsCurrentClipEmpty() const;
	bool AreClipsFull() const;
	bool IsCurrentClipFull() const;

	UFUNCTION(BlueprintCallable)
	FAmmoData GetAmmoData() const { return AmmoData; }

	UPROPERTY(BlueprintAssignable)
	FOnAmmoDataChanged OnAmmoDataChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxShootDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float FireRateInSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	FAmmoData AmmoData;

	void Shoot();
	void ReloadClip();
	void LogAmmo();
	bool TrySpendAmmo();
	void GetTraceData(AActor* WeaponOwner, FVector& TraceStart,
	                  FVector& TraceEnd);
	void ApplyDamage(AActor* WeaponOwner, FHitResult HitResult, FVector HitFromDirection);
	FVector GetMuzzleLocation();

	FHitResult MakeHit(AActor* WeaponOwner, const FVector TraceStart, const FVector TraceEnd);
private:
	FTimerHandle FireRateTimer;
	float DelayBetweenShots;
};
