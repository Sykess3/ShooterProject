// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPAICharacter.h"
#include "SPAIController.generated.h"

struct FActorPerceptionUpdateInfo;
struct FAIStimulus;
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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="AI")
	FName EnemyBlackboardKey;
	UPROPERTY()
	ASPAICharacter* AICharacter;

	UFUNCTION()
	void OnTargetPerceptionUpdateHandler(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnTargetPerceptionInfoUpdatedHandler(const FActorPerceptionUpdateInfo& UpdateInfo);
	UFUNCTION()
	void OnPerceptionUpdatedHandler(const TArray<AActor*>& Actors);
private:
	UFUNCTION()
	void InitializeCharacter();
};
