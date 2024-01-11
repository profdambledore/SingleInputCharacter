// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputInventory.h"

// Sets default values for this component's properties
USingleInputInventory::USingleInputInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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

TArray<FItemData> USingleInputInventory::GetInventoryData()
{
	return InventoryItems;
}

void USingleInputInventory::AddItemToArray(FItemData NewItem)
{
	// Check if there is an index that has this item already in the array
	for (int i = 0; i < InventoryItems.Num(); i++) {
		if (InventoryItems[i].ID == NewItem.ID && NewItem.Amount > 0) {
			if (!InventoryItems[i].GetItemAtMaxStack()) {
				NewItem.Amount = InventoryItems[i].AddItems(NewItem);
				//UE_LOG(LogTemp, Warning, TEXT("sii : %i"), InventoryItems[i].Amount)
			}
		}
	}

	// If some amount still exists, create a new index with the NewItem data without an amount and recurse
	if (NewItem.Amount > 0) {
		InventoryItems.Add(FItemData(NewItem.ID, NewItem.Name, NewItem.Type, 0, NewItem.MaxStack, InventoryItems.Num()));
		AddItemToArray(NewItem);
	}
}

void USingleInputInventory::RemoveItemFromArray(FItemData ItemToRemove)
{
	// Check that the inventory holds enough of the item wanting to be removed
	int AmountInInvent = 0;

	for (int i = 0; i < InventoryItems.Num(); i++) {
		if (InventoryItems[i].ID == ItemToRemove.ID) {
			AmountInInvent = AmountInInvent + InventoryItems[i].Amount;
		}
	}

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

void USingleInputInventory::SortInventory(TEnumAsByte<EInventorySortType> SortBy)
{
	if (SortBy == EInventorySortType::Alphabetically) {
		InventorySort = SortBy;
		SortInventoryAlphabetically();
	}
}

void USingleInputInventory::ReSortInventory()
{
	SortInventory(InventorySort);
}

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
				else if (comparisonResult <= -1) {
					// Insert i after j
					SortedArray.Insert(i, j);
					break;
				}
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
	InventoryItems = SortedArray;
}

