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

FItemData::FItemData(FItemData InItemData, int InAmount, int InInventOrder)
{
	ID = InItemData.ID;
	Name = InItemData.Name;
	Type = InItemData.Type;
	MaxStack = InItemData.MaxStack;
	StaticMesh = InItemData.StaticMesh;
	SkelMesh = InItemData.SkelMesh;
	Icon = InItemData.Icon;

	Amount = InAmount;
	InventoryOrder = InInventOrder;
}

FItemData::~FItemData()
{
}

int FItemData::AddItems(FName NewItemID, int AmountToAdd)
{
	if (NewItemID == ID) {
		Amount = Amount + AmountToAdd;
		if (Amount > MaxStack && MaxStack != -1) {
			int ret = Amount - MaxStack;
			Amount = MaxStack;
			return ret;
		}
		return 0;
	}
	return AmountToAdd;
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
