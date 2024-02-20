// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	void SetupStats();

	/// -- Stat Modification --
	// Called to make the unit take damage
	void TakeDamage(int Amount);

	// Called to heal the unit
	void HealUnit(int Amount);

	/// -- Getting Stats --
	// Called to return the current health
	int GetCurrentHealth();

	// Called to return the max health
	int GetMaxHealth();

	// Called to return the damage multiplier
	float GetUnitDamageMultiplier();

	// Called to return the base damage increase
	int GetUnitBonusDamage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/// -- Universal Stats --
	// Int denoting the object's current health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int CurrentHealth = -1;

	// Int denoting the object's max health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int MaxHealth = 200;

	// Int denoting the object's base defence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int BaseDefence;

	// Int denoting the object's defence bonus
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int BonusDefence = 0;

	// Int denoting the defence calculation value
	// Reaching this amount of defence will reduce damage by 50%, with reduced effeciveness past this
	int DefenceCalcValue = 200;

	// Int denoting the current damage multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	float DamageMulti = 1.0f;

	// Int denoting the units bonus damage 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universal Stats")
	int BonusDamage = 0;

	/// -- Player Specific --
	// Pointer to the PlayerUI owned by the player
	class USI_PlayerUI* PlayerUI = nullptr;
};
