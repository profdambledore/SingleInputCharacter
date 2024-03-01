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
		WeaponIcon = FM->GetItemDataFromID<FItemConst>(ItemData.ItemID, EItemType::Item).Icon;
		WeaponData = FM->GetWeaponDataFromID(ItemData.ItemID);
	}
}

void AWeaponItem::ClearWeapon()
{
	ItemMesh->SetSkeletalMesh(nullptr);
	WeaponData = FWeaponData();;
}

float AWeaponItem::GetWeaponRange()
{
	return WeaponData.Range;
}

FName AWeaponItem::GetWeaponAmmoID()
{
	return WeaponData.AmmoID;
}

void AWeaponItem::StartFireRateCooldown()
{
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, FTimerDelegate::CreateUObject(this, &AWeaponItem::EndFireRateCooldown), WeaponData.FireRate / 60, false, WeaponData.FireRate / 60);
}

void AWeaponItem::EndFireRateCooldown()
{
	bCanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(FireRateHandle);
}

void AWeaponItem::StartAccuracyIncrease()
{
	// Calculate the accuracy per tick
	AccuracyPerTick = (WeaponData.MinAccuracy - WeaponData.MaxAccuracy) / 0.5f;
	CurrentAccuracy = WeaponData.MinAccuracy;
	GetWorld()->GetTimerManager().SetTimer(AccuracyHandle, FTimerDelegate::CreateUObject(this, &AWeaponItem::AccuracyIncreaseTick), 0.5f, true, 0.5f);
}

void AWeaponItem::PauseAccuracyIncrease()
{
	GetWorld()->GetTimerManager().PauseTimer(AccuracyHandle);
}

void AWeaponItem::EndAccuracyIncrease()
{
	GetWorld()->GetTimerManager().ClearTimer(AccuracyHandle);
}

void AWeaponItem::AccuracyIncreaseTick()
{
	CurrentAccuracy += AccuracyPerTick;
	if (CurrentAccuracy == WeaponData.MaxAccuracy) {
		EndAccuracyIncrease();
	}
}

float AWeaponItem::GetCurrentAccuracy()
{
	return CurrentAccuracy;
}

void AWeaponItem::FireWeapon(AActor* Target)
{
}
