// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Texture2D.h"

#include "CraftingData.generated.h"

// Enum denoting the type of crafting statio required
UENUM(BlueprintType, Category = "Crafting")
enum EStationType
{
	None UMETA(DisplayName = "None"),
	Table UMETA(DisplayName = "Table"),
	Furnace UMETA(DisplayName = "Furnace"),
	Anvil UMETA(DisplayName = "Anvil")
};

// Struct holding the data of an item in a crafting recipe
USTRUCT(BlueprintType, Category = "Crafting")
struct SINGLEINPUTCHARACTER_API FCraftingItemData
{
public:
	GENERATED_BODY();

	/// -- Crafting Data --
	// The ID of the item (this matches the row name in the data table)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Item Data")
	FName ID;

	// The amount of the recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting, Item Data")
	int Amount;

	// If the item is consumed by the recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting, Item Data")
	bool bConsumed;

public:
	FCraftingItemData();
	~FCraftingItemData();
};


// Struct holding the data of a crafting recipe
USTRUCT(BlueprintType, Category = "Crafting")
struct SINGLEINPUTCHARACTER_API FCraftingData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Crafting Data --
	// The ID of the recipe (this matches the row name in the data table)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Data")
	FName ID;

	// The inputs of the recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Data")
	TArray<FCraftingItemData> Inputs;

	// The outpus of the recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Data")
	FCraftingItemData Output;

	// The station required by this recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Data")
	TEnumAsByte<EStationType> Station;

	/// -- Crafting Actives --
	// Bool denoting if the recipe can be used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting Actives")
	bool bRecipeActive = false;

public:
	FCraftingData();
	FCraftingData(FCraftingData InData, bool bInActive);
	~FCraftingData();
};
