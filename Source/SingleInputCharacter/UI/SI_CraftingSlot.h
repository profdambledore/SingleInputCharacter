// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "SI_CraftingSlot.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API USI_CraftingSlot : public UUserWidget
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
	// Button to update the currently selected item to this one
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UImage* SelectItemImage = nullptr;

	/// -- Item Data -- 
	// The ID of the recipe in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	FName SlotRecipeID;

protected:
	/// -- References --
	// Pointer to the InventoryUI that the owning TileListView is placed in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	class USI_CraftingState* CraftingUI = nullptr;
	
};
