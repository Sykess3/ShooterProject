// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SPCharacter.h"
#include "SPAICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPAICharacter : public ASPCharacter
{
	GENERATED_BODY()
public:
	ASPAICharacter(const FObjectInitializer& ObjectInitializer);

	UBehaviorTree* GetBehaviourTree() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
