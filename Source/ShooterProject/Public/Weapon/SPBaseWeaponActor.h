// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPBaseWeaponActor.generated.h"

UCLASS()
class SHOOTERPROJECT_API ASPBaseWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPBaseWeaponActor();
	void TryShoot(AActor* WeaponOwner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxShootDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Damage")
	TSubclassOf<UDamageType> DamageType;
};
