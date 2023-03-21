// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/SPPickUpBaseActor.h"
#include "Components/SphereComponent.h"

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
	Destroy();
}


