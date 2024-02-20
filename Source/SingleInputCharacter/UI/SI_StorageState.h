// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_ParentState.h"

#include "Components/TileView.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Data/ItemData.h"

#include "SI_StorageState.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USI_StorageState : public USI_ParentState
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// -- Parent State --
	virtual void OnStateActive() override;

	virtual void OnStateDeactivate() override;

	/// -- Tile Views --
	// Called to update the list view with an array of items of the player's inventory (in blueprint)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerTileViewWithItems(const TArray<FItemData>& NewItems);

	// Called to update the list view with an array of items of the storage's inventory (in blueprint)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStorageTileViewWithItems(const TArray<FItemData>& NewItems);

	// Called to display both the player and storage's inventory on the UI by the current sort type items
	UFUNCTION()
	void DisplayInventoryItems(class UInventoryComponent* NewStorageInventory);

	// Called to display the player's inventory on the UI by the current sort type items
	UFUNCTION()
	void DisplayPlayerInventoryItems();

	// Called to display the storage's inventory on the UI by the current sort type items
	// Will not work if DisplayInventoryItems has not been called before
	UFUNCTION()
	void DisplayStorageInventoryItems();

	/// -- Inventory Management --
	// Called to move a single item from one inventory to the other
	UFUNCTION(BlueprintCallable)
	void MoveItemSingle(int Order, bool bFromPlayerInventory);

	// Called to move a whole stack of items from one inventory to the other
	UFUNCTION(BlueprintCallable)
	void MoveItemStack(int Order, bool bFromPlayerInventory);


protected:
	/// -- Inventory Sorting --
	// Player Side
	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnPlayerDisplayAlphabeticalReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnPlayerDisplayNewestReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnPlayerDisplayOldestReleased();

	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnPlayerDisplayItemsReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnPlayerDisplayWeaponsReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnPlayerDisplayArmourReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnPlayerDisplayMaterialsReleased();

	// Storage Side
	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnStorageDisplayAlphabeticalReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnStorageDisplayNewestReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnStorageDisplayOldestReleased();

	// Button OnRelease to sort the inventory alphabetically
	UFUNCTION()
	void OnStorageDisplayItemsReleased();

	// Button OnRelease to sort the inventory by Newest first
	UFUNCTION()
	void OnStorageDisplayWeaponsReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnStorageDisplayArmourReleased();

	// Button OnRelease to sort the inventory by oldest first
	UFUNCTION()
	void OnStorageDisplayMaterialsReleased();

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

	// Pointer to the player's inventory component of this UI
	class UInventoryComponent* PlayerInventory = nullptr;

	// Pointer to the storage's inventory component of this UI
	class UInventoryComponent* StorageInventory = nullptr;

protected:
	/// -- Components --
	// Tile Views
	// Tile View Object for displaying the player's inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* PlayerItemTileView = nullptr;

	// Tile View Object for displaying the storage's inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* StorageItemTileView = nullptr;

	// Player Side
	// Text Box to show how the player's inventory is currently being sorted
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerSortText = nullptr;

	// Horizontal Box used to place all player buttons together
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* PlayerHorizontalBox = nullptr;

	// Button to set PlayerTypeToDisplay to 'Item'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayItemsButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Weapons'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayWeaponsButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Armour'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayArmourButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Materials'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayMaterialsButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Alphabetically'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayAlphabeticalButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Newest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayNewestButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Oldest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* PlayerDisplayOldestButton = nullptr;

	// Storage Side
	// Text Box to show how the player's inventory is currently being sorted
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* StorageSortText = nullptr;

	// Horizontal Box used to place all player buttons together
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* StorageHorizontalBox = nullptr;

	// Button to set PlayerTypeToDisplay to 'Item'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayItemsButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Weapons'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayWeaponsButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Armour'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayArmourButton = nullptr;

	// Button to set PlayerTypeToDisplay to 'Materials'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayMaterialsButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Alphabetically'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayAlphabeticalButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Newest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayNewestButton = nullptr;

	// Button to set PlayerDisplayOrder to 'Oldest'
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* StorageDisplayOldestButton = nullptr;

	// Menu Navigation
	// Button to navigate back to the main menu
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* MainMenuButton = nullptr;

	// Button to close the menu UI and return to the game
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CloseMenuButton = nullptr;

	/// -- Properties --
	// Player Side
	// Enum used to decide what player items types should be displayed (Item = All items)
	TEnumAsByte<EItemType> PlayerTypeToDisplay = EItemType::Item;

	// Enum used to decide what order the items should be displayed in (Alphabetically, Newest First or Oldest First);
	TEnumAsByte<EInventorySortType> PlayerDisplayOrder = EInventorySortType::Alphabetically;

	// Storage Side
	// Enum used to decide what player items types should be displayed (Item = All items)
	TEnumAsByte<EItemType> StorageTypeToDisplay = EItemType::Item;

	// Enum used to decide what order the items should be displayed in (Alphabetically, Newest First or Oldest First);
	TEnumAsByte<EInventorySortType> StorageDisplayOrder = EInventorySortType::Alphabetically;

};
