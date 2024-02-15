// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Data/ItemData.h"
#include "Data/CraftingData.h"

#include "Kismet/GameplayStatics.h"

#include "CraftingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SINGLEINPUTCHARACTER_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// -- Crafting --
	// Called to get all available recipes of an item type matching the current station.
	// Checks the inventory component to see if the item can be crafted
	// TArray<FCraftingData> GetAllActiveRecipesOfType(TEnumAsByte<EItemType> InType);

	// Called to get the active station of this crafting component
	TEnumAsByte<EStationType> GetActiveStation();

	// Called to set the active station
	UFUNCTION(BlueprintCallable)
	void SetActiveStation(TEnumAsByte<EStationType> InStation);

	// Called to check if a recipe can be crafted.  If so, craft the item via the ItemManager
	void CraftRecipe(FName InID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/// -- Pointers --
	// Pointer to the users InventoryComponent
	class UInventoryComponent* InventoryComponent = nullptr;

protected:
	/// -- Pointers --
	// Pointer to the ItemManager object
	class AItemManager* ItemManager = nullptr;

	// Enum to denote what crafting station is currently being accessed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EStationType> ActiveStation = EStationType::None;
		
};
