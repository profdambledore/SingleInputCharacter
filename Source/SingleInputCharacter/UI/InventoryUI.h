// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

#include "Core/Data/ItemData.h"

#include "InventoryUI.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// -- Item List --
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateListViewWithItems(const TArray<FItemData>& NewItems);

	UFUNCTION()
	void SortInventoryByAll();

	void SortInventoryByStat(TEnumAsByte<EItemType> TypeToSort);

	/// -- Description Box --
	UFUNCTION(BlueprintCallable)
	void UpdateDescriptionBox(UInventorySlot* NewSlot);

protected:
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
	// Reference to the SingleInputPerson
	//UPROPERTY(BlueprintReadOnly, Category = "References")
	//class ASingleInputPerson* SingleInputPerson = nullptr;

	// Pointer to the SingleInputUI
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class USingleInputUI* MainUI = nullptr;

	// Pointer to the UInventorySlot of the current selected item
	class UInventorySlot* CurrentSelectedItem = nullptr;

	/// -- Components --
	// Tile View
	// Tile View Object for displaying the inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* ItemTileView = nullptr;

	// Description Box
	// Image displaying the model for the selected item

	// Text Box displaying the name and amount of the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SelectedItemName = nullptr;

	// Text Box displaying the description of the selected item
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* SelectedItemDesc = nullptr;

	// Button used to drop the selected item


	// Sorting
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
	// Enum to store how the inventory is currently sorted
	TEnumAsByte<EItemType> SortedBy;

	bool bSortedByAll = true;
};
