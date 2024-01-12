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
void USingleInputInventory::RemoveItemFromArray(FItemData ItemToRemove)
{
	// Check that the inventory holds enough of the item wanting to be removed
	int AmountInInvent = 0;

	for (int i = 0; i < InventoryItems.Num(); i++) {
		if (InventoryItems[i].ID == ItemToRemove.ID) {
			AmountInInvent = AmountInInvent + InventoryItems[i].Amount;
		}
	}

	// If there is enough to remove, then iterate over the array finding all matching IDs
	// Remove amounts of items from each ID until either enough is removed or that index is now empty
	// On index empty, remove it from the array
	if (AmountInInvent >= ItemToRemove.Amount) {
		for (int i = 0; i < InventoryItems.Num(); i++) {
			if (InventoryItems[i].ID == ItemToRemove.ID && ItemToRemove.Amount > 0) {
				ItemToRemove.Amount = InventoryItems[i].RemoveItems(ItemToRemove.Amount);
				if (ItemToRemove.Amount <= 0) {
					InventoryItems.RemoveAt(i);
					i--;
					ItemToRemove.Amount = ItemToRemove.Amount * -1;
				}
			}
		}
	}
}

// Called to sort the inventory by an inputted way
void USingleInputInventory::SortInventory(TEnumAsByte<EInventorySortType> SortBy)
{
	// If the inputted sort is Alphabetically, then call SortInventoryAlphabetically
	if (SortBy == EInventorySortType::Alphabetically) {
		InventorySort = SortBy;
		SortInventoryAlphabetically();
	}
	// Or by Newest
	else if (SortBy == EInventorySortType::Newest) {
		InventorySort = SortBy;
		SortInventoryNewest();
	}
	// Or by Oldest
	else if (SortBy == EInventorySortType::Oldest) {
		InventorySort = SortBy;
		SortInventoryOldest();
	}
}

// Called to resort the inventory by the current type
void USingleInputInventory::ReSortInventory()
{
	// Simply sort the inventory with the current setting
	SortInventory(InventorySort);
}

// Called to sort the inventory in alphabetical order
void USingleInputInventory::SortInventoryAlphabetically()
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
	InventoryItems = SortedArray;
}

// Called to sort the inventory by newest item first
void USingleInputInventory::SortInventoryNewest()
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
	InventoryItems = SortedArray;
}

// Called to sort the inventory by oldest item first
void USingleInputInventory::SortInventoryOldest()
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
	InventoryItems = SortedArray;
}

