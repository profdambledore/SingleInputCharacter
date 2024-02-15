// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CraftingComponent.h"

#include "Character/InventoryComponent.h"
#include "Item/ItemManager.h"

// Sets default values for this component's properties
UCraftingComponent::UCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Find the ItemManager in the world and store a pointer to it
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass());
	if (FoundActor) {
		ItemManager = Cast<AItemManager>(FoundActor);
	}
}

// Called when the game starts
void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TEnumAsByte<EStationType> UCraftingComponent::GetActiveStation()
{
	return ActiveStation;
}

void UCraftingComponent::SetActiveStation(TEnumAsByte<EStationType> InStation)
{
	ActiveStation = InStation;
}

void UCraftingComponent::CraftRecipe(FName InID)
{
	// First, check that the pointers are valid
	if (ItemManager && InventoryComponent) {
		// Then get the recipe data from the ItemManager
		FCraftingConst CurrentRecipe = ItemManager->GetRecipeDataFromID(InID);

		// Get all of the ID's of the inputs and store them in a temp array
		//TArray<FName> IDs;
		//for (FCraftingItemData I : CurrentRecipe.Inputs) {
		//	IDs.Add(I.ID);
		//}

		UE_LOG(LogTemp, Warning, TEXT("In CraftingComponent"));
		// Next, check that all of the items exist in the player's inventory
		if (InventoryComponent->GetItemsExistInInventory(CurrentRecipe.Inputs, EItemType::Item)) {
			ItemManager->CraftItem(InID, InventoryComponent);
		}
	}
}
