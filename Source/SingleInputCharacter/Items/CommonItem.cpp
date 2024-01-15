// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CommonItem.h"

ACommonItem::ACommonItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	
}

void ACommonItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemData.ID != "") {
		SetupItem(ItemData);
	}
}

void ACommonItem::SetupItem(FItemData NewItemData)
{
	ItemData = NewItemData;
	ItemMesh->SetStaticMesh(ItemData.StaticMesh);
}

