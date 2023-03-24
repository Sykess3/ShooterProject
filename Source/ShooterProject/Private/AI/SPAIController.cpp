// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAIController.h"

#include "AI/ALSAIController.h"
#include "AI/SPAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

ASPAIController::ASPAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perciption");
	SetPerceptionComponent(*PerceptionComponent);
}

void ASPAIController::BeginPlay()
{
	Super::BeginPlay();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASPAIController::OnTargetPerceptionUpdateHandler);
	PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this, &ASPAIController::OnTargetPerceptionInfoUpdatedHandler);
}

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ASPAIController::InitializeCharacter);
}

ETeamAttitude::Type ASPAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (!AICharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *GetName());
		return ETeamAttitude::Neutral;
	}
	
	if (auto OtherAgent= Cast<IGenericTeamAgentInterface>(&Other))
	{
		ETeamId ThisCharacterTeam = static_cast<ETeamId>(AICharacter->GetGenericTeamId().GetId());
		ETeamId OtherGenericTeamId = static_cast<ETeamId>(OtherAgent->GetGenericTeamId().GetId());
		
		return ThisCharacterTeam == OtherGenericTeamId
		? ETeamAttitude::Type::Friendly
		: ETeamAttitude::Type::Hostile;
	}

	return ETeamAttitude::Type::Neutral;
}

void ASPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASPAIController::OnTargetPerceptionUpdateHandler(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(EnemyBlackboardKey, Actor);	
	}
	else
	{
		GetBlackboardComponent()->ClearValue(EnemyBlackboardKey);	
	}
	UE_LOG(LogTemp, Error, TEXT("OnTargetPerceptionUpdateHandler"));
}

void ASPAIController::OnTargetPerceptionInfoUpdatedHandler(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Error, TEXT("OnTargetPerceptionInfoUpdatedHandler"));
}

void ASPAIController::OnPerceptionUpdatedHandler(const TArray<AActor*>& Actors)
{
	UE_LOG(LogTemp, Error, TEXT("OnPerceptionUpdatedHandler"));

}

void ASPAIController::InitializeCharacter()
{
	AICharacter = Cast<ASPAICharacter>(GetPawn());
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->GetBehaviourTree());
	}
}
