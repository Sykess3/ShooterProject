// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPCharacter.h"
#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"
#include "Components/TextRenderComponent.h"

ASPCharacter::ASPCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WeaponComponent = CreateDefaultSubobject<USPWeaponComponent>("WeaponComponent");
	HealthComponent = CreateDefaultSubobject<USPHealthComponent>("HealthComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());
}

void ASPCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	HealthComponent->OnHealthChanged.AddUObject(this, &ASPCharacter::OnHealthChangedHandler);
}

void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ASPCharacter::OnHealthChangedHandler(float Amount)
{
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Amount)));
}
