// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlot.h"
#include "UI/InventoryUI.h"

// Called on construct to setup the widget
void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Select Button Release
	SelectItemButton->OnReleased.AddDynamic(this, &UInventorySlot::OnInventorySlotButtonRelease);

}

// Called to update the properties of the widget
void UInventorySlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

// Called to un-select this slot
void UInventorySlot::UnSelectSlot()
{
	// Change any visual modifications back to base
}

// Button to update the currently selected item to this one
void UInventorySlot::OnInventorySlotButtonRelease()
{
	// Check if the slot's data has been set correctly.
	if (SlotItem.ID != "" && InventoryUI) {
		// Set this slot as the new item in the Selected Box
		InventoryUI->UpdateDescriptionBox(this);
	}

}
