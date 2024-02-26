// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffSystem/ParentBuff.h"
#include "StatBuff.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API AStatBuff : public AParentBuff
{
	GENERATED_BODY()

public:
	// Called to setup the buff (used if the buff/debuff has multiple uses, such as consumables)
	void SetupBuff(FString NewBuffName, FString InStatTag, int InBaseStat, float InMultiplier, float InDuration);

	// Called to start the buff
	virtual void StartBuff() override;

	// Called to refresh the buff
	virtual void RefreshBuff() override;

	/// -- Buff Timers --
	// Timer function to end buff after a duration
	virtual void EndBuff() override;

protected:
	virtual void BeginPlay() override;

private:
	FString StatTag;
	int BaseStatIncrease;
	float Multiplier;
	float Duration;

	float TotalStatChange;

	FTimerHandle BuffTotalHandle;
	
};
