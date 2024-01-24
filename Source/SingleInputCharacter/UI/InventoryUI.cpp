// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"
#include "Core/SingleInputUI.h"
#include "UI/InventorySlot.h"
#include "Core/SingleInputPerson.h"
#include "Core/SingleInputInventory.h"
#include "UI/ItemDisplay.h"

// Called on construct to setup the widget
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

	// Sort Alphabetical Button Release
	InventSortAlphabeticalButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortAlphabeticalReleased);

	// Sort Newest Button Release
	InventSortNewestButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortNewestReleased);

	// Sort Oldest Button Release
	InventSortOldestButton->OnReleased.AddDynamic(this, &UInventoryUI::OnInventSortOldestReleased);
}

// Called to update the properties of the widget
void UInventoryUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// Update the Inventory Tile List with the current inventory
	if (MainUI) {
		// Resort the inventory and clear the description box
		//IC->ReSortInventory();
		//ClearDescriptionBox();
		if (bSortedByAll) {
			SortInventoryByAll();
		}

		else {
			SortInventoryByStat(SortedBy);
		}
	}
}

void UInventoryUI::OnStateActive()
{
	// Check if the ItemDisplay pointer is set.  If not, set it now
	if (!ItemDisplay) {
		ItemDisplay = MainUI->SingleInputPerson->ItemDisplay;
	}

	// Check if the InventoryComponent pointer is set.  If not, set it now
	if (!IC) {
		IC = MainUI->SingleInputPerson->InventoryComponent;
	}

	// Update the Inventory Tile List with the current inventory
	if (MainUI) {
		// Resort the inventory and clear the description box
		//IC->ReSortInventory();
		ClearDescriptionBox();
		if (bSortedByAll) {
			SortInventoryByAll();
		}

		else {
			SortInventoryByStat(SortedBy);
		}
	}
}

void UInventoryUI::OnStateDeactivate()
{
}

/// -- Inventory Sorting --
// Button OnRelease to sort the inventory alphabetically
void UInventoryUI::OnInventSortAlphabeticalReleased()
{
	// Set the sorting type to Alphabetically and then sync the widget
	IC->InventorySort = EInventorySortType::Alphabetically;
	SynchronizeProperties();
}

// Button OnRelease to sort the inventory by Newest first
void UInventoryUI::OnInventSortNewestReleased()
{
	// Set the sorting type to Newest and then sync the widget
	IC->InventorySort = EInventorySortType::Newest;
	SynchronizeProperties();
}

// Button OnRelease to sort the inventory by oldest first
void UInventoryUI::OnInventSortOldestReleased()
{
	// Set the sorting type to Oldest and then sync the widget
	IC->InventorySort = EInventorySortType::Oldest;
	SynchronizeProperties();
}

/// -- Sorting UI --
// Called to sort the UI by all items
void UInventoryUI::SortInventoryByAll()
{
	// Update the TileView with all items in the inventory
	bSortedByAll = true;
	UpdateListViewWithItems(IC->SortInventory());
	CurrentSortText->SetText(FText::FromString(TEXT("All")));
}

// Button to sort the inventory and display only weapons
void UInventoryUI::OnSortWeaponsButtonReleased()
{
	SortInventoryByStat(EItemType::Weapon);
}

// Button to sort the inventory and display only armour
void UInventoryUI::OnSortArmourButtonReleased()
{
	SortInventoryByStat(EItemType::Armour);
}

// Button to sort the inventory and display only materials
void UInventoryUI::OnSortMaterialsButtonReleased()
{
	SortInventoryByStat(EItemType::Material);
}

// Called to sort the UI by an inputted stat
void UInventoryUI::SortInventoryByStat(TEnumAsByte<EItemType> TypeToSort)
{
	// Update sorted properties
	bSortedByAll = false;
	SortedBy = TypeToSort;

	// Sort the inventory and store all items matching the selected type
	TArray<FItemData> SortedItems;
	for (FItemData i : IC->SortInventory()) {
		if (i.Type == TypeToSort) {
			SortedItems.Add(i);
		}
	}

	// Then update the list and CurrentSortText
	UpdateListViewWithItems(SortedItems);
	CurrentSortText->SetText(FText::FromName(UEnum::GetValueAsName(TypeToSort)));
}

/// -- Description Box --
// Called to update the description box to the data in the NewSlot
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

// Called to clear the description box and clear the SelectedSlot
void UInventoryUI::ClearDescriptionBox()
{
	// Clear the pointer
	CurrentSelectedItem = nullptr;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString("Select an item"));
}
