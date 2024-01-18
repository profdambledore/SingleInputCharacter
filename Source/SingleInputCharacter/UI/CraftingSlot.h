// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Core/Data/ItemData.h"
#include "Core/Data/CraftingData.h"

#include "CraftingSlot.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API UCraftingSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to un-select this slot
	void UnSelectSlot();

protected:
	/// -- Button Functions --
	UFUNCTION()
	void OnCraftingSlotButtonRelease();

public:
	/// -- Components --
	// Button to update the currently selected item to this one
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SelectRecipeButton = nullptr;

	// Image to display the icon of the item in the slot
	// Button to update the currently selected item to this one
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UImage* SelectRecipeImage = nullptr;

	/// -- ItemData -- 
	// The FCraftingData struct in this slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	FCraftingData SlotRecipe;

protected:
	/// -- References --
	// Pointer to the InventoryUI that the owning TileListView is placed in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	class UCraftingUI* CraftingUI = nullptr;
};
