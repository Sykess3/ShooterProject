// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPCharacter.h"
#include "Components/SPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "SPBaseWeaponActor.h"

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
		WeaponInUse->Shoot(this);
	}
}


void ASPCharacter::OnOverlayStateChanged(EALSOverlayState PreviousState)
{
	Super::OnOverlayStateChanged(PreviousState);
	switch (OverlayState)
	{
	case EALSOverlayState::Rifle: SpawnRifle();
		break;
	case EALSOverlayState::PistolOneHanded: SpawnRifle();
		break;
	}
}

void ASPCharacter::OnHealthChangedHandler(float Amount)
{
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Amount)));
}

void ASPCharacter::SpawnRifle()
{
	UWorld* World = GetWorld();
	if (!WeaponInUse)
	{
		WeaponInUse = World->SpawnActor<ASPBaseWeaponActor>(WeaponClass);
	}
	check(WeaponInUse);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	WeaponInUse->AttachToComponent(GetMesh(), AttachmentRules, HoldWeaponSocket);
}
