// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/SPPickUpAmmoBaseActor.h"

#include "Player/SPCharacter.h"

bool ASPPickUpAmmoBaseActor::TryGivePickUpTo(AActor* OtherActor)
{
	if (ASPCharacter* Character = Cast<ASPCharacter>(OtherActor))
	{
		
	}

	return false;
}
