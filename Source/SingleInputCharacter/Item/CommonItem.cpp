// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CommonItem.h"


ACommonItem::ACommonItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));

}

void ACommonItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemData.ItemID != "") {
		SetupItem(ItemData);
	}
}

void ACommonItem::SetupItem(FItemData NewItemData)
{
	ItemData = NewItemData;
	AItemManager* FM = Cast<AItemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass()));
	if (FM) {
		ItemMesh->SetStaticMesh(FM->GetItemDataFromID<FItemConst>(ItemData.ItemID, EItemType::Item).StaticMesh);
	}
	
}