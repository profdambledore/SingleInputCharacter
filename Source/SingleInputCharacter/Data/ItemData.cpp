// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemData.h"

FItemConst::FItemConst()
{
}

FItemConst::~FItemConst()
{
}

FItemData::FItemData()
{
}

FItemData::~FItemData()
{
}

FItemData::FItemData(FName InItemID, FString InName, int InAmount, int InOrder)
{
	ItemID = InItemID;
	Name = InName;
	Amount = InAmount;
	Order = InOrder;
}

int FItemData::AddItems(FName NewItemID, int AmountToAdd, int MaxStack)
{
	// Add to the current amount
	Amount = Amount + AmountToAdd;
	// If, after adding, the current amount exceeds the current MaxStack and the MaxStack isn't infinite
	if (Amount > MaxStack && MaxStack != -1) {
		// Calculate the amount that cannot fit in this FItemData, then set Amount to the MaxStack and return the excees
		int ret = Amount - MaxStack;
		Amount = MaxStack;
		return ret;
	}
	// If they can all fit, just return 0
	return 0;
}

int FItemData::RemoveItems(int InAmount)
{
	// Remove the amount inputted from the argument then return the remaining amount
	Amount = Amount - InAmount;
	return Amount;
}

FInventoryTypeData::FInventoryTypeData()
{
}

FInventoryTypeData::~FInventoryTypeData()
{
}

FInventoryTypeData::FInventoryTypeData(TArray<FItemData> NewData)
{
	Items = NewData;
}
