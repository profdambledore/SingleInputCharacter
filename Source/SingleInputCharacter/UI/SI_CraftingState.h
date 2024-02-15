// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_ParentState.h"

#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

#include "Data/ItemData.h"
#include "Data/CraftingData.h"

#include "SI_CraftingState.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USI_CraftingState : public USI_ParentState
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// -- Parent State --
	virtual void OnStateActive() override;

	virtual void OnStateDeactivate() override;

	/// -- Crafting List --
	// Called to update the list view with an array of crafting recipes (in blueprint)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateListViewWithItems(const TArray<FCraftingConst>& NewItems);

	/// -- Description Box --
	// Called to update the description box to the data in the NewSlot ! class UCraftingSlot* NewSlot
	UFUNCTION(BlueprintCallable)
	void UpateDescriptionBox(FName RecipeID, class USI_CraftingSlot* NewSlot);

	// Called to clear the description box and clear the SelectedSlot
	void ClearDescriptionBox();

	// Called to update the input list view (in blueprints)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInputList(const TArray<FCraftingItemData>& NewItems);

protected:
	/// -- Crafting List -- 
	// Called to display all of the inventory items on the UI by the current sort type items
	UFUNCTION()
	void DisplayCraftingRecipes();

	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnDisplayItemsReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnDisplayWeaponsReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnDisplayArmourReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnDisplayMaterialsReleased();

	/// -- Description Box --
	// Button to craft the recipe in the current selected slot
	UFUNCTION()
	void OnCraftButtonReleased();

	/// -- Menu Navigation --
	// Button to close the current UI State and return to gameplay
	UFUNCTION()
	void OnCloseMenuButtonReleased();

public:
	/// -- Pointers --
	// Pointer to the ItemDisplay
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class AItemManager* ItemManager = nullptr;

	// Pointer to the PlayerUI, or the UI that this state is contained in
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class USI_PlayerUI* PlayerUI = nullptr;

	// Pointer to the inventory component of this UI
	class UInventoryComponent* Inventory = nullptr;

	// Pointer to the crafting component of this UI owner
	class UCraftingComponent* Crafting = nullptr;

	// FName ID of the recipe currently selected
	// If empty, then no recipe is set
	FName SelectedRecipeID = "";

	// Pointer to the USI_CraftingSlot of the current selected item
	USI_CraftingSlot* CurrentCraftingSlot = nullptr;

protected:
	/// -- Components --
	// Tile View
	// Tile View Object for displaying the inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* ItemTileView = nullptr;

	// Description Box
	// Text Box displaying the name and amount of the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SelectedItemName = nullptr;

	// Text Box displaying the description of the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SelectedItemDesc = nullptr;

	// List View displaying the inputs of the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* SelectedItemInputs = nullptr;

	// Button to craft the current chosen item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CraftButton = nullptr;

	// Tile ViewSorting
	// Text Box to show how the inventory is currently being sorted
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentSortText = nullptr;

	// Horizontal Box used to place all sorting buttons together
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* SortHorizontalBox = nullptr;

	// Button to sort the ListView to 'All'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SortAllButton = nullptr;

	// Button to sort the ListView to 'Weapons'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SortWeaponsButton = nullptr;

	// Button to sort the ListView to 'Armour'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SortArmourButton = nullptr;

	// Button to sort the ListView to 'Materials'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SortMaterialsButton = nullptr;

	// Menu Navigation
	// Text Box displaying the station currently being used
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TitleText = nullptr;

	// Button to navigate back to the main menu
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* MainMenuButton = nullptr;

	// Button to close the menu UI and return to the game
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CloseMenuButton = nullptr;

	/// -- Properties --
	// Enum and bool to store how the inventory is currently sorted
	TEnumAsByte<EItemType> ItemTypeToDisplay;
};
