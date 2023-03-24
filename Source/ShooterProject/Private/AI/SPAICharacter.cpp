// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAICharacter.h"

#include "AI/SPAIController.h"
#include "Components/SPHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASPAICharacter::ASPAICharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	AIControllerClass = ASPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

UBehaviorTree* ASPAICharacter::GetBehaviourTree() const
{
	return BehaviorTree;
}

int32 ASPAICharacter::GetAward() const
{
	return Award;
}


