// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAccumulatedAwardChanged);

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void TakeAward(int32 Amount);
	UFUNCTION(BlueprintCallable)
	int32 GetAccumulatedAward() const;

	UPROPERTY(BlueprintAssignable)
	FOnAccumulatedAwardChanged OnAccumulatedAwardChanged;
private:
	int32 AccumulatedAward = 0;
};
