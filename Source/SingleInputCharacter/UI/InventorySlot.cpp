// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlot.h"
#include "UI/InventoryUI.h"


void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Select Button Release
	SelectItemButton->OnReleased.AddDynamic(this, &UInventorySlot::OnInventorySlotButtonRelease);

}

void UInventorySlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInventorySlot::UnSelectSlot()
{
	// Change any visual modifications back to base
}

void UInventorySlot::OnInventorySlotButtonRelease()
{
	// Check if the slot's data has been set correctly.
	if (SlotItem.ID != "" && InventoryUI) {
		// Set this slot as the new item in the Selected Box
		InventoryUI->UpdateDescriptionBox(this);
	}

}
