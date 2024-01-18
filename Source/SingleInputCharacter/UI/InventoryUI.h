// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ParentState.h"

#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Engine/DataTable.h"

#include "Core/Data/ItemData.h"

#include "InventoryUI.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API UInventoryUI : public UParentState
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// -- Parent State --
	virtual void OnStateActive() override;

	virtual void OnStateDeactivate() override;

	/// -- Item List --
	// Called to update the list view with an array of items (in blueprint)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateListViewWithItems(const TArray<FItemData>& NewItems);

	// Called to sort the UI by all items
	UFUNCTION()
	void SortInventoryByAll();

	// Called to sort the UI by an inputted stat
	void SortInventoryByStat(TEnumAsByte<EItemType> TypeToSort);

	/// -- Description Box --
	// Called to update the description box to the data in the NewSlot
	UFUNCTION(BlueprintCallable)
	void UpdateDescriptionBox(UInventorySlot* NewSlot);

	// Called to clear the description box and clear the SelectedSlot
	void ClearDescriptionBox();

protected:
	/// -- Inventory Sorting --
	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnInventSortAlphabeticalReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnInventSortNewestReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnInventSortOldestReleased();

	/// -- Item List -- 
	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortWeaponsButtonReleased();

	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortArmourButtonReleased();

	// Button to sort the inventory and display only weapons
	UFUNCTION()
	void OnSortMaterialsButtonReleased();

public:
	/// -- References --
	// Reference to the ItemDisplay
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class AItemDisplay* ItemDisplay = nullptr;

	// Pointer to the SingleInputUI
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class USingleInputUI* MainUI = nullptr;

	// Pointer to the InventoryComponent
	class USingleInputInventory* IC = nullptr;

	// Pointer to the UInventorySlot of the current selected item
	class UInventorySlot* CurrentSelectedItem = nullptr;

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

	// Button used to drop the selected item

	// Inventory Sorting
	// Button to sort the inventory alphabetically
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* InventSortAlphabeticalButton = nullptr;

	// Button to sort the inventory by newest item first
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* InventSortNewestButton = nullptr;

	// Button to sort the inventory by oldest item first
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* InventSortOldestButton = nullptr;

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
