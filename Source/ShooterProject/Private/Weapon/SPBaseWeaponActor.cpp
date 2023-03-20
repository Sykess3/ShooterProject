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
	DelayBetweenShots = 1 / FireRateInSecond;
}

void ASPBaseWeaponActor::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &ASPBaseWeaponActor::Shoot, DelayBetweenShots,
	                                       true);
}

void ASPBaseWeaponActor::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimer);
}

void ASPBaseWeaponActor::Shoot()
{
	SpendAmmo();
	FVector TraceStart, TraceEnd;
	GetTraceData(GetOwner(), TraceStart, TraceEnd);

	FHitResult HitResult = MakeHit(GetOwner(), TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);

		FVector HitFromDirection = TraceEnd - TraceStart;
		ApplyDamage(GetOwner(), HitResult, HitFromDirection);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleLocation(), TraceEnd, FColor::Red, false, 3.0f);
	}
	
}

void ASPBaseWeaponActor::GetTraceData(AActor* WeaponOwner, FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	AController* Controller = WeaponOwner->GetInstigatorController();
	check(Controller);
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	TraceStart = ViewLocation;
	const FVector TraceDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + TraceDirection * MaxShootDistance;
}

void ASPBaseWeaponActor::ApplyDamage(AActor* WeaponOwner, FHitResult HitResult, FVector HitFromDirection)
{
	if (AActor* HitActor = HitResult.GetActor())
	{
		UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitFromDirection, HitResult,
		                                   WeaponOwner->GetInstigatorController(),
		                                   WeaponOwner,
		                                   DamageType);
	}
}

void ASPBaseWeaponActor::OnDeathHandler()
{
	StopFire();
}


bool ASPBaseWeaponActor::IsAmmoBagEmpty() const
{
	return AmmoData.AmountInBag == 0;
}

FVector ASPBaseWeaponActor::GetMuzzleLocation()
{
	return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ASPBaseWeaponActor::IsCurrentClipEmpty() const
{
	return AmmoData.CurrentClipAmount == 0;
}

void ASPBaseWeaponActor::ChangeClip()
{
	if (AmmoData.ClipCapacity > AmmoData.AmountInBag)
	{
		AmmoData.CurrentClipAmount = AmmoData.AmountInBag;
		AmmoData.AmountInBag = 0;
	}
	else
	{
		AmmoData.CurrentClipAmount = AmmoData.ClipCapacity;
		AmmoData.AmountInBag -= AmmoData.ClipCapacity;
	}
}

void ASPBaseWeaponActor::LogAmmo()
{
}

void ASPBaseWeaponActor::SpendAmmo()
{
	if (IsCurrentClipEmpty() && !IsAmmoBagEmpty())
	{
		ChangeClip();
	}

	--AmmoData.CurrentClipAmount;
}

FHitResult ASPBaseWeaponActor::MakeHit(AActor* WeaponOwner, const FVector TraceStart, const FVector TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(WeaponOwner);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, CollisionParams);
	return HitResult;
}
