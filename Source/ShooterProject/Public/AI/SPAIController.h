// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPAIController.generated.h"

class USPAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASPAIController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="AI")
	USPAIPerceptionComponent* SPPerceptionComponent;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
};
