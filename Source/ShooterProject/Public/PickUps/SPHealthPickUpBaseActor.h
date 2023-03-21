// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/SPPickUpBaseActor.h"
#include "SPHealthPickUpBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPHealthPickUpBaseActor : public ASPPickUpBaseActor
{
	GENERATED_BODY()
public:
	ASPHealthPickUpBaseActor();
protected:
	virtual bool TryGivePickUpTo(AActor* OtherActor) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
};
