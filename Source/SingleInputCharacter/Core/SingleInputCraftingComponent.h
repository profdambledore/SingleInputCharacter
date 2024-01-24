// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SingleInputCraftingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEINPUTCHARACTER_API USingleInputCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USingleInputCraftingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// -- Crafting --
	// Called to return all craftables at the current station
	TArray<FCraftingData> GetCurrentCraftables();

	// Called to return all craftables at the current station of an item type
	TArray<FCraftingData> GetCurrentCraftablesOfType(TEnumAsByte<EItemType> InType);

	// Called to get the data of a recipe from the data table
	FCraftingData FindRecipeData(FName RecipeID);

	// Called to return the FItemData of an recipe's output
	FItemData GetOutputItem(FName RecipeID);

	// Called to craft an item
	void CraftItem(FName RecipeID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/// -- References -- 
	// Pointer to the users InventoryComponent
	class USingleInputInventory* IC = nullptr;

	// Enum to denote what crafting station is currently being accessed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStationType> ActiveStation = EStationType::None;

protected:	
	/// -- Crafting Data --
	// Data Table of all items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* CraftingDataTable = nullptr;



		
};
