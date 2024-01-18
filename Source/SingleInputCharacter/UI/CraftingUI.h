// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ParentState.h"

#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Engine/DataTable.h"

#include "Core/Data/ItemData.h"
#include "Core/Data/CraftingData.h"

#include "CraftingUI.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API UCraftingUI : public UParentState
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
	void UpdateListViewWithItems(const TArray<FCraftingData>& NewItems);

	// Called to sort the UI by all items
	UFUNCTION()
	void SortRecipesByAll();

	// Called to sort the UI by an inputted stat
	void SortRecipesByStat(TEnumAsByte<EItemType> TypeToSort);

	/// -- Description Box --
	// Called to update the description box to the data in the NewSlot
	UFUNCTION(BlueprintCallable)
	void UpateDescriptionBox(class UCraftingSlot* NewSlot);

	// Called to clear the description box and clear the SelectedSlot
	void ClearDescriptionBox();

	// Called to update the input list view (in blueprints)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInputList(const TArray<FCraftingItemData>& NewItems);

protected:
	/// -- Crafting List -- 
	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortWeaponsButtonReleased();

	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortArmourButtonReleased();

	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortMaterialsButtonReleased();

	/// -- Description Box --
	// Button to craft the recipe in the current selected slot
	UFUNCTION()
	void OnCraftButtonReleased();

public:
	/// -- References --
	// Reference to the ItemDisplay
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class AItemDisplay* ItemDisplay = nullptr;

	// Pointer to the SingleInputUI
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class USingleInputUI* MainUI = nullptr;

	// Pointer to the player's crafting component
	class USingleInputCraftingComponent* CC = nullptr;

	// Pointer to the player's inventory component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	class USingleInputInventory* IC = nullptr;

	// Pointer to the current selected crafting slot
	class UCraftingSlot* CurrentCraftingSlot = nullptr;

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
	TEnumAsByte<EItemType> SortedBy;
	bool bSortedByAll = true;
};
