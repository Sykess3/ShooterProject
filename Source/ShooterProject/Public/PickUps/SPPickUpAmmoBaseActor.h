// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/SPPickUpBaseActor.h"
#include "SPPickUpAmmoBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPPickUpAmmoBaseActor : public ASPPickUpBaseActor
{
	GENERATED_BODY()
public:	
	ASPPickUpAmmoBaseActor();
protected:
	virtual bool TryGivePickUpTo(AActor* OtherActor) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AmmoAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
};
