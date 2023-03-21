// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SPHealthComponent.h"


USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth > 0)

	SetHeath(MaxHealth);

	AActor* Owner = GetOwner();
	Owner->OnTakeAnyDamage.AddDynamic(this, &USPHealthComponent::OnTakeDamageHandler);
}


void USPHealthComponent::OnTakeDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy,
                                             AActor* DamageCauser)
{
	if (Damage <= 0 || IsDead())
	{
		return;
	}

	SetHeath(CurrentHealth - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void USPHealthComponent::SetHeath(float Amount)
{
	CurrentHealth = FMath::Clamp(Amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}
