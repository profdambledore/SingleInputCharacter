// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Algo/Reverse.h"

#include "Core/Data/ItemData.h"

#include "SingleInputInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEINPUTCHARACTER_API USingleInputInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USingleInputInventory();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// -- Inventory --
	// Called to return an array of all items in the inventory
	TArray<FItemData> GetInventoryData();

	// Called to add an item to the inventory
	void AddItemToArray(FItemData NewItem);

	// Called to remove an item from the inventory
	void RemoveItemFromArray(FItemData ItemToRemove);

	// Called to sort the inventory by an inputted way
	void SortInventory(TEnumAsByte<EInventorySortType> SortBy);

	// Called to resort the inventory by the current type
	void ReSortInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called to sort the inventory in alphabetical order
	void SortInventoryAlphabetically();

	// Called to sort the inventory by newest item first
	void SortInventoryNewest();

	// Called to sort the inventory by newest item first
	void SortInventoryOldest();

public:	
	/// -- Inventory Data --
	// Enum to designate how the inventory is currently sorted / when resorted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TEnumAsByte<EInventorySortType> InventorySort = EInventorySortType::Newest;

protected:
	/// -- Inventory Data --
	// Array to hold all data about the players items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FItemData> InventoryItems;

	int InventoryOrder = 0;

		
};
