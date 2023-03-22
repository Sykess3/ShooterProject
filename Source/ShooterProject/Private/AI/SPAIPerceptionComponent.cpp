// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/SPHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USPAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0)
		return nullptr;

	AAIController* AIController = GetOwner<AAIController>();
	check(AIController);

	const APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
		return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestActor = nullptr;

	for(auto PossibleTarget : PerceivedActors)
	{
		USPHealthComponent* HealthComponent = PossibleTarget->FindComponentByClass<USPHealthComponent>();
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const float PossibleBestDistance = (PossibleTarget->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (PossibleBestDistance < BestDistance)
			{
				BestDistance = PossibleBestDistance;
				BestActor = PossibleTarget;
			}	
		}
	}
	return BestActor;
}

