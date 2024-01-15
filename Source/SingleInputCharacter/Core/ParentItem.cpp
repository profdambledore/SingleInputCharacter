// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ParentItem.h"

// Sets default values
AParentItem::AParentItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AParentItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentItem::SetupItem(FItemData NewItemData)
{
}

void AParentItem::PickupItem()
{
	this->Destroy();
}

