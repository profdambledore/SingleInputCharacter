// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CraftingSlot.h"
#include "UI/CraftingUI.h"

void UCraftingSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Select Button Release
	SelectRecipeButton->OnReleased.AddDynamic(this, &UCraftingSlot::OnCraftingSlotButtonRelease);
}

void UCraftingSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCraftingSlot::UnSelectSlot()
{
	// Change any visual modifications back to base
}

void UCraftingSlot::OnCraftingSlotButtonRelease()
{
	// Check if the slot's data has been set correctly.
	if (SlotRecipe.ID != "" && CraftingUI) {
		// Set this slot as the new item in the Selected Box
		CraftingUI->UpateDescriptionBox(this);
	}
}
