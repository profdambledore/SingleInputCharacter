// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputCraftingComponent.h"
#include "Core/SingleInputInventory.h"

// Sets default values for this component's properties
USingleInputCraftingComponent::USingleInputCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Get a reference to the crafting data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Items/DT_CraftingData"));
	if (DTObject.Succeeded()) { CraftingDataTable = DTObject.Object; }
}


// Called when the game starts
void USingleInputCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USingleInputCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FCraftingData> USingleInputCraftingComponent::GetCurrentCraftables()
{
	TArray<FName> OutRows = CraftingDataTable->GetRowNames();
	FCraftingData* CurrentRow;

	TArray<FCraftingData> MatchingItems;

	// For each recipe in the data table, check if it has the matching station or "None" station
	for (FName i : OutRows) {
		CurrentRow = CraftingDataTable->FindRow<FCraftingData>(i, "", true);
		if (CurrentRow->Station == EStationType::None || ActiveStation) {
			// If it does, check if it can be crafted with the current items in the inventory
			if (IC->GetItemsExistInInventory(CurrentRow->Inputs)) {
				MatchingItems.Add(FCraftingData(*CurrentRow, true));
			}
			else {
				MatchingItems.Add(*CurrentRow);
			}
		}
	}

	return MatchingItems;
}

TArray<FCraftingData> USingleInputCraftingComponent::GetCurrentCraftablesOfType(TEnumAsByte<EItemType> InType)
{
	TArray<FName> OutRows = CraftingDataTable->GetRowNames();
	FCraftingData* CurrentRow;

	TArray<FCraftingData> MatchingItems;

	// For each recipe in the data table, check if it has the matching station or "None" station
	for (FName i : OutRows) {
		CurrentRow = CraftingDataTable->FindRow<FCraftingData>(i, "", true);
		if (CurrentRow->Station == EStationType::None || ActiveStation) {
			// If it does, check if the output item matches the InType
			if (IC->FindItemData(CurrentRow->Output.ID).Type == InType) {
				// Finally, check if it can be crafted with the current items in the inventory
				if (IC->GetItemsExistInInventory(CurrentRow->Inputs)) {
					MatchingItems.Add(FCraftingData(*CurrentRow, true));
				}
				else {
					MatchingItems.Add(*CurrentRow);
				}
			}
		}
	}

	return MatchingItems;
}

FCraftingData USingleInputCraftingComponent::FindRecipeData(FName RecipeID)
{
	return *CraftingDataTable->FindRow<FCraftingData>(RecipeID, "", true);
}

FItemData USingleInputCraftingComponent::GetOutputItem(FName RecipeID)
{
	return FItemData();
}

void USingleInputCraftingComponent::CraftItem(FName RecipeID)
{
	FCraftingData *Recipe = CraftingDataTable->FindRow<FCraftingData>(RecipeID, "", true);
	if (Recipe->ID != "") {
		for (FCraftingItemData i : Recipe->Inputs) {
			if (i.bConsumed) {
				IC->RemoveItemFromArray(i.ID, i.Amount);
			}
		}

		IC->AddItemToArray(Recipe->Output.ID, Recipe->Output.Amount);
	}
}


