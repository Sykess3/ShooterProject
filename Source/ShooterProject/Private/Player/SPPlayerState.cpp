// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerState.h"

void ASPPlayerState::TakeAward(int32 Amount)
{
	AccumulatedAward += Amount;
	OnAccumulatedAwardChanged.Broadcast();
}

int32 ASPPlayerState::GetAccumulatedAward() const
{
	return AccumulatedAward;
}
