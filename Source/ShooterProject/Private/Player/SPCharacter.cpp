// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPCharacter.h"
#include "Components/SPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Weapon/SPBaseWeaponActor.h"

ASPCharacter::ASPCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HealthComponent = CreateDefaultSubobject<USPHealthComponent>("HealthComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());

	HoldWeaponSocket = TEXT("VB RHS_ik_hand_gun");
}

void ASPCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	HealthComponent->OnHealthChanged.AddUObject(this, &ASPCharacter::OnHealthChangedHandler);
}

void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASPCharacter::Shoot()
{
	if (WeaponInUse)
	{
		WeaponInUse->TryShoot(this);
	}
}


void ASPCharacter::AttachWeaponToHand()
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	WeaponInUse->AttachToComponent(GetMesh(), AttachmentRules, HoldWeaponSocket);
}

void ASPCharacter::ChangeWeaponSlot_Implementation(const EWeaponSlot WeaponSlot)
{
	UWorld* World = GetWorld();
	if (WeaponInUse)
	{
		WeaponInUse->Destroy();
	}
	const int8 SlotIndex = static_cast<int8>(WeaponSlot);
	WeaponInUse = World->SpawnActor<ASPBaseWeaponActor>(WeaponClasses[SlotIndex]);
	check(WeaponInUse);

	AttachWeaponToHand();
}

void ASPCharacter::OnOverlayStateChanged(EALSOverlayState PreviousState)
{
	Super::OnOverlayStateChanged(PreviousState);
	
	switch (OverlayState)
	{
	case EALSOverlayState::Rifle: ChangeWeaponSlot(EWeaponSlot::Main);
		break;
	case EALSOverlayState::PistolOneHanded: ChangeWeaponSlot(EWeaponSlot::Additive);
		break;
	}
}

void ASPCharacter::OnHealthChangedHandler(float Amount)
{
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Amount)));
}

