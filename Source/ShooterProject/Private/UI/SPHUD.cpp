// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPHUD.h"
#include "Engine/Canvas.h"

void ASPHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void ASPHUD::DrawCrosshair()
{
	FVector2D Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;

	DrawLine(Center.X - HalfLineSize, Center.Y, Center.X + HalfLineSize,
	         Center.Y, FLinearColor::Green, LineThickness);
	DrawLine(Center.X, Center.Y - HalfLineSize, Center.X,
	         Center.Y + HalfLineSize, FLinearColor::Green, LineThickness);
}
