// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Data/ItemData.h"
#include "Data/CraftingData.h"

#include "Kismet/GameplayStatics.h"

#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEINPUTCHARACTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// -- Queries --
	// Called to return all items in the inventory
	TArray<FItemData> GetAllInventoryItems();

	// Called to return all items of a specific type
	TArray<FItemData> GetInventoryItemsOfType(TEnumAsByte<EItemType> Type);

	// Called to add an item to the inventory
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FName InItemID, int InAmount);

	// Called to remove an item from the inventory
	void RemoveItemFromInventory(FName InItemID, int Amount);

	// Called to sort the inventory in alphabetical order
	TArray<FItemData> SortInventoryAlphabetically(TEnumAsByte<EItemType> Type);

	// Called to sort the inventory by newest item first
	TArray<FItemData> SortInventoryNewest(TEnumAsByte<EItemType> Type);

	// Called to sort the inventory by oldest item first
	TArray<FItemData> SortInventoryOldest(TEnumAsByte<EItemType> Type);

	// Called to get if all items exist in the inventory
	bool GetItemsExistInInventory(TArray<FCraftingItemData> Items, TEnumAsByte<EItemType>);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/// -- Inventory Data --
	// Enum to designate how the inventory is currently sorted / when resorted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TEnumAsByte<EInventorySortType> InventorySort = EInventorySortType::Newest;

protected:
	/// -- Inventory Data --
	// Map of Arrays holding each type of item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TMap<TEnumAsByte<EItemType>, FInventoryTypeData> Inventory;

	// The current inventory order
	int InventoryOrder = 0;

	/// -- Pointers --
	// Pointer to the ItemManager object
	class AItemManager* ItemManager = nullptr;

		
};
