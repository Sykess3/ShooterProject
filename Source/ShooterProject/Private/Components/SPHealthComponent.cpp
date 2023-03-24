// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SPHealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Player/SPCharacter.h"


USPHealthComponent::USPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth > 0)

	SetHeath(MaxHealth);

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USPHealthComponent::OnTakeDamageHandler);
}


void USPHealthComponent::OnTakeDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy,
                                             AActor* DamageCauser)
{
	AActor* B = GetOwner();
	ETeamAttitude::Type Attitude = FGenericTeamId::GetAttitude(DamageCauser, B);
	if (Attitude != ETeamAttitude::Type::Hostile)
		return;

	if (Damage <= 0 || IsDead())
		return;

	SetHeath(CurrentHealth - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void USPHealthComponent::Heal(float Amount)
{
	SetHeath(CurrentHealth + Amount);
}

void USPHealthComponent::SetHeath(float Amount)
{
	CurrentHealth = FMath::Clamp(Amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}
