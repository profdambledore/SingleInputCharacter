// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"
#include "Core/SingleInputUI.h"
#include "UI/InventorySlot.h"
#include "Core/SingleInputPerson.h"
#include "Core/SingleInputInventory.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Sort All Button Release
	SortAllButton->OnReleased.AddDynamic(this, &UInventoryUI::SortInventoryByAll);

	// Sort Weapons Button Release
	SortWeaponsButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortWeaponsButtonReleased);

	// Sort Armour Button Release
	SortArmourButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortArmourButtonReleased);

	// Sort Materials Button Release
	SortMaterialsButton->OnReleased.AddDynamic(this, &UInventoryUI::OnSortMaterialsButtonReleased);
}

void UInventoryUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (MainUI) {
		if (bSortedByAll) {
			SortInventoryByAll();
		}

		else {
			SortInventoryByStat(SortedBy);
		}
	}
}

/// -- Sorting --
void UInventoryUI::SortInventoryByAll()
{
	bSortedByAll = true;
	UpdateListViewWithItems(MainUI->SingleInputPerson->InventoryComponent->GetInventoryData());
	CurrentSortText->SetText(FText::FromString(TEXT("All")));
}

void UInventoryUI::OnSortWeaponsButtonReleased()
{
	SortInventoryByStat(EItemType::Weapon);
}

void UInventoryUI::OnSortArmourButtonReleased()
{
	SortInventoryByStat(EItemType::Armour);
}

void UInventoryUI::OnSortMaterialsButtonReleased()
{
	SortInventoryByStat(EItemType::Material);
}

void UInventoryUI::SortInventoryByStat(TEnumAsByte<EItemType> TypeToSort)
{
	bSortedByAll = false;
	SortedBy = TypeToSort;

	CurrentSortText->SetText(FText::FromName(UEnum::GetValueAsName(TypeToSort)));
}

/// -- Description Box --
void UInventoryUI::UpdateDescriptionBox(UInventorySlot* NewSlot)
{
	// Call the un-select function on the previous selected slot
	CurrentSelectedItem->UnSelectSlot();

	// Update the CurrentSelectedItem with the new slot
	CurrentSelectedItem = NewSlot;

	// Update the description box elements
	SelectedItemName->SetText(FText::FromString(FString::Printf(TEXT("%s - x %i"), *CurrentSelectedItem->SlotItem.Name, CurrentSelectedItem->SlotItem.Amount)));

}
