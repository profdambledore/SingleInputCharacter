// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CraftingUI.h"
#include "Core/SingleInputUI.h"
#include "UI/CraftingSlot.h"
#include "Core/SingleInputPerson.h"
#include "Core/SingleInputInventory.h"
#include "Core/SingleInputCraftingComponent.h"
#include "UI/ItemDisplay.h"

void UCraftingUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Sort All Button Release
	SortAllButton->OnReleased.AddDynamic(this, &UCraftingUI::SortRecipesByAll);

	// Sort Weapons Button Release
	SortWeaponsButton->OnReleased.AddDynamic(this, &UCraftingUI::OnSortWeaponsButtonReleased);

	// Sort Armour Button Release
	SortArmourButton->OnReleased.AddDynamic(this, &UCraftingUI::OnSortArmourButtonReleased);

	// Sort Materials Button Release
	SortMaterialsButton->OnReleased.AddDynamic(this, &UCraftingUI::OnSortMaterialsButtonReleased);

	// Craft Button Release
	CraftButton->OnReleased.AddDynamic(this, &UCraftingUI::OnCraftButtonReleased);
}

void UCraftingUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// Update the Crafting Tile List with the current craftables
	if (MainUI) {
		ClearDescriptionBox();
		if (bSortedByAll) {
			SortRecipesByAll();
		}

		else {
			SortRecipesByStat(SortedBy);
		}
	}
}

void UCraftingUI::OnStateActive()
{
	// Check if the ItemDisplay pointer is set.  If not, set it now
	if (!ItemDisplay) {
		ItemDisplay = MainUI->SingleInputPerson->ItemDisplay;
	}

	// Set the CraftingComponent pointer if not already set
	if (!CC){
		CC = MainUI->SingleInputPerson->CraftingComponent;
		IC = MainUI->SingleInputPerson->InventoryComponent;
	}

	SortRecipesByAll();

	CraftButton->SetVisibility(ESlateVisibility::Hidden);

	if (CC->ActiveStation == EStationType::None) {
		TitleText->SetText(FText::FromString("Crafting"));
	}
	else {
		TitleText->SetText(FText::FromName(UEnum::GetValueAsName(MainUI->SingleInputPerson->CraftingComponent->ActiveStation)));
	}
}

void UCraftingUI::OnStateDeactivate()
{
	CC->ActiveStation = EStationType::None;
	ItemTileView->ClearListItems();
}

void UCraftingUI::SortRecipesByAll()
{
	// Update bSortedByAll to true, then update the list view with all available recipes
	UpdateListViewWithItems(CC->GetCurrentCraftables());
	CurrentSortText->SetText(FText::FromString(TEXT("All")));
}

void UCraftingUI::OnSortWeaponsButtonReleased()
{
	SortRecipesByStat(EItemType::Weapon);
}

void UCraftingUI::OnSortArmourButtonReleased()
{
	SortRecipesByStat(EItemType::Armour);
}

void UCraftingUI::OnSortMaterialsButtonReleased()
{
	SortRecipesByStat(EItemType::Material);
}

void UCraftingUI::OnCraftButtonReleased()
{
	if (CurrentCraftingSlot) {
		if (CurrentCraftingSlot->SlotRecipe.bRecipeActive == true) {
			CC->CraftItem(CurrentCraftingSlot->SlotRecipe.ID);
			SynchronizeProperties();
		}
	}
}

void UCraftingUI::SortRecipesByStat(TEnumAsByte<EItemType> TypeToSort)
{
	// Update sorted properties
	bSortedByAll = false;
	SortedBy = TypeToSort;

	// Get the current recipes available of the item type and update the list view
	UpdateListViewWithItems(CC->GetCurrentCraftablesOfType(TypeToSort));
	CurrentSortText->SetText(FText::FromName(UEnum::GetValueAsName(TypeToSort)));
}

/// -- Description Box --
// Called to update the description box to the data in the NewSlot
void UCraftingUI::UpateDescriptionBox(UCraftingSlot* NewSlot)
{
	// Call the un-select function on the previous selected slot
	CurrentCraftingSlot->UnSelectSlot();

	// Update the CurrentSelectedItem with the new slot
	CurrentCraftingSlot = NewSlot;

	// Get the data of the recipes output
	FItemData NewItem = IC->FindItemData(CurrentCraftingSlot->SlotRecipe.Output.ID);

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *NewItem.Name, CurrentCraftingSlot->SlotRecipe.Output.Amount)));
	SelectedItemDesc->SetText(FText::FromString(NewItem.Desc));
	UpdateInputList(CurrentCraftingSlot->SlotRecipe.Inputs);

	// Update the mesh being shown in the Item Display
	ItemDisplay->SetNewMeshTarget(NewItem.StaticMesh, NewItem.SkelMesh, 100);

	// Set the visibility of the craft button based on if the recipe is active
	if (CurrentCraftingSlot->SlotRecipe.bRecipeActive == true) {
		CraftButton->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		CraftButton->SetVisibility(ESlateVisibility::Hidden);
	}

}

// Called to clear the description box and clear the SelectedSlot
void UCraftingUI::ClearDescriptionBox()
{
	// Clear the pointer
	CurrentCraftingSlot = nullptr;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString("Select an item"));
	SelectedItemDesc->SetText(FText::FromString(""));
	SelectedItemInputs->ClearListItems();
	CraftButton->SetVisibility(ESlateVisibility::Hidden);

	ItemDisplay->ClearMeshTarget();

}