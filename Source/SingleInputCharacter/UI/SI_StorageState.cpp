// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_StorageState.h"

#include "Item/ItemManager.h"
#include "Character/InventoryComponent.h"
#include "UI/SI_PlayerUI.h"

void USI_StorageState::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Sort All Button Release
	PlayerDisplayAlphabeticalButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayAlphabeticalReleased);

	// Sort Weapons Button Release
	PlayerDisplayNewestButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayNewestReleased);

	// Sort Armour Button Release
	PlayerDisplayOldestButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayOldestReleased);

	// Sort Materials Button Release
	PlayerDisplayItemsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayItemsReleased);

	// Sort Alphabetical Button Release
	PlayerDisplayWeaponsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayWeaponsReleased);

	// Sort Newest Button Release
	PlayerDisplayArmourButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayArmourReleased);

	// Sort Oldest Button Release
	PlayerDisplayMaterialsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnPlayerDisplayMaterialsReleased);

	// Storage Side
	// Sort All Button Release
	StorageDisplayAlphabeticalButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayAlphabeticalReleased);

	// Sort Weapons Button Release
	StorageDisplayNewestButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayNewestReleased);

	// Sort Armour Button Release
	StorageDisplayOldestButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayOldestReleased);

	// Sort Materials Button Release
	StorageDisplayItemsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayItemsReleased);

	// Sort Alphabetical Button Release
	StorageDisplayWeaponsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayWeaponsReleased);

	// Sort Newest Button Release
	StorageDisplayArmourButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayArmourReleased);

	// Sort Oldest Button Release
	StorageDisplayMaterialsButton->OnReleased.AddDynamic(this, &USI_StorageState::OnStorageDisplayMaterialsReleased);

	// Close Menu Button Release
	CloseMenuButton->OnReleased.AddDynamic(this, &USI_StorageState::OnCloseMenuButtonReleased);
}

void USI_StorageState::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USI_StorageState::OnStateActive()
{
	// Set the pointers if they are not set already
	if (PlayerUI) {
		if (!ItemManager) {
			// Find the ItemManager in the world and store a pointer to it
			AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass());
			if (FoundActor) {
				ItemManager = Cast<AItemManager>(FoundActor);
			}
		}
	}
}

void USI_StorageState::OnStateDeactivate()
{
	StorageInventory = nullptr;
}

void USI_StorageState::DisplayInventoryItems(class UInventoryComponent* NewStorageInventory, FString InStorageName)
{
	// Set the StorageInventory to the NewStorageInventory if not nullptr;
	if (NewStorageInventory) {
		StorageInventory = NewStorageInventory;
	}

	// Update the StorageName
	StorageName = InStorageName;

	if (PlayerInventory) {
		switch (PlayerDisplayOrder) {
		case EInventorySortType::Alphabetically:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryAlphabetically(PlayerTypeToDisplay));
			break;

		case EInventorySortType::Newest:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryNewest(PlayerTypeToDisplay));
			break;

		case EInventorySortType::Oldest:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryOldest(PlayerTypeToDisplay));
			break;

			// If somehow default, do Alphabetically;
		default:
			PlayerDisplayOrder = Alphabetically;
			break;
		}
	}

	if (StorageInventory) {
		switch (StorageDisplayOrder) {
		case EInventorySortType::Alphabetically:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryAlphabetically(StorageTypeToDisplay));
			break;

		case EInventorySortType::Newest:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryNewest(StorageTypeToDisplay));
			break;

		case EInventorySortType::Oldest:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryOldest(StorageTypeToDisplay));
			break;

			// If somehow default, do Alphabetically;
		default:
			StorageDisplayOrder = Alphabetically;
			break;
		}
	}
}

void USI_StorageState::DisplayPlayerInventoryItems()
{
	if (PlayerInventory) {
		switch (PlayerDisplayOrder) {
		case EInventorySortType::Alphabetically:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryAlphabetically(PlayerTypeToDisplay));
			break;

		case EInventorySortType::Newest:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryNewest(PlayerTypeToDisplay));
			break;

		case EInventorySortType::Oldest:
			UpdatePlayerTileViewWithItems(PlayerInventory->SortInventoryOldest(PlayerTypeToDisplay));
			break;

			// If somehow default, do Alphabetically;
		default:
			PlayerDisplayOrder = Alphabetically;
			break;
		}
	}
}

