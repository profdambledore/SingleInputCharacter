// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/StatsComponent.h"

#include "UI/SI_PlayerUI.h"
#include "UI/SI_InGameState.h"
#include "BuffSystem/ParentBuffDebuff.h"
#include "BuffSystem/Buff/Regen.h"
#include "BuffSystem/Buff/StatBuff.h"
#include "Item/WeaponItem.h"

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

void UStatsComponent::SetupStats(int InTeam)
{
	ObjectTeam = InTeam;

	if (CurrentHealth == -1) {
		CurrentHealth = MaxHealth / 2;
		if (PlayerUI) {
			PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
		}
	}
}

void UStatsComponent::TakeDamage(int Amount, float InCritChance, float InCritMulti)
{
	bool bHasCrit = false;
	int IncomingDamage;

	if (FMath::RandRange(0.0f, 1.0f) <= CritChance) {
		IncomingDamage = Amount * CritDamage;
	}

	// Calculate the amount of damage the unit should take
	CurrentHealth -= IncomingDamage * (1.0f - (Defence / (Defence + DefenceCalcValue)));

	// Check if the unit has lost all their health
	if (CurrentHealth < 0) {
		GetOwner()->Destroy();
	}

	// Finally, check if a InGameState pointer has been set.  If so, update the health bar
	if (PlayerUI) {
		PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
}

int UStatsComponent::CalculateCrit()
{
	if (FMath::RandRange(0.0f, 1.0f) <= CritChance) {
		return Damage * CritDamage;
	}
	return Damage;
}

void UStatsComponent::HealUnit(int Amount)
{
	// Increase the units current health by the amount
	CurrentHealth += Amount;

	// If the current health now exceeds the MaxHealth, set CurrentHealth to MaxHealth
	if (CurrentHealth > MaxHealth) {
		CurrentHealth = MaxHealth;
	}

	// If a players StatsComponent, update their health bar
	if (PlayerUI) {
		PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
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
			Cast<AStatBuff>(ActiveBuffMap.FindRef("StatBuff" + StatTag))->SetupReBuff(BaseStat, Multiplier, Duration);
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
		return Defence;
	}
	else if (StatTag == "Damage") {
		return Damage;
	}
	else if (StatTag == "CritChance") {
		return CritChance;
	}
	else if (StatTag == "CritDamage") {
		return CritDamage;
	}
	else if (StatTag == "AccuracyChargeTime") {
		return AccuracyChargeTime;
	}
	else if (StatTag == "MinAccuracy") {
		return MinAccuracy;
	}
	else if (StatTag == "MaxAccuracy") {
		return MaxAccuracy;
	}
	else if (StatTag == "Range") {
		return Range;
	}
	else if (StatTag == "FireRate") {
		return FireRate;
	}
	return 0.0f;
}

int UStatsComponent::GetTeam()
{
	return ObjectTeam;
}

int UStatsComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int UStatsComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UStatsComponent::UpdateStat(FString StatTag, float ModificationAmount)
{
	if (StatTag == "Health") {
		MaxHealth += ModificationAmount;
		// If a players StatsComponent, update their health bar
		if (PlayerUI) {
			PlayerUI->InGameState->UpdateHealthBar(CurrentHealth, MaxHealth);
		}

	}
	else if (StatTag == "Armour") {
		Defence += ModificationAmount;
	}
	else if (StatTag == "Damage") {
		Defence += ModificationAmount;
	}
	else if (StatTag == "CritChance") {
		CritChance += ModificationAmount;
	}
	else if (StatTag == "CritDamage") {
		CritDamage += ModificationAmount;
	}
	else if (StatTag == "AccuracyChargeTime") {
		AccuracyChargeTime += ModificationAmount;
	}
	else if (StatTag == "MinAccuracy") {
		MinAccuracy += ModificationAmount;
	}
	else if (StatTag == "MaxAccuracy") {
		MaxAccuracy += ModificationAmount;
	}
	else if (StatTag == "Range") {
		Range += ModificationAmount;
	}
	else if (StatTag == "FireRate") {
		Defence += ModificationAmount;
	}
}

void UStatsComponent::UpdateCombatStatsFromWeapon(FWeaponData WeaponStats, bool bEquipping, UTexture2D* WeaponIcon, int CurrentAmmo)
{
	// Set if we should increase or decrease the stats
	int Multiply = 1;
	if (!bEquipping) {
		Multiply = -1;
	}

	// Then modify the stats
	Damage += WeaponStats.Damage * Multiply;
	CritChance += WeaponStats.CritChance * Multiply;
	CritDamage += WeaponStats.CritDamage * Multiply;
	AccuracyChargeTime += WeaponStats.AccuracyChargeTime * Multiply;
	MinAccuracy += WeaponStats.MinAccuracy * Multiply;
	MaxAccuracy += WeaponStats.MaxAccuracy * Multiply;
	Range += WeaponStats.Range * Multiply;
	FireRate += WeaponStats.FireRate * Multiply;

	// Also, update the weapon icon and ammo amount
	PlayerUI->InGameState->UpdateWeaponSlot(WeaponIcon);
	PlayerUI->InGameState->UpdateAmmoCount(CurrentAmmo);
}

