// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSystem/ParentBuffDebuff.h"
#include "Character/StatsComponent.h"

// Sets default values
AParentBuffDebuff::AParentBuffDebuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParentBuffDebuff::BeginPlay()
{
	Super::BeginPlay();
	
	// Start the buff
	//StartBuff();
}

// Called every frame
void AParentBuffDebuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AParentBuffDebuff::SetupBuff(FString BuffName, int Potency, float Duration, float TickRate, FString StatTag)
//{
//}

void AParentBuffDebuff::StartBuff()
{
}

void AParentBuffDebuff::RefreshBuff()
{
}

void AParentBuffDebuff::BuffTickTimer()
{
}

void AParentBuffDebuff::EndBuff()
{
}

