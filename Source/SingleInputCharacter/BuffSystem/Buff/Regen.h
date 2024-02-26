// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffSystem/ParentBuff.h"
#include "Regen.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ARegen : public AParentBuff
{
	GENERATED_BODY()
	
public:
	// Called to setup the buff (used if the buff/debuff has multiple uses, such as consumables)
	void SetupBuff(FString NewBuffName, int InPotency, float InDuration, float InTickRate);

	// Called to start the buff
	virtual void StartBuff() override;

	// Called to refresh the buff
	virtual void RefreshBuff() override;

	/// -- Buff Timers --
	// Timer function to tick over time
	virtual void BuffTick();

	// Timer function to end buff after a duration
	virtual void EndBuff() override;

protected:
	virtual void BeginPlay() override;

private:
	int Potency;
	float Duration;
	float TickRate;

	FTimerHandle BuffTickHandle;
	FTimerHandle BuffTotalHandle;
};
