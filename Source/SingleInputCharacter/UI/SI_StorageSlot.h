// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "SI_StorageSlot.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API USI_StorageSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// Called to un-select this slot
	void UnSelectSlot();

protected:
	/// -- Button Functions --
	UFUNCTION()
	void OnSlotButtonRelease();

public:
	/// -- Components --
	// Button to update the currently selected item to this one
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SelectItemButton = nullptr;

	// Image to display the icon of the item in the slot
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UImage* SelectItemImage = nullptr;

	// Text block to display the amount of the item in the slot
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UTextBlock* SelectItemAmount = nullptr;

	/// -- Item Data -- 
	// The ID of the item in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	FName SlotItemID;

	// The amount of the item in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	int SlotItemAmount;

	// The order of the item in the inventory in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	int SlotItemOrder;

	// Bool to denote if the item is in the player's inventory or the storage objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	bool bPlayerInvent;

protected:
	/// -- References --
	// Pointer to the StorageState that the owning TileListView is placed in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	class USI_StorageState* StorageState = nullptr;
};
