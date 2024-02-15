// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ParentCraftingStation.h"

// Sets default values
AParentCraftingStation::AParentCraftingStation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Station Mesh"));
}

// Called when the game starts or when spawned
void AParentCraftingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentCraftingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

