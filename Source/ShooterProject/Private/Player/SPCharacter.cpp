// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPCharacter.h"

#include "Components/SPWeaponComponent.h"

ASPCharacter::ASPCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WeaponComponent = CreateDefaultSubobject<USPWeaponComponent>("WeaponComponent");
}

void ASPCharacter::OnOverlayStateChanged(const EALSOverlayState PreviousState)
{
	Super::OnOverlayStateChanged(PreviousState);
}
