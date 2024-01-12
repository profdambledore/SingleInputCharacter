// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/ItemData.h"

/// -- Constructors --
// Default Constructor
FItemData::FItemData()
{
}

// Constructor used to directly set the data stats
FItemData::FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack)
{
	ID = InID;
	Name = InName;
	Type = InType;
	Amount = InAmount;
	MaxStack = InMaxStack;
}

// Constructor to set the data stats from an existing FItemData, alongside a new amount and inventory order
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

// Default Destructor
FItemData::~FItemData()
{
}

// Called to add items to an existing FItemData
int FItemData::AddItems(FName NewItemID, int AmountToAdd)
{
	// Check if the new ID matches the current ID
	if (NewItemID == ID) {
		// If so, add to the current amount
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
	// If they don't match, just return the full amount
	return AmountToAdd;
}

// Called to remove items from an existing FItemData
int FItemData::RemoveItems(int InAmount)
{
	// Remove the amount inputted from the argument then return the remaining amount
	Amount = Amount - InAmount;
	return Amount;
}

// Called to check if an existing FItemData's Amount is at its MaxStack
bool FItemData::GetItemAtMaxStack()
{
	if (Amount == MaxStack) {
		return true;
	}
	return false;
}
