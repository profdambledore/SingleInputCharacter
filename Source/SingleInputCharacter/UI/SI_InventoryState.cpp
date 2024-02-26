// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InventoryState.h"

#include "Item/ItemManager.h"
#include "Character/InventoryComponent.h"
#include "UI/SI_PlayerUI.h"
#include "UI/SI_InventorySlot.h"

void USI_InventoryState::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Sort All Button Release
	DisplayAlphabeticalButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayAlphabeticalReleased);

	// Sort Weapons Button Release
	DisplayNewestButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayNewestReleased);

	// Sort Armour Button Release
	DisplayOldestButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayOldestReleased);

	// Sort Materials Button Release
	DisplayItemsButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayItemsReleased);

	// Sort Alphabetical Button Release
	DisplayWeaponsButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayWeaponsReleased);

	// Sort Newest Button Release
	DisplayArmourButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayArmourReleased);

	// Sort Oldest Button Release
	DisplayMaterialsButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnDisplayMaterialsReleased);

	// Close Menu Button Release
	CloseMenuButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnCloseMenuButtonReleased);

	// Selected Item Used Button Release
	SelectedItemUseButton->OnReleased.AddDynamic(this, &USI_InventoryState::OnSelectedItemUseButtonReleased);
}

void USI_InventoryState::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USI_InventoryState::OnStateActive()
{
	// Set the pointers if they are not set already
	if (PlayerUI) {
		if (!ItemManager) {
			// Find the ItemManager in the world and store a pointer to it
			AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass());
			if (FoundActor) {
				ItemManager = Cast<AItemManager>(FoundActor);
			}
		}
	}
	DisplayInventoryItems();
}

void USI_InventoryState::OnStateDeactivate()
{
	if (PlayerUI) {
		PlayerUI->SwapActiveUIState("InGame");
	}
}

/// -- Sorting UI --
// Called to display all of the inventory items on the UI by the current sort type items
void USI_InventoryState::DisplayInventoryItems()
{
	ClearDescriptionBox();

	if (Inventory) {
		switch (ItemDisplayOrder) {
		case EInventorySortType::Alphabetically:
			UpdateListViewWithItems(Inventory->SortInventoryAlphabetically(ItemsTypeToDisplay));
			break;

		case EInventorySortType::Newest:
			UpdateListViewWithItems(Inventory->SortInventoryNewest(ItemsTypeToDisplay));
			break;

		case EInventorySortType::Oldest:
			UpdateListViewWithItems(Inventory->SortInventoryOldest(ItemsTypeToDisplay));
			break;

			// If somehow default, do Alphabetically;
		default:
			ItemDisplayOrder = Alphabetically;
			break;
		}
	}
}

void USI_InventoryState::OnDisplayAlphabeticalReleased()
{
	ItemDisplayOrder = Alphabetically;
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayNewestReleased()
{
	ItemDisplayOrder = Newest;
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayOldestReleased()
{
	ItemDisplayOrder = Oldest;
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayItemsReleased()
{
	ItemsTypeToDisplay = Item;
	CurrentSortText->SetText(FText::FromString(TEXT("All")));
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayWeaponsReleased()
{
	ItemsTypeToDisplay = Weapon;
	CurrentSortText->SetText(FText::FromString(TEXT("Weapons")));
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayArmourReleased()
{
	ItemsTypeToDisplay = Armour;
	CurrentSortText->SetText(FText::FromString(TEXT("Armour")));
	DisplayInventoryItems();
}

void USI_InventoryState::OnDisplayMaterialsReleased()
{
	ItemsTypeToDisplay = Material;
	CurrentSortText->SetText(FText::FromString(TEXT("Materials")));
	DisplayInventoryItems();
}

void USI_InventoryState::OnSelectedItemUseButtonReleased()
{
	Inventory->UseItem(SelectedItem);

	// Update the specific UI elements
	CurrentSelectedItem->SlotItemAmount -= 1;
	if (CurrentSelectedItem->SlotItemAmount == 0) {
		ItemTileView->RemoveItem(CurrentSelectedItem->SlotItemData);
		ClearDescriptionBox();
	}
	else {
		CurrentSelectedItem->SelectItemAmount->SetText(FText::FromString(FString::Printf(TEXT("x %i"), CurrentSelectedItem->SlotItemAmount)));
		SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *ItemName, CurrentSelectedItem->SlotItemAmount)));
	}
	
}

void USI_InventoryState::OnCloseMenuButtonReleased()
{
	PlayerUI->SwapActiveUIState("InGame");
}

void USI_InventoryState::UpdateDescriptionBox(FName InID, int Amount, int Order, USI_InventorySlot* NewSlot)
{
	// Call the un-select function on the previous selected slot
	CurrentSelectedItem->UnSelectSlot();

	// Update the CurrentSelectedItem with the new slot
	CurrentSelectedItem = NewSlot;

	SelectedItem = Order;

	// Get the item data from the Data Table
	FItemConst NewItem = ItemManager->GetItemDataFromID<FItemConst>(InID, EItemType::Item);

	ItemName = NewItem.Name;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *ItemName, Amount)));
	SelectedItemDesc->SetText(FText::FromString(*NewItem.Desc));

	// Update the mesh being shown in the Item Display
	ItemManager->SetNewMeshTarget(NewItem.StaticMesh, NewItem.SkelMesh, 100);

	// Check if the item is a weapon or a consumable.  If so, display the button to equip.
	if (NewItem.Type == EItemType::Weapon || EItemType::Consumable) {
		SelectedItemUseButton->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		SelectedItemUseButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USI_InventoryState::RefreshDescriptionBox()
{
	
	// Get the item data from the Data Table
	//FItemConst NewItem = ItemManager->GetItemDataFromID<FItemConst>(CurrentSelectedItem->SlotItemID, EItemType::Item);

	//SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *NewItem.Name, Amount)));
}

void USI_InventoryState::ClearDescriptionBox()
{
	// Reset the SelectedItem
	SelectedItem = -1;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(""));
	SelectedItemDesc->SetText(FText::FromString("Select an item"));

	ItemManager->ClearMeshTarget();
}
