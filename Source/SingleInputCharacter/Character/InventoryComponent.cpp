// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InventoryComponent.h"
#include "Core/SI_PlayerCharacter.h"
#include "Character/StatsComponent.h"
#include "Item/ItemManager.h"
#include "UI/SI_PlayerUI.h"
#include "UI/SI_InGameState.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find the ItemManager in the world and store a pointer to it
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass());
	if (FoundActor) {
		ItemManager = Cast<AItemManager>(FoundActor);
	}

	// Initalize the inventory map with empty arrays if the array doesn't already exist
	for (EItemType i : TEnumRange<EItemType>()) {
		if (!Inventory.Contains(i)) {
			Inventory.Add(i, TArray<FItemData>());
		}
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SetCurrentAmmoType(FName InItemID)
{
	if (InItemID != "") {
		AmmoID = InItemID;
	}
	else {
		AmmoID = "";
	}
}

TArray<FItemData> UInventoryComponent::GetAllInventoryItems()
{
	// Make an array that combines all of the TMap Inventory arrays together and return
	TArray<FItemData> CombinedInventory;
	TArray<FInventoryTypeData> InventoryTypes; Inventory.GenerateValueArray(InventoryTypes);
	for (FInventoryTypeData i : InventoryTypes) {
		CombinedInventory += i.Items;
	}

	return CombinedInventory;
}

TArray<FItemData> UInventoryComponent::GetInventoryItemsOfType(TEnumAsByte<EItemType> Type)
{
	return Inventory.Find(Type)->Items;
}

void UInventoryComponent::AddItemToInventory(FName InItemID, int InAmount)
{
	// Check if the ItemManager pointer has been set
	if (ItemManager) {
		// Get the item data from the manager
		FItemConst NewItem = ItemManager->GetItemDataFromID<FItemConst>(InItemID, EItemType::Item);

		// Get the TMap array that matches this items type
		TArray<FItemData> Items = Inventory.Find(NewItem.Type)->Items;

		while (InAmount > 0) {
			UE_LOG(LogTemp, Warning, TEXT("%i"), InAmount);
			// Check if there is an index that has this item already in the array
			for (int i = 0; i < Items.Num(); i++) {
				if (Items[i].ItemID == InItemID && InAmount > 0) {
					if (Items[i].Amount != NewItem.MaxStack) {
						InAmount = Items[i].AddItems(InItemID, InAmount, NewItem.MaxStack);
					}
				}
			}
			// If some amount still exists, create a new index with the NewItem data without an amount and recurse
			if (InAmount > 0) {
				Items.Add(FItemData(InItemID, NewItem.Name, 0, InventoryOrder));
				InventoryOrder++;
				UE_LOG(LogTemp, Warning, TEXT("Added New Index"));
			}
		}

		// Add the array back to the map in the correct key
		Inventory.Add(NewItem.Type, FInventoryTypeData(Items));

		// Finally, check if the new item was the same item used as the current weapon
		if (InItemID == AmmoID && PlayerUI) {
			PlayerUI->InGameState->UpdateAmmoCount(GetAmountOfItem(AmmoID));
		}
	}
}

void UInventoryComponent::RemoveItemFromInventory(FName InItemID, int Amount)
{
	// Check if the ItemManager pointer has been set
	if (ItemManager) {
		// Get the item data from the manager
		FItemConst NewItem = ItemManager->GetItemDataFromID<FItemConst>(InItemID, EItemType::Item);

		// Get the TMap array that matches this items type
		TArray<FItemData> Items = Inventory.Find(NewItem.Type)->Items;

		// Check that the inventory holds enough of the item wanting to be removed
		int AmountInInvent = 0;

		for (int i = 0; i < Items.Num(); i++) {
			if (Items[i].ItemID == InItemID) {
				AmountInInvent = AmountInInvent + Items[i].Amount;
			}
		}

		ASI_PlayerCharacter* PlayerPointer = nullptr;
		// Check if the item is a Weapon (or it is equipable)
		if (NewItem.Type == Weapon) {
			// Check if the owner of the inventory is a Player
			if (InventoryOwner->IsA(ASI_PlayerCharacter::StaticClass())) {
				// Cast to the player class (do it now, just incase the player ownes multiple weapons)
				// Changes cast amount from n=AmountOfWeapons to n=1
				PlayerPointer = Cast<ASI_PlayerCharacter>(InventoryOwner);
			}
		}

		// If there is enough to remove, then iterate over the array finding all matching IDs
		// Remove amounts of items from each ID until either enough is removed or that index is now empty
		// On index empty, remove it from the array
		if (AmountInInvent >= Amount) {
			for (int i = 0; i < Items.Num(); i++) {
				if (Items[i].ItemID == InItemID && Amount > 0) {
					// Check if the item is currently equipped
					if (PlayerPointer) {
						// If it is, unequip the weapon
						if (PlayerPointer->EquippedWeaponOrder == Items[i].Order) {
							PlayerPointer->UnequipWeapon();
						}
					}
					Amount = Items[i].RemoveItems(Amount);
					if (Amount <= 0) {
						Items.RemoveAt(i);
						i--;
						Amount = Amount * -1;
					}
				}
			}
		}

		// Add the array back to the map in the correct key
		Inventory.Add(NewItem.Type, FInventoryTypeData(Items));

		// Finally, check if the item was the same item used as the current weapon
		if (InItemID == AmmoID && PlayerUI) {
			PlayerUI->InGameState->UpdateAmmoCount(GetAmountOfItem(AmmoID));
		}
	}
}

void UInventoryComponent::UseItem(int Order)
{
	// Check if the selected item is a weapon.  If so, equip it
	FItemData Item = GetItemAtInventoryOrder(Order);
	if (Item.Order != -1) {
		FItemConst ItemCons = ItemManager->GetItemDataFromID<FItemConst>(Item.ItemID, EItemType::Item);
		if (ItemCons.Type == Weapon) {
			Cast<ASI_PlayerCharacter>(InventoryOwner)->EquipWeapon(Item);
		}
		else if (ItemCons.Type == Consumable) {
			if (StatsComponent) {
				FConsumableData ConsumCost = ItemManager->GetConsumableDataFromID(Item.ItemID);
				StatsComponent->StartConsumableBuff(ConsumCost.BuffType, ConsumCost.StatTag, ConsumCost.BaseStat, ConsumCost.Multiplier, ConsumCost.Duration, ConsumCost.TickRate);
				RemoveItemFromInventory(Item.ItemID, 1);
			}
		}
	}
}

int UInventoryComponent::GetAmountOfItem(FName InItemID)
{
	TArray<FItemData> ArrayToSearch = GetAllInventoryItems();
	int AmountFound = 0;

	if (ArrayToSearch.IsEmpty() == false) {
		for (FItemData j : ArrayToSearch) {
			if (j.ItemID == InItemID) {
				AmountFound += j.Amount;
			}
		}
	}
	return AmountFound;
}

TArray<FItemData> UInventoryComponent::SortInventoryAlphabetically(TEnumAsByte<EItemType> Type)
{
	if (Inventory.IsEmpty()) {
		return TArray<FItemData>();
	}

	TArray<FItemData> SortedArray;
	TArray<FItemData> ArrayToSort;

	// Get the items that require sorting
	if (Type == EItemType::Item) {
		ArrayToSort = GetAllInventoryItems();
	}
	else {
		ArrayToSort = GetInventoryItemsOfType(Type);
	}

	// For each item in the player's inventory
	for (FItemData i : ArrayToSort) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the strings
			for (int j = 0; j < SortedArray.Num(); j++) {
				int comparisonResult = i.Name.Compare(SortedArray[j].Name, ESearchCase::IgnoreCase);

				// If they are the same
				if (comparisonResult == 0) {
					// Insert i after j
					SortedArray.Insert(i, j + 1);
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

TArray<FItemData> UInventoryComponent::SortInventoryNewest(TEnumAsByte<EItemType> Type)
{
	if (Inventory.IsEmpty()) {
		return TArray<FItemData>();
	}

	TArray<FItemData> SortedArray;
	TArray<FItemData> ArrayToSort;

	// Get the items that require sorting
	if (Type == EItemType::Item) {
		ArrayToSort = GetAllInventoryItems();
	}
	else {
		ArrayToSort = GetInventoryItemsOfType(Type);
	}

	// For each item in the player's inventory
	for (FItemData i : ArrayToSort) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the InventoryOrder
			for (int j = 0; j < SortedArray.Num(); j++) {
				// If they are less (i is earlier on in the alphabet)
				if (i.Order <= SortedArray[j].Order) {
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

TArray<FItemData> UInventoryComponent::SortInventoryOldest(TEnumAsByte<EItemType> Type)
{
	if (Inventory.IsEmpty()) {
		return TArray<FItemData>();
	}

	TArray<FItemData> SortedArray;
	TArray<FItemData> ArrayToSort;

	// Get the items that require sorting
	if (Type == EItemType::Item) {
		ArrayToSort = GetAllInventoryItems();
	}
	else {
		ArrayToSort = GetInventoryItemsOfType(Type);
	}

	// For each item in the player's inventory
	for (FItemData i : ArrayToSort) {

		// Check if it is the first item to sort.  If so, add it
		if (SortedArray.Num() == 0) {
			SortedArray.Add(i);
		}
		// If it is the second onwards item, then continue
		else {
			// For each item in the SortedArray, compare the InventoryOrder
			for (int j = 0; j < SortedArray.Num(); j++) {
				// If they are less (i is earlier on in the alphabet)
				if (i.Order <= SortedArray[j].Order) {
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

FItemData UInventoryComponent::GetItemAtInventoryOrder(int Order)
{
	for (FItemData i : GetAllInventoryItems()) {
		if (i.Order == Order) {
			UE_LOG(LogTemp, Warning, TEXT("Found"));
			return i;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Not Found"));
	return FItemData("Not Found", "", 0, -1);
}

bool UInventoryComponent::GetItemsExistInInventory(TArray<FCraftingItemData> Items, TEnumAsByte<EItemType> Type)
{
	TArray<FItemData> ArrayToSearch;

	// Get the items that require sorting
	if (Type == EItemType::Item) {
		ArrayToSearch = GetAllInventoryItems();
	}
	else {
		ArrayToSearch = GetInventoryItemsOfType(Type);
	}

	if (ArrayToSearch.IsEmpty() == false) {
		for (FCraftingItemData i : Items) {
			for (FItemData j : ArrayToSearch) {
				if (i.ID == j.ItemID) {
					i.Amount -= j.Amount;
					if (i.Amount <= 0) {
						UE_LOG(LogTemp, Warning, TEXT("eno"));
						break;
					}
				}
			}
			if (i.Amount > 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}