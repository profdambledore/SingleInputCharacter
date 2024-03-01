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

	/// -- Actives --
	// Called to set the current ammo type of the equipped weapon
	void SetCurrentAmmoType(FName InItemID);

	/// -- Queries --
	// Called to return all items in the inventory
	TArray<FItemData> GetAllInventoryItems();

	// Called to return all items of a specific type
	TArray<FItemData> GetInventoryItemsOfType(TEnumAsByte<EItemType> Type);

	// Called to add an item to the inventory
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FName InItemID, int InAmount);

	// Called to remove an item from the inventory
	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(FName InItemID, int Amount);

	// Called to use an item in the inventory
	void UseItem(int Order);

	// Called to return the amount of an item in the inventory
	int GetAmountOfItem(FName InItemID);

	// Called to sort the inventory in alphabetical order
	TArray<FItemData> SortInventoryAlphabetically(TEnumAsByte<EItemType> Type);

	// Called to sort the inventory by newest item first
	TArray<FItemData> SortInventoryNewest(TEnumAsByte<EItemType> Type);

	// Called to sort the inventory by oldest item first
	TArray<FItemData> SortInventoryOldest(TEnumAsByte<EItemType> Type);

	// Called to get the item at the inventory order
	FItemData GetItemAtInventoryOrder(int Order);

	// Called to get if all items exist in the inventory
	UFUNCTION(BlueprintCallable)
	bool GetItemsExistInInventory(TArray<FCraftingItemData> Items, TEnumAsByte<EItemType> Type);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/// -- Pointers --
	// Pointer to the owner of this inventory
	AActor* InventoryOwner = nullptr;

	// Pointer to the users InventoryComponent
	class UStatsComponent* StatsComponent = nullptr;

	/// -- Player Specific --
	// Pointer to the PlayerUI owned by the player
	class USI_PlayerUI* PlayerUI = nullptr;

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

	// FName denoting the units current ammo object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Stats")
	FName AmmoID;

	/// -- Pointers --
	// Pointer to the ItemManager object
	class AItemManager* ItemManager = nullptr;	
};
