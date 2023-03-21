// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/SPHealthPickUpBaseActor.h"

#include "Components/SPHealthComponent.h"

ASPHealthPickUpBaseActor::ASPHealthPickUpBaseActor() 
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Model");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

bool ASPHealthPickUpBaseActor::TryGivePickUpTo(AActor* OtherActor)
{
	UActorComponent* Component = OtherActor->GetComponentByClass(USPHealthComponent::StaticClass());
	if (!Component)
		return false;
	
	if (USPHealthComponent* HealthComponent = Cast<USPHealthComponent>(Component))
	{
		if (HealthComponent->IsHealthFull())
			return false;

		HealthComponent->Heal(HealAmount);
		return true;
	}

	return false;
}
