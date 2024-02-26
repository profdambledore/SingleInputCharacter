// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/StatsComponent.h"

#include "UI/SI_PlayerUI.h"
#include "UI/SI_InGameState.h"
#include "BuffSystem/ParentBuffDebuff.h"
#include "BuffSystem/Buff/Regen.h"
#include "BuffSystem/Buff/StatBuff.h"

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
		CurrentHealth = MaxHealth / 2;
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

	PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
}

void UStatsComponent::StartConsumableBuff(TEnumAsByte<EConsumableType> BuffType, FString StatTag, int BaseStat, float Multiplier, float Duration, float TickRate)
{
	if (BuffType == Healing) {
		HealUnit(BaseStat);
	}
	else if (BuffType == Regen) {
		// Check if a Regen buff is currently active.
		if (ActiveBuffMap.Find("Regen")) {
			// If so, update that buff object with the new stats and refresh
			Cast<ARegen>(ActiveBuffMap.FindRef("Regen"))->SetupBuff("Regen", BaseStat, Duration, TickRate);
		}
		else {
			// Create a ARegen object, attach it to the owner of this component, then setup its stats
			class ARegen* Buff_Regen = GetWorld()->SpawnActorDeferred<ARegen>(ARegen::StaticClass(), FTransform());
			if (Buff_Regen) {
				Buff_Regen->AttacheeStatsComponent = this;
				UGameplayStatics::FinishSpawningActor(Buff_Regen, FTransform());
			}
			Buff_Regen->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale, "");
			Buff_Regen->SetupBuff("Regen", BaseStat, Duration, TickRate);
		}
	}
	else if (BuffType == StatBuff) {
		// Check if a StatBuff matching the new buff's type is active
		if (ActiveBuffMap.Find("StatBuff" + StatTag)) {
			// If so, update that buff object
			Cast<AStatBuff>(ActiveBuffMap.FindRef("StatBuff" + StatTag))->SetupBuff("StatBuff", StatTag, BaseStat, Multiplier, Duration);
		}
		else {
			// Create a AStatBuff object, attach it to the owner of this component, then setup its stats
			class AStatBuff* Buff_StatBuff = GetWorld()->SpawnActorDeferred<AStatBuff>(AStatBuff::StaticClass(), FTransform());
			if (Buff_StatBuff) {
				Buff_StatBuff->AttacheeStatsComponent = this;
				UGameplayStatics::FinishSpawningActor(Buff_StatBuff, FTransform());
			}
			Buff_StatBuff->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale, "");
			Buff_StatBuff->SetupBuff("StatBuff", StatTag, BaseStat, Multiplier, Duration);
		}
	}
}

void UStatsComponent::AddBuff(bool bBuff, AParentBuffDebuff* Buff)
{
	if (bBuff) {
		ActiveBuffMap.Add(Buff->BuffName, Buff);
	}
}

void UStatsComponent::RemoveBuff(bool bBuff, FString Name)
{
	if (bBuff) {
		ActiveBuffMap.Remove(Name);
	}
}

float UStatsComponent::GetStatByTag(FString StatTag)
{
	if (StatTag == "Health") {
		return MaxHealth;
	}
	else if (StatTag == "Armour") {
		return BaseDefence;
	}
	return 0.0f;
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

void UStatsComponent::UpdateStat(FString StatTag, float ModificationAmount)
{
	if (StatTag == "Health") {
		MaxHealth += ModificationAmount;
		PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);

	}
	else if (StatTag == "Armour") {
		BaseDefence += ModificationAmount;
	}
}

