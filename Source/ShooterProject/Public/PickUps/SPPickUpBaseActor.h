// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPPickUpBaseActor.generated.h"

UCLASS()
class SHOOTERPROJECT_API ASPPickUpBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASPPickUpBaseActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	virtual bool TryGivePickUpTo(AActor* OtherActor);
	virtual void PickUpHasTaken();
private:
};
