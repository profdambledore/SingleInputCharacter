// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InventorySlot.h"

#include "UI/SI_InventoryState.h"

void USI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	SelectItemButton->OnReleased.AddDynamic(this, &USI_InventorySlot::OnSlotButtonRelease);
}

void USI_InventorySlot::UnSelectSlot()
{
}

void USI_InventorySlot::OnSlotButtonRelease()
{
	// Check if the slot's data has been set correctly.
	if (SlotItemID != "" && InventoryUI) {
		// Set this slot as the new item in the Selected Box
		InventoryUI->UpdateDescriptionBox(SlotItemID, SlotItemAmount, SlotItemOrder, this);
	}
}
 