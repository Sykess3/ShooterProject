// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SPHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERPROJECT_API ASPHUD : public AHUD
{
	GENERATED_BODY()

	virtual void DrawHUD() override;

	void DrawCrosshair();
};
