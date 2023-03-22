// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RandomNearLocationBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API URandomNearLocationBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	URandomNearLocationBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargetLocationKey;
	
};
