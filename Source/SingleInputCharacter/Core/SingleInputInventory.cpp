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
				UE_LOG(LogTemp, Warning, TEXT("sii : %i"), InventoryItems[i].Amount)
			}
		}
	}

	// If some amount still exists, create a new index with the NewItem data without an amount and recurse
	if (NewItem.Amount > 0) {
		InventoryItems.Add(FItemData(NewItem.ID, NewItem.Name, NewItem.Type, 0, NewItem.MaxStack));
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

