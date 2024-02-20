// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/StatsComponent.h"

#include "UI/SI_PlayerUI.h"
#include "UI/SI_InGameState.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::SetupStats()
{
	if (CurrentHealth == -1) {
		CurrentHealth = MaxHealth;
		PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
}

void UStatsComponent::TakeDamage(int Amount)
{
	// Calculate the amount of damage the unit should take
	int IncomingDamage = Amount * (BaseDefence + BonusDefence / BaseDefence + BonusDefence + DefenceCalcValue);
	CurrentHealth -= IncomingDamage;

	// Check if the unit has lost all their health
	if (CurrentHealth > 0) {
		//Owner->Destroy();
	}

	// Finally, check if a InGameState pointer has been set.  If so, update the health bar
	if (PlayerUI) {
		PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
}

void UStatsComponent::HealUnit(int Amount)
{
	// Increase the units current health by the amount
	CurrentHealth += Amount;

	// If the current health now exceeds the MaxHealth, set CurrentHealth to MaxHealth
	if (CurrentHealth > MaxHealth) {
		CurrentHealth = MaxHealth;
	}
}

int UStatsComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int UStatsComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UStatsComponent::GetUnitDamageMultiplier()
{
	return 0.0f;
}

int UStatsComponent::GetUnitBonusDamage()
{
	return 0;
}

