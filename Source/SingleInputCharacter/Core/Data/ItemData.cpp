// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/ItemData.h"

FItemData::FItemData()
{
}

FItemData::FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack)
{
	ID = InID;
	Name = InName;
	Type = InType;
	Amount = InAmount;
	MaxStack = InMaxStack;
}

FItemData::FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack, int InInventOrder)
{
	ID = InID;
	Name = InName;
	Type = InType;
	Amount = InAmount;
	MaxStack = InMaxStack;
	InventoryOrder = InInventOrder;
}

FItemData::~FItemData()
{
}

int FItemData::AddItems(FItemData ItemsToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("befre = %i"), Amount);
	if (ItemsToAdd.ID == ID) {
		Amount = Amount + ItemsToAdd.Amount;
		UE_LOG(LogTemp, Warning, TEXT("after = %i"), Amount);
		if (Amount > MaxStack) {
			int ret = Amount - MaxStack;
			Amount = MaxStack;
			return ret;
		}
		return 0;
	}
	return ItemsToAdd.Amount;
}

int FItemData::RemoveItems(int InAmount)
{
	Amount = Amount - InAmount;
	return Amount;
}

bool FItemData::GetItemAtMaxStack()
{
	if (Amount == MaxStack) {
		return true;
	}
	return false;
}
