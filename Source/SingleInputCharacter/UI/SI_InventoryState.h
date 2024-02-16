// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_ParentState.h"

#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

#include "Data/ItemData.h"

#include "SI_InventoryState.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USI_InventoryState : public USI_ParentState
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

	// Called to display all of the inventory items on the UI by the current sort type items
	UFUNCTION()
	void DisplayInventoryItems();

	/// -- Description Box --
	// Called to update the description box to the data in the NewSlot | class UInventorySlot* NewSlot,
	UFUNCTION(BlueprintCallable)
	void UpdateDescriptionBox(FName InID, int Amount, int Order, USI_InventorySlot* NewSlot);

	// Called to clear the description box and clear the SelectedSlot
	void ClearDescriptionBox();

protected:
	/// -- Inventory Sorting --
	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnDisplayAlphabeticalReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnDisplayNewestReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnDisplayOldestReleased();

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

	// Button OnRelease to use the current selected item
	UFUNCTION()
	void OnSelectedItemUseButtonReleased();

	// Button OnRelease to exit the inventory
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

	// Int matching the InventoryOrder of the current selected item
	// If -1, no item is set
	int SelectedItem = -1;

	// Pointer to the UInventorySlot of the current selected item
	class USI_InventorySlot* CurrentSelectedItem = nullptr;

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

	// Button used to use the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Description Box")
	UButton* SelectedItemUseButton = nullptr;

	// Inventory Sorting
	// Button to set ItemDisplayOrder to 'Alphabetically'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayAlphabeticalButton = nullptr;

	// Button to set ItemDisplayOrder to 'Newest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayNewestButton = nullptr;

	// Button to set ItemDisplayOrder to 'Oldest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayOldestButton = nullptr;

	// Tile ViewSorting
	// Text Box to show how the inventory is currently being sorted
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentSortText = nullptr;

	// Horizontal Box used to place all sorting buttons together
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* SortHorizontalBox = nullptr;

	// Button to set ItemsTypeToDisplay to 'Item'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayItemsButton = nullptr;

	// Button to set ItemsTypeToDisplay to 'Weapons'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayWeaponsButton = nullptr;

	// Button to set ItemsTypeToDisplay to 'Armour'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayArmourButton = nullptr;

	// Button to set ItemsTypeToDisplay to 'Materials'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* DisplayMaterialsButton = nullptr;

	// Menu Navigation
	// Button to navigate back to the main menu
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* MainMenuButton = nullptr;

	// Button to close the menu UI and return to the game
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CloseMenuButton = nullptr;

	/// -- Properties --
	// Enum used to decide what item types should be displayed (Item = All items)
	TEnumAsByte<EItemType> ItemsTypeToDisplay = EItemType::Item;

	// Enum used to decide what order the items should be displayed in (Alphabetically, Newest First or Oldest First);
	TEnumAsByte<EInventorySortType> ItemDisplayOrder = EInventorySortType::Alphabetically;
};
