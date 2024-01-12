// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"
#include "Core/SingleInputUI.h"
#include "UI/InventorySlot.h"
#include "Core/SingleInputPerson.h"
#include "Core/SingleInputInventory.h"
#include "UI/ItemDisplay.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Sort All Button Release
	SortAllButton->OnReleased.AddDynamic(this, &UInventoryUI::SortInventoryByAll);

	// Sort Weapons Button Release
	SortWeaponsButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortWeaponsButtonReleased);

	// Sort Armour Button Release
	SortArmourButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortArmourButtonReleased);

	// Sort Materials Button Release
	SortMaterialsButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortMaterialsButtonReleased);

	// Sort Materials Button Release
	InventSortAlphabeticalButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortAlphabeticalReleased);

	// Sort Materials Button Release
	InventSortNewestButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortNewestReleased);

	// Sort Materials Button Release
	InventSortOldestButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortOldestReleased);
}

void UInventoryUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// Check if the ItemDisplay is spawned.  If it isn't, spawn it
	if (!ItemDisplay) {
		ItemDisplay = GetWorld()->SpawnActor<AItemDisplay>(AItemDisplay::StaticClass(), FVector(0.0f, 0.0f, 10000.0f), FRotator(), FActorSpawnParameters());
	}

	// Update the Inventory Tile List with the current inventory
	if (MainUI) {
		// Resort the inventory and clear the description box
		MainUI->SingleInputPerson->InventoryComponent->ReSortInventory();
		ClearDescriptionBox();
		if (bSortedByAll) {
			SortInventoryByAll();
		}

		else {
			SortInventoryByStat(SortedBy);
		}
	}
}

/// -- Soring Inventory --
void UInventoryUI::OnInventSortAlphabeticalReleased()
{
	MainUI->SingleInputPerson->InventoryComponent->InventorySort = EInventorySortType::Alphabetically;
	SynchronizeProperties();
}

void UInventoryUI::OnInventSortNewestReleased()
{
	MainUI->SingleInputPerson->InventoryComponent->InventorySort = EInventorySortType::Newest;
	SynchronizeProperties();
}

void UInventoryUI::OnInventSortOldestReleased()
{
	MainUI->SingleInputPerson->InventoryComponent->InventorySort = EInventorySortType::Oldest;
	SynchronizeProperties();
}

/// -- Sorting UI --
void UInventoryUI::SortInventoryByAll()
{
	// Update the TileView with all items in the inventory
	bSortedByAll = true;
	UpdateListViewWithItems(MainUI->SingleInputPerson->InventoryComponent->GetInventoryData());
	CurrentSortText->SetText(FText::FromString(TEXT("All")));
}

void UInventoryUI::OnSortWeaponsButtonReleased()
{
	SortInventoryByStat(EItemType::Weapon);
}

void UInventoryUI::OnSortArmourButtonReleased()
{
	SortInventoryByStat(EItemType::Armour);
}

void UInventoryUI::OnSortMaterialsButtonReleased()
{
	SortInventoryByStat(EItemType::Material);
}

void UInventoryUI::SortInventoryByStat(TEnumAsByte<EItemType> TypeToSort)
{
	// Update sorted properties
	bSortedByAll = false;
	SortedBy = TypeToSort;

	// Sort the inventory and store all items matching the selected type
	TArray<FItemData> SortedItems;
	for (FItemData i : MainUI->SingleInputPerson->InventoryComponent->GetInventoryData()) {
		if (i.Type == TypeToSort) {
			SortedItems.Add(i);
		}
	}

	// Then update the list and CurrentSortText
	UpdateListViewWithItems(SortedItems);
	CurrentSortText->SetText(FText::FromName(UEnum::GetValueAsName(TypeToSort)));
}

/// -- Description Box --
void UInventoryUI::UpdateDescriptionBox(UInventorySlot* NewSlot)
{
	// Call the un-select function on the previous selected slot
	CurrentSelectedItem->UnSelectSlot();

	// Update the CurrentSelectedItem with the new slot
	CurrentSelectedItem = NewSlot;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *CurrentSelectedItem->SlotItem.Name, CurrentSelectedItem->SlotItem.Amount)));

	// Update the mesh being shown in the Item Display
	ItemDisplay->SetNewMeshTarget(CurrentSelectedItem->SlotItem.StaticMesh, CurrentSelectedItem->SlotItem.SkelMesh, 100);

}

void UInventoryUI::ClearDescriptionBox()
{
	CurrentSelectedItem = nullptr;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString("Select an item"));
}
