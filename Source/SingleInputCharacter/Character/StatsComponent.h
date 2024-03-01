// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Data/ItemData.h"

#include "Kismet/GameplayStatics.h"

#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEINPUTCHARACTER_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// -- Stat Setup --
	// Called to setup the default stats
	void SetupStats(int InTeam);

	/// -- Stat Modification --
	// Called to make the unit take damage
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Amount, float InCritChance, float InCritMulti);

	// Called to calculate if an attack should crit or not
	UFUNCTION(BlueprintCallable)
	int CalculateCrit();

	// Called to heal the unit
	void HealUnit(int Amount);

	/// -- Buffs --
	// Called to begin a stat buff (or debuff if Potency is negative)
	void StartConsumableBuff(TEnumAsByte<EConsumableType> BuffType, FString StatTag, int BaseStat, float Multiplier, float Duration, float TickRate);

	// Called to add a buff to this StatsComponent
	void AddBuff(bool bBuff, class AParentBuffDebuff* Buff);

	// Called to remove a buff from the map
	void RemoveBuff(bool bBuff, FString Name);

	/// -- Getting Stats --
	// Called to get a stat based on a stat tag
	UFUNCTION(BlueprintCallable)
	float GetStatByTag(FString StatTag);

	// Called to return the team value
	int GetTeam();

	// Called to return the current health
	int GetCurrentHealth();

	// Called to return the max health
	int GetMaxHealth();

	/// -- Setting Stats --
	// Called to update a stat amount
	void UpdateStat(FString StatTag, float ModificationAmount);

	// Called to update combat stats when equipping or unequipping a weapon
	void UpdateCombatStatsFromWeapon(FWeaponData WeaponStats, bool bEquipping, UTexture2D* WeaponIcon, int CurrentAmmo);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/// -- Universal Stats --
	// Int denoting the owners team (-1 for destructable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int ObjectTeam;

	// Int denoting the object's current health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int CurrentHealth = -1;

	// Int denoting the object's max health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int MaxHealth = 200;

	// Int denoting the object's base defence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int Defence;

	// Int denoting the defence calculation value
	// Reaching this amount of defence will reduce damage by 50%, with reduced effeciveness past this
	int DefenceCalcValue = 200;

	/// -- Combat Stats --
	// Pointer to the unit's equipped weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	class AWeaponItem* EquippedWeapon = nullptr;

	// Int denoting the units damage 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	int Damage = 0;

	// Float denoting the units crit chance (chance to increase weapon damage) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float CritChance = 0.0f;

	// Float denoting the units crit damage (the amount to increase the base damage by when criting) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float CritDamage = 0.0f;

	// Float denoting the duration the unit takes to reach maximum accuracy 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float AccuracyChargeTime = 0.0f;

	// Float denoting the minimum (empty charge) accuracy angle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float MinAccuracy = 0.0f;

	// Float denoting the maximum (full charge) accuracy angle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float MaxAccuracy = 0.0f;

	// Int denoting the unit's maximum range (in uu)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	int Range = 0;

	// Float denoting the duration of time between each shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	float FireRate = 0.0f;

	// Bool denoting if the unit has infinite ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
	bool bInfiniteAmmo = false;

	/// -- Buffs/Debuffs --
	// TMap storing all timer handles related to buffs/debuffs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, class AParentBuffDebuff*> ActiveBuffMap;

	/// -- Player Specific --
	// Pointer to the PlayerUI owned by the player
	class USI_PlayerUI* PlayerUI = nullptr;
};
