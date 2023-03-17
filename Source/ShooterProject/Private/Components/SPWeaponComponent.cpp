#include "Components/SPWeaponComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Player/SPCharacter.h"

USPWeaponComponent::USPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USPWeaponComponent::Shoot()
{
	ASPCharacter* Player = Cast<ASPCharacter>(GetOwner());
	check(Player);

	AController* Controller = Player->GetController();
	check(Controller);

	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
		WeaponMeshComponent.GetComponent(Player));
	check(SkeletalMeshComponent);

	const FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = ViewLocation;
	const FVector TraceDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + TraceDirection * MaxShootDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);
		
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, TraceEnd - TraceStart, HitResult, Controller, Player,
			                                   DamageType);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f);
	}
}
