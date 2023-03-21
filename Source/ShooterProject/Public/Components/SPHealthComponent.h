// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealthAbsoluteAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERPROJECT_API USPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USPHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const {return CurrentHealth / MaxHealth;} 

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return CurrentHealth <= 0; }

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta =(ClampMin = 0.0f, ClampMax = 1000.0f))
	float MaxHealth;
	
	virtual void BeginPlay() override;

	void SetHeath(float Amount);

private:
	float CurrentHealth;

	UFUNCTION()
	void OnTakeDamageHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
		AActor* DamageCauser);
};
