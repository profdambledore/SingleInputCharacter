// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Data/CraftingData.h"
#include "Data/ItemData.h"

#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"

#include "ItemManager.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Item Display --
	// Called to set a new mesh as the Display's target
	UFUNCTION()
	void SetNewMeshTarget(UStaticMesh* InStaticMesh, USkeletalMesh* InSkelMesh, float InSpringArmLength);

	// Called to clear both mesh components
	void ClearMeshTarget();

	/// -- Queries --
	// Called to return the data of a submitted item ID
	template <typename T>
	T GetItemDataFromID(FName InID, TEnumAsByte<EItemType> InType);

	// Called to return an item to Blueprints (templates cannot be exposed to BP)
	UFUNCTION(BlueprintCallable)
	FItemConst GetItemData(FName InID);

	// Called to return weapon data
	FWeaponData GetWeaponDataFromID(FName InID);

	// Called to return consumable data
	FConsumableData GetConsumableDataFromID(FName InID);

	// Called to return a recipe of a submitted recipe ID
	UFUNCTION(BlueprintCallable)
	FCraftingConst GetRecipeDataFromID(FName InID);

	// Called to return all recipe data
	TArray<FCraftingConst> GetRecipeData();

	// Called to return all recipes matching station type
	TArray<FCraftingConst> GetRecipeDataOfStation(TEnumAsByte<EStationType> InStation);

	// Called to return all recipes matching an item and station type (or all if EItemType is "Item")
	TArray<FCraftingConst> GetRecipeDataOfStationAndType(TEnumAsByte<EItemType> InType, TEnumAsByte<EStationType> InStation);

	/// -- Crafting --
	// Called to craft an item and add it to an inventory
	void CraftItem(FName InID, class UInventoryComponent* Inventory);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


protected:
	/// -- Item Display --
	// Static Mesh Component used to display static mesh items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshDisplay_Static = nullptr;

	// Skeletal Mesh Component used to display skeletal mesh items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshDisplay_Skel = nullptr;

	// Spring Arm Component used to move the display capture back from the meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* DisplaySpringArm = nullptr;

	// SceneCaptureComponent used to record and save the icon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneCaptureComponent2D* DisplayCapture = nullptr;

	/// -- Data Tables --
	// Data Table of all items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* ItemDataTable = nullptr;

	// Data Table of all weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* WeaponDataTable = nullptr;

	// Data Table of all consumables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* ConsumablesDataTable = nullptr;

	// Data Table of all recipes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* CraftingDataTable = nullptr;

};

// Convert from template to function
// Didnt work as expected
template<typename T>
inline T AItemManager::GetItemDataFromID(FName InID, TEnumAsByte<EItemType> InType)
{
	switch (InType) {
	case EItemType::Weapon:
		//return (T)FWeaponData();
		break;

	case EItemType::Consumable:
		break;

	default:
		FItemConst* FoundItem = ItemDataTable->FindRow<FItemConst>(InID, "", true);
		return (T)*FoundItem;
		break;
	}
	return T();
}
