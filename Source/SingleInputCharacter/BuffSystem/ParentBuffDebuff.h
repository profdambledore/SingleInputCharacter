// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentBuffDebuff.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AParentBuffDebuff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentBuffDebuff();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Buff Functions --
	

	// Called to start the buff
	virtual void StartBuff();

	// Called to refresh the buff
	virtual void RefreshBuff();

	/// -- Buff Timers --
	// Timer function to tick over time
	virtual void BuffTickTimer();

	// Timer function to end buff after a duration
	virtual void EndBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Buff Identifiers --
	// String denoting the buff/debuff's name
	FString BuffName;

	// The actor this buff is attached to
	//AActor* AttachedActor = nullptr;

	// The StatsComponent of the actor that is currently affected by this buff/debuff
	class UStatsComponent* AttacheeStatsComponent = nullptr;
};
