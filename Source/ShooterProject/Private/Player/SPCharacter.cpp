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

	HoldWeaponSocket = TEXT("VB RHS_ik_hand_gun");
}

void ASPCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
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

USPHealthComponent* ASPCharacter::GetHealthComponent() const
{
	return HealthComponent;
}

FGenericTeamId ASPCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(static_cast<uint8>(TeamId));	
}


void ASPCharacter::AttachToHand(AActor* ActorToWhichAttach) const
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	ActorToWhichAttach->AttachToComponent(GetMesh(), AttachmentRules, HoldWeaponSocket);
}

void ASPCharacter::ChangeWeaponSlot_Implementation(const EWeaponSlot WeaponSlot)
{
	StopFire();
	UWorld* World = GetWorld();
	if (WeaponInUse)
	{
		WeaponInUse->GetRootComponent()->SetVisibility(false, true);
	}
	
	const int8 SlotIndex = static_cast<int8>(WeaponSlot);
	if (!WeaponsCache.Contains(WeaponSlot))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		const auto NewWeaponActor = World->SpawnActor<ASPBaseWeaponActor>(WeaponClasses[SlotIndex], SpawnParameters);
		WeaponsCache.Add(WeaponSlot, NewWeaponActor);
	}
	WeaponInUse = WeaponsCache[WeaponSlot];
	WeaponInUse->GetRootComponent()->SetVisibility(true, true);
	check(WeaponInUse);

	AttachToHand(WeaponInUse);
	
	OnWeaponChanged.Broadcast();
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


void ASPCharacter::OnDeathHandler(AActor* Killer, AActor* Victim)
{
	RagdollAction();
	GetCharacterMovement()->DisableMovement();
	Controller->ChangeState(NAME_Spectating);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	SetLifeSpan(4.0f);
}

