// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPWeaponComponent.generated.h"

struct FComponentReference;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERPROJECT_API USPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USPWeaponComponent();
	void Shoot();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	FComponentReference WeaponMeshComponent;

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
