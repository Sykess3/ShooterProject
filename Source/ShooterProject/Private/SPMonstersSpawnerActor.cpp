// Fill out your copyright notice in the Description page of Project Settings.


#include "SPMonstersSpawnerActor.h"

#include "AI/SPAIController.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ASPMonstersSpawnerActor::ASPMonstersSpawnerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Spawner");
}

void ASPMonstersSpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < OnStartMonsterCount; ++i)
	{
		SpawnMonsterInRandomLocation();
	}
	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASPMonstersSpawnerActor::SpawnMonsterInRandomLocation,
	                                DelayBetweenSpawns, true, DelayBetweenSpawns);
}

FMonsterSpawnData ASPMonstersSpawnerActor::GetRandomMonsterSpawnData()
{
	const float RandomValue = FMath::FRandRange(0.0f, 100.0f);
	float CurrentRandomValue = 0.0f;
	for (const auto Data : MonstersData)
	{
		CurrentRandomValue += Data.Percent;
		if (FMath::IsNearlyEqual(CurrentRandomValue, RandomValue) || CurrentRandomValue > RandomValue)
		{
			return Data;
		}
	}

	checkNoEntry();
	return {};
}

void ASPMonstersSpawnerActor::SpawnMonsterInRandomLocation()
{
	FMonsterSpawnData SpawnData = GetRandomMonsterSpawnData();
	SpawnMonsterInRandomLocation(SpawnData.AIControllerClass, SpawnData.AICharacterClass);
}

void ASPMonstersSpawnerActor::SpawnMonsterInRandomLocation(const TSubclassOf<ASPAIController>& AIController,
                                                           const TSubclassOf<ASPAICharacter>& AICharacter)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FBoxSphereBounds Bounds = BoxComponent->Bounds;
	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(Bounds.Origin, Bounds.BoxExtent);
	

	ASPAIController* Controller = GetWorld()->SpawnActor<ASPAIController>(AIController);
	ASPAICharacter* Character = GetWorld()->SpawnActor<ASPAICharacter>(AICharacter, Location, FRotator::ZeroRotator,
	                                                                   SpawnParameters);
	Controller->SetPawn(Character);
	Controller->Possess(Character);

	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
	Controller->AttachToComponent(Character->GetRootComponent(), AttachRules);
}
