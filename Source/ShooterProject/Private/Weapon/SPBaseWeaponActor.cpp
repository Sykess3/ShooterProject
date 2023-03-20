// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SPBaseWeaponActor.h"

#include "Kismet/GameplayStatics.h"

ASPBaseWeaponActor::ASPBaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMeshComponent->SetupAttachment(RootComponent);
	CollisionChannel = ECollisionChannel::ECC_Visibility;
	MaxShootDistance = 10000.0f;
}


void ASPBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPBaseWeaponActor::TryShoot(AActor* WeaponOwner)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	AController* Controller = WeaponOwner->GetInstigatorController();
	check(Controller);
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform SocketTransform = WeaponMeshComponent->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = ViewLocation;
	const FVector TraceDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + TraceDirection * MaxShootDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(WeaponOwner);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);

		if (AActor* HitActor = HitResult.GetActor())
		{
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, TraceEnd - TraceStart, HitResult, Controller, WeaponOwner,
											   DamageType);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f);
	}
}