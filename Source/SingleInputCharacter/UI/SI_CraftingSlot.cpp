// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_CraftingSlot.h"

#include "UI/SI_CraftingState.h"

void USI_CraftingSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SelectItemButton->OnReleased.AddDynamic(this, &USI_CraftingSlot::OnSlotButtonRelease);
}

void USI_CraftingSlot::UnSelectSlot()
{
}

void USI_CraftingSlot::OnSlotButtonRelease()
{
	// Check if the slot's data has been set correctly.
	if (SlotRecipeID != "" && CraftingUI) {
		// Set this slot as the new item in the Selected Box
		CraftingUI->UpateDescriptionBox(SlotRecipeID, this);
	}
}