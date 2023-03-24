// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/SPPickUpBaseActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ASPPickUpBaseActor::ASPPickUpBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ASPPickUpBaseActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPPickUpBaseActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (TryGivePickUpTo(OtherActor))
	{
		PickUpHasTaken();
	}
}

bool ASPPickUpBaseActor::TryGivePickUpTo(AActor* OtherActor)
{
	return false;
}

void ASPPickUpBaseActor::PickUpHasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle RespawnTimer;
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASPPickUpBaseActor::Respawn, RespawnTime);
}

void ASPPickUpBaseActor::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}


