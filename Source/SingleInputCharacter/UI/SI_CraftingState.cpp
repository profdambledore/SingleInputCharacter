// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_CraftingState.h"

#include "Item/ItemManager.h"
#include "Character/InventoryComponent.h"
#include "Character/CraftingComponent.h"
#include "UI/SI_PlayerUI.h"
#include "UI/SI_CraftingSlot.h"

void USI_CraftingState::NativeConstruct()
{
	Super::NativeConstruct();

	// Sort Materials Button Release
	SortAllButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnDisplayItemsReleased);

	// Sort Alphabetical Button Release
	SortWeaponsButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnDisplayWeaponsReleased);

	// Sort Newest Button Release
	SortArmourButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnDisplayArmourReleased);

	// Sort Oldest Button Release
	SortMaterialsButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnDisplayMaterialsReleased);

	// Craft Button Release
	CraftButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnCraftButtonReleased);

	// Close Menu Button Release
	CloseMenuButton->OnReleased.AddDynamic(this, &USI_CraftingState::OnCloseMenuButtonReleased);
}

void USI_CraftingState::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USI_CraftingState::OnStateActive()
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

	// Then update the ItemTileView with all the available recipes
	DisplayCraftingRecipes();
}

void USI_CraftingState::OnStateDeactivate()
{
}

void USI_CraftingState::DisplayCraftingRecipes()
{
	// Clear the description box
	ClearDescriptionBox();

	if (Inventory) {
		if (ItemTypeToDisplay == Item) {
			UpdateListViewWithItems(ItemManager->GetRecipeDataOfStation(Crafting->GetActiveStation()));
			CurrentSortText->SetText(FText::FromString(TEXT("All")));

		}
		else{
			UpdateListViewWithItems(ItemManager->GetRecipeDataOfStationAndType(ItemTypeToDisplay, Crafting->GetActiveStation()));
			CurrentSortText->SetText(FText::FromName(UEnum::GetValueAsName(ItemTypeToDisplay)));
		}
	}
}

void USI_CraftingState::OnDisplayItemsReleased()
{
	ItemTypeToDisplay = Item;
	DisplayCraftingRecipes();
}

void USI_CraftingState::OnDisplayWeaponsReleased()
{
	ItemTypeToDisplay = Weapon;
	DisplayCraftingRecipes();
}

void USI_CraftingState::OnDisplayArmourReleased()
{
	ItemTypeToDisplay = Armour;
	DisplayCraftingRecipes();
}

void USI_CraftingState::OnDisplayMaterialsReleased()
{
	ItemTypeToDisplay = Material;
	DisplayCraftingRecipes();
}

void USI_CraftingState::UpateDescriptionBox(FName RecipeID, USI_CraftingSlot* NewSlot)
{
	// Call the un-select function on the previous selected slot
	CurrentCraftingSlot->UnSelectSlot();

	// Update the CurrentSelectedItem with the new slot
	CurrentCraftingSlot = NewSlot;

	SelectedRecipeID = RecipeID;

	// Get the data of the crafting recipe
	FCraftingConst NewRecipe = ItemManager->GetRecipeDataFromID(RecipeID);

	// Get the data of the recipes output
	FItemConst OutputItem = ItemManager->GetItemDataFromID<FItemConst>(NewRecipe.Output.ID, EItemType::Item);

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *OutputItem.Name, NewRecipe.Output.Amount)));
	SelectedItemDesc->SetText(FText::FromString(OutputItem.Desc));
	UpdateInputList(NewRecipe.Inputs);

	// Update the mesh being shown in the Item Display
	ItemManager->SetNewMeshTarget(OutputItem.StaticMesh, OutputItem.SkelMesh, 100);

	// Set the visibility of the craft button based on if the recipe is active
	if (Inventory->GetItemsExistInInventory(NewRecipe.Inputs, EItemType::Item)) {
		CraftButton->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		CraftButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USI_CraftingState::ClearDescriptionBox()
{
	// Clear the pointer
	CurrentCraftingSlot = nullptr;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString("Select an item"));
	SelectedItemDesc->SetText(FText::FromString(""));
	SelectedItemInputs->ClearListItems();
	CraftButton->SetVisibility(ESlateVisibility::Hidden);

	// Also clear the current selected recipe
	SelectedRecipeID = "";

	ItemManager->ClearMeshTarget();
}

void USI_CraftingState::OnCraftButtonReleased()
{
	if (SelectedRecipeID != "") {
		// Craft the recipe via the CraftingComponent
		if (Crafting) {
			Crafting->CraftRecipe(SelectedRecipeID);
		}
	}
}

void USI_CraftingState::OnCloseMenuButtonReleased()
{
	PlayerUI->SwapActiveUIState("InGame");
}