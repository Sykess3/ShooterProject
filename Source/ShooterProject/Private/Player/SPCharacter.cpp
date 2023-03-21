// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	HealthComponent->OnHealthChanged.AddDynamic(this, &ASPCharacter::OnHealthChangedHandler);
	HealthComponent->OnDeath.AddDynamic(this, &ASPCharacter::OnDeathHandler);
}


void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASPCharacter::StartFire()
{
	if (WeaponInUse)
	{
		WeaponInUse->StartFire();
	}
}

void ASPCharacter::StopFire()
{
	if (WeaponInUse)
	{
		WeaponInUse->StopFire();
	}
}


void ASPCharacter::AttachToHand(AActor* ActorToWhichAttach) const
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	ActorToWhichAttach->AttachToComponent(GetMesh(), AttachmentRules, HoldWeaponSocket);
}

void ASPCharacter::ChangeWeaponSlot_Implementation(const EWeaponSlot WeaponSlot)
{
	UWorld* World = GetWorld();
	if (WeaponInUse)
	{
		//HealthComponent->OnDeath.Remove(WeaponInUse, &ASPBaseWeaponActor::OnDeathHandler);
		WeaponInUse->Destroy();
	}
	const int8 SlotIndex = static_cast<int8>(WeaponSlot);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	WeaponInUse = World->SpawnActor<ASPBaseWeaponActor>(WeaponClasses[SlotIndex], SpawnParameters);
	check(WeaponInUse);

	AttachToHand(WeaponInUse);
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

void ASPCharacter::OnDeathHandler()
{
	RagdollAction();
	GetCharacterMovement()->DisableMovement();
	Controller->ChangeState(NAME_Spectating);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	SetLifeSpan(4.0f);
}

