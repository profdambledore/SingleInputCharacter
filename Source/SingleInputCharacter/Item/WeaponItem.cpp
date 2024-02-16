// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"

AWeaponItem::AWeaponItem()
{
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Item Mesh"));
}


void AWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemData.ItemID != "") {
		SetupItem(ItemData);
	}
}

void AWeaponItem::SetupItem(FItemData NewItemData)
{
	ItemData = NewItemData;
	AItemManager* FM = Cast<AItemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass()));
	if (FM) {
		ItemMesh->SetSkeletalMesh(FM->GetItemDataFromID<FItemConst>(ItemData.ItemID, EItemType::Item).SkelMesh);
		WeaponData = FM->GetWeaponDataFromID(ItemData.ItemID);
	}
}

float AWeaponItem::GetWeaponRange()
{
	return WeaponData.Range;
}

FName AWeaponItem::GetWeaponAmmoID()
{
	return WeaponData.AmmoID;
}

void AWeaponItem::FireWeapon(AActor* Target)
{
}
