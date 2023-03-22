// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RandomNearLocationBTTaskNode.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

URandomNearLocationBTTaskNode::URandomNearLocationBTTaskNode()
{
	NodeName = "RandomNearLocation";
}

EBTNodeResult::Type URandomNearLocationBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Pawn is nullptr"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NavSystem is nullptr"));
		return EBTNodeResult::Failed;
	}
	FNavLocation NavLocationResult;
	bool HasFounded = NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocationResult);
	if (!HasFounded)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocationResult.Location);
	return EBTNodeResult::Succeeded;
}
