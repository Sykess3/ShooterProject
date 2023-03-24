// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SPMonstersSpawnerActor.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASPAICharacter> AICharacterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASPAIController> AIControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(ClampMax = 100, ClampMin = 0))
	float Percent;
};

UCLASS()
class SHOOTERPROJECT_API ASPMonstersSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASPMonstersSpawnerActor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TArray<FMonsterSpawnData> MonstersData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	int32 OnStartMonsterCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float DelayBetweenSpawns;
private:
	FTimerHandle RespawnTimer;
	
	void SpawnMonsterInRandomLocation(const TSubclassOf<ASPAIController>& AIController, const TSubclassOf<ASPAICharacter>& AICharacter);
	void SpawnMonsterInRandomLocation();
	UFUNCTION()
	void AccrueKillAward(AActor* Killer, AActor* Victim);
	FMonsterSpawnData GetRandomMonsterSpawnData();
};
