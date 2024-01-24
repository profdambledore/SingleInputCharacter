// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputInventory.h"

// Sets default values for this component's properties
USingleInputInventory::USingleInputInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Get a reference to the item data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Items/DT_ItemData"));
	if (DTObject.Succeeded()) { ItemDataTable = DTObject.Object; }
}


// Called when the game starts
void USingleInputInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USingleInputInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called to return an array of all items in the inventory
TArray<FItemData> USingleInputInventory::GetInventoryData()
{
	return InventoryItems;
}

// Called to get the data of an item from the data table
FItemData USingleInputInventory::FindItemData(FName ItemID)
{
	FItemData* FoundItem = ItemDataTable->FindRow<FItemData>(ItemID, "", true);
	return *FoundItem;
}

// Called to add an item to the inventory
void USingleInputInventory::AddItemToArray(FName NewItemID, int Amount)
{
	// Check if there is an index that has this item already in the array
	for (int i = 0; i < InventoryItems.Num(); i++) {
		if (InventoryItems[i].ID == NewItemID && Amount > 0) {
			if (!InventoryItems[i].GetItemAtMaxStack()) {
				Amount = InventoryItems[i].AddItems(NewItemID, Amount);
			}
		}
	}

	// If some amount still exists, create a new index with the NewItem data without an amount and recurse
	if (Amount > 0) {
		
		InventoryItems.Add(FItemData(FindItemData(NewItemID), 0, InventoryOrder));
		InventoryOrder++;
		AddItemToArray(NewItemID, Amount);
	}
}

// Called to remove an item from the inventory
void USingleInputInventory::RemoveItemFromArray(FName NewItemID, int Amount)
{
	// Check that the inventory holds enough of the item wanting to be removed
	int AmountInInvent = 0;

	for (int i = 0; i < InventoryItems.Num(); i++) {
		if (InventoryItems[i].ID == NewItemID) {
			AmountInInvent = AmountInInvent + InventoryItems[i].Amount;
		}
	}

	// If there is enough to remove, then iterate over the array finding all matching IDs
	// Remove amounts of items from each ID until either enough is removed or that index is now empty
	// On index empty, remove it from the array
	if (AmountInInvent >= Amount) {
		for (int i = 0; i < InventoryItems.Num(); i++) {
			if (InventoryItems[i].ID == NewItemID && Amount > 0) {
				Amount = InventoryItems[i].RemoveItems(Amount);
				if (Amount <= 0) {
					InventoryItems.RemoveAt(i);
					i--;
					Amount = Amount * -1;
				}
			}
		}
	}
}

// Called to return the inventory's data, sorted by an inputted way
TArray<FItemData> USingleInputInventory::SortInventory()
{
	// If the inputted sort is Alphabetically, then call SortInventoryAlphabetically
	if (InventorySort == EInventorySortType::Alphabetically) {
		return SortInventoryAlphabetically();
	}
	// Or by Newest
	else if (InventorySort == EInventorySortType::Newest) {
		return SortInventoryNewest();
	}
	// Or by Oldest
	else if (InventorySort == EInventorySortType::Oldest) {
		return SortInventoryOldest();
	}
	return InventoryItems;
}

// DEPRECTE - Called to resort the inventory by the current type
void USingleInputInventory::ReSortInventory()
{
	// Simply sort the inventory with the current setting
	//SortInventory(InventorySort);
}

// Called to sort the inventory in alphabetical order
TArray<FItemData> USingleInputInventory::SortInventoryAlphabetically()
{
	TArray<FItemData> SortedArray;

	// For each item in the player's inventory
	for (FItemData i : InventoryItems) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the strings
			for (int j = 0; j < SortedArray.Num(); j++) {
				int comparisonResult = i.Name.Compare(SortedArray[j].Name, ESearchCase::IgnoreCase);
				UE_LOG(LogTemp, Warning, TEXT("result is %i"), comparisonResult);

				// If they are the same
				if (comparisonResult == 0) {
					// Insert i after j
					SortedArray.Insert(i, j+ 1);
					UE_LOG(LogTemp, Warning, TEXT("adding %s"), *i.Name);
					break;
				}
				// If they are less (i is earlier on in the alphabet)
				else if (comparisonResult <= -1) {
					// Insert i after j
					SortedArray.Insert(i, j);
					break;
				}
				// If they are lated (i is later on in the alphabet)
				else if (comparisonResult >= 1) {
					if (j + 1 >= SortedArray.Num()) {
						// Insert i at the end of the array
						SortedArray.Insert(i, SortedArray.Num());
						break;
					}
					continue;
				}
			}
		}
	}

	// Update the inventory with the new sorted items
	return SortedArray;
}

// Called to sort the inventory by newest item first
TArray<FItemData> USingleInputInventory::SortInventoryNewest()
{
	TArray<FItemData> SortedArray;

	// For each item in the player's inventory
	for (FItemData i : InventoryItems) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the InventoryOrder
			for (int j = 0; j < SortedArray.Num(); j++) {
				// If they are less (i is earlier on in the alphabet)
				if (i.InventoryOrder <= SortedArray[j].InventoryOrder) {
					// Insert i after j
					SortedArray.Insert(i, j);
					break;
				}
				// If they are lated (i is later on in the alphabet)
				else {
					if (j + 1 >= SortedArray.Num()) {
						// Insert i at the end of the array
						SortedArray.Insert(i, SortedArray.Num());
						break;
					}
					continue;
				}
			}
		}
	}
	// Update the inventory with the new sorted items
	Algo::Reverse(SortedArray);
	return SortedArray;
}

// Called to sort the inventory by oldest item first
TArray<FItemData> USingleInputInventory::SortInventoryOldest()
{
	TArray<FItemData> SortedArray;

	// For each item in the player's inventory
	for (FItemData i : InventoryItems) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the InventoryOrder
			for (int j = 0; j < SortedArray.Num(); j++) {
				// If they are less (i is earlier on in the alphabet)
				if (i.InventoryOrder <= SortedArray[j].InventoryOrder) {
					// Insert i after j
					SortedArray.Insert(i, j);
					break;
				}
				// If they are lated (i is later on in the alphabet)
				else {
					if (j + 1 >= SortedArray.Num()) {
						// Insert i at the end of the array
						SortedArray.Insert(i, SortedArray.Num());
						break;
					}
					continue;
				}
			}
		}
	}
	// Update the inventory with the new sorted items
	return SortedArray;
}

bool USingleInputInventory::GetItemsExistInInventory(TArray<FCraftingItemData> Items)
{
	if (InventoryItems.IsEmpty() == false) {
		for (FCraftingItemData i : Items) {
			for (FItemData j : InventoryItems) {
				if (i.ID == j.ID) {
					i.Amount -= j.Amount;
					UE_LOG(LogTemp, Warning, TEXT("Id = %s / Amount remaining = %i"), *i.ID.ToString(), i.Amount);
					if (i.Amount <= 0) {
						UE_LOG(LogTemp, Warning, TEXT("eno"));
						break;
					}
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Check before next item: Id = %s / Amount remaining = %i"), *i.ID.ToString(), i.Amount);
			if (i.Amount > 0) {
				UE_LOG(LogTemp, Warning, TEXT("not eno"));
				return false;
			}
		}
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("not exist"));
	return false;
}