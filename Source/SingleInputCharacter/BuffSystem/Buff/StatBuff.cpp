// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSystem/Buff/StatBuff.h"

#include "Character/StatsComponent.h"

void AStatBuff::BeginPlay()
{
	Super::BeginPlay();
}

void AStatBuff::SetupBuff(FString NewBuffName, FString InStatTag, int InBaseStat, float InMultiplier, float InDuration)
{
	BuffName = NewBuffName + InStatTag;
	StatTag = InStatTag;
	BaseStatIncrease = InBaseStat;
	Multiplier = InMultiplier;
	Duration = InDuration;

	// Start the buff
	StartBuff();
}

void AStatBuff::SetupReBuff(int InBaseStat, float InMultiplier, float InDuration)
{
	// Undo the stat changes
	AttacheeStatsComponent->UpdateStat(StatTag, TotalStatChange * -1);

	BaseStatIncrease = InBaseStat;
	Multiplier = InMultiplier;
	Duration = InDuration;

	// Start the buff
	StartBuff();
}

void AStatBuff::StartBuff()
{
	GetWorld()->GetTimerManager().SetTimer(BuffTotalHandle, FTimerDelegate::CreateUObject(this, &AStatBuff::EndBuff), Duration, false, Duration);

	// Also add the buff to the AttacheeStatsComponent
	AttacheeStatsComponent->AddBuff(true, this);

	// Finally, update the Attachee's stats
	// Calculate the total stat change
	float StatBeforeBuff = AttacheeStatsComponent->GetStatByTag(StatTag);
	TotalStatChange = BaseStatIncrease + (StatBeforeBuff * Multiplier);

	// Then set it
	AttacheeStatsComponent->UpdateStat(StatTag, TotalStatChange);
}

void AStatBuff::RefreshBuff()
{
	// Clear the duration timer handle and restart the buff
	// If tick is wanted to be restarted too, call StartBuff again and clear both timer handles
	GetWorld()->GetTimerManager().ClearTimer(BuffTotalHandle);
	GetWorld()->GetTimerManager().SetTimer(BuffTotalHandle, FTimerDelegate::CreateUObject(this, &AStatBuff::EndBuff), Duration, false, Duration);
}

void AStatBuff::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Stat Buff End"));

	// Clear the timer handles
	GetWorld()->GetTimerManager().ClearTimer(BuffTotalHandle);

	// Remove this buff from the affectee's buff map
	AttacheeStatsComponent->RemoveBuff(true, BuffName);

	// Undo the stat changes
	AttacheeStatsComponent->UpdateStat(StatTag, TotalStatChange * -1);

	// Then destroy this actor
	Destroy();
}