// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAIController.h"

#include "AI/SPAICharacter.h"
#include "AI/SPAIPerceptionComponent.h"


ASPAIController::ASPAIController()
{
	SPPerceptionComponent = CreateDefaultSubobject<USPAIPerceptionComponent>("Perception");
	SetPerceptionComponent(*SPPerceptionComponent);
}

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const ASPAICharacter* AiCharacter = Cast<ASPAICharacter>(InPawn);
	if (AiCharacter)
	{
		RunBehaviorTree(AiCharacter->GetBehaviourTree());
	}
}

void ASPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AActor* ClosestEnemy = SPPerceptionComponent->GetClosestEnemy();
	if (ClosestEnemy)
	{
		SetFocus(ClosestEnemy);
	}
	else
	{
		SetFocus(nullptr);
	}
}
