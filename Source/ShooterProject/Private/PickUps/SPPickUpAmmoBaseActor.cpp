// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/SPPickUpAmmoBaseActor.h"

#include "Player/SPCharacter.h"
#include "Weapon/SPBaseWeaponActor.h"

ASPPickUpAmmoBaseActor::ASPPickUpAmmoBaseActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Model");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

bool ASPPickUpAmmoBaseActor::TryGivePickUpTo(AActor* OtherActor)
{
	if (ASPCharacter* Character = Cast<ASPCharacter>(OtherActor))
	{
		if (ASPBaseWeaponActor* Weapon = Character->GetWeaponInUse())
		{
			if (Weapon->AreClipsFull())
			{
				return false;
			}

			Weapon->AccrueAmmo(AmmoAmount);
			return true;
		}
	}

	return false;
}
