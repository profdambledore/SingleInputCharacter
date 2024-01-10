// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

protected:
	/// -- Inventory Data --
	// Array to hold all data about the players items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Data")
	TArray<FItemData> InventoryItems;
		
};