void USI_StorageState::DisplayStorageInventoryItems()
{
	if (StorageInventory) {
		switch (StorageDisplayOrder) {
		case EInventorySortType::Alphabetically:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryAlphabetically(StorageTypeToDisplay));
			break;

		case EInventorySortType::Newest:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryNewest(StorageTypeToDisplay));
			break;

		case EInventorySortType::Oldest:
			UpdateStorageTileViewWithItems(StorageInventory->SortInventoryOldest(StorageTypeToDisplay));
			break;

			// If somehow default, do Alphabetically;
		default:
			StorageDisplayOrder = Alphabetically;
			break;
		}
	}
}

void USI_StorageState::MoveItemSingle(int Order, bool bFromPlayerInventory)
{
	// Move a single item from inventory one to inventory two
	// First, set invent one and invent two
	UInventoryComponent* FromInventory;
	UInventoryComponent* TooInventory;

	if (bFromPlayerInventory) {
		FromInventory = PlayerInventory;
		TooInventory = StorageInventory;
	}
	else {
		FromInventory = StorageInventory;
		TooInventory = PlayerInventory;
	}

	// Next, remove one of the item from FromInventory and add it to TooInventory
	FItemData Item = FromInventory->GetItemAtInventoryOrder(Order);
	FromInventory->RemoveItemFromInventory(Item.ItemID, 1);

	TooInventory->AddItemToInventory(Item.ItemID, 1);

	// Finally, update the state's lists
	DisplayInventoryItems(nullptr);
}

void USI_StorageState::MoveItemStack(int Order, bool bFromPlayerInventory)
{
	// Move a single item from inventory one to inventory two
	// First, set invent one and invent two
	UInventoryComponent* FromInventory;
	UInventoryComponent* TooInventory;

	if (bFromPlayerInventory) {
		FromInventory = PlayerInventory;
		TooInventory = StorageInventory;
	}
	else {
		FromInventory = StorageInventory;
		TooInventory = PlayerInventory;
	}

	// Next, remove one of the item from FromInventory and add it to TooInventory
	FItemData Item = FromInventory->GetItemAtInventoryOrder(Order);
	FromInventory->RemoveItemFromInventory(Item.ItemID, Item.Amount);

	TooInventory->AddItemToInventory(Item.ItemID, Item.Amount);

	// Finally, update the state's lists
	DisplayInventoryItems(nullptr);
}

void USI_StorageState::OnPlayerDisplayAlphabeticalReleased()
{
	PlayerDisplayOrder = Alphabetically;
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayNewestReleased()
{
	PlayerDisplayOrder = Newest;
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayOldestReleased()
{
	PlayerDisplayOrder = Oldest;
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayItemsReleased()
{
	PlayerTypeToDisplay = Item;
	PlayerSortText->SetText(FText::FromString(TEXT("Inventory - All")));
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayWeaponsReleased()
{
	PlayerTypeToDisplay = Weapon;
	PlayerSortText->SetText(FText::FromString(TEXT("Inventory - Weapon")));
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayArmourReleased()
{
	PlayerTypeToDisplay = Armour;
	PlayerSortText->SetText(FText::FromString(TEXT("Inventory - Armour")));
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnPlayerDisplayMaterialsReleased()
{
	PlayerTypeToDisplay = Material;
	PlayerSortText->SetText(FText::FromString(TEXT("Inventory - Materials")));
	DisplayPlayerInventoryItems();
}

void USI_StorageState::OnStorageDisplayAlphabeticalReleased()
{
	StorageDisplayOrder = Alphabetically;
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnStorageDisplayNewestReleased()
{
	StorageDisplayOrder = Newest;
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnStorageDisplayOldestReleased()
{
	StorageDisplayOrder = Oldest;
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnStorageDisplayItemsReleased()
{
	StorageTypeToDisplay = Item;
	StorageSortText->SetText(FText::FromString(FString::Printf(TEXT("%s - All"), *StorageName)));
	DisplayStorageInventoryItems();

}

void USI_StorageState::OnStorageDisplayWeaponsReleased()
{
	StorageTypeToDisplay = Weapon;
	StorageSortText->SetText(FText::FromString(FString::Printf(TEXT("%s - Weapon"), *StorageName)));
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnStorageDisplayArmourReleased()
{
	StorageTypeToDisplay = Armour;
	StorageSortText->SetText(FText::FromString(FString::Printf(TEXT("%s - Armour"), *StorageName)));
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnStorageDisplayMaterialsReleased()
{
	StorageTypeToDisplay = Material;
	StorageSortText->SetText(FText::FromString(FString::Printf(TEXT("%s - Material"), *StorageName)));
	DisplayStorageInventoryItems();
}

void USI_StorageState::OnCloseMenuButtonReleased()
{
	PlayerUI->SwapActiveUIState("InGame");
}
