// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSystem/Buff/Regen.h"
#include "Regen.h"

#include "Character/StatsComponent.h"

// Called when the game starts or when spawned
void ARegen::BeginPlay()
{
	Super::BeginPlay();
}

void ARegen::SetupBuff(FString NewBuffName, int InPotency, float InDuration, float InTickRate)
{
	BuffName = NewBuffName;
	Potency = InPotency;
	Duration = InDuration;
	TickRate = InTickRate;

	// Start the buff
	StartBuff();
}

void ARegen::StartBuff()
{
	// Setup two timers for this buff - the buff tick and the total buff duration
	GetWorld()->GetTimerManager().SetTimer(BuffTotalHandle, FTimerDelegate::CreateUObject(this, &ARegen::EndBuff), Duration, false, Duration);
	GetWorld()->GetTimerManager().SetTimer(BuffTickHandle, FTimerDelegate::CreateUObject(this, &ARegen::BuffTick), TickRate, true, TickRate);

	// Also add the buff to the AttacheeStatsComponent
	AttacheeStatsComponent->AddBuff(true, this);
}

void ARegen::RefreshBuff()
{
	// Clear the duration timer handle and restart the buff
	// If tick is wanted to be restarted too, call StartBuff again and clear both timer handles
	GetWorld()->GetTimerManager().ClearTimer(BuffTotalHandle);
	GetWorld()->GetTimerManager().SetTimer(BuffTotalHandle, FTimerDelegate::CreateUObject(this, &ARegen::EndBuff), 0.0f, false, Duration);
	
}

void ARegen::BuffTick()
{
	AttacheeStatsComponent->HealUnit(Potency);
}

void ARegen::EndBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Buff End"));

	// Clear the timer handles
	GetWorld()->GetTimerManager().ClearTimer(BuffTotalHandle);
	GetWorld()->GetTimerManager().ClearTimer(BuffTickHandle);

	// Remove this buff from the affectee's buff map
	AttacheeStatsComponent->RemoveBuff(true, BuffName);

	// Then destroy this actor
	Destroy();
}
