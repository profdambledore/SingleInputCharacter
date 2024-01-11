// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "ItemData.generated.h"

UENUM(BlueprintType, Category = "Items")
enum EItemType
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armour UMETA(DisplayName = "Armour"),
	Material UMETA(DisplayName = "Material")
};


UENUM(BlueprintType, Category = "Items")
enum EInventorySortType
{
	Alphabetically UMETA(DisplayName = "Alphabetically"),
	Newest UMETA(DisplayName = "Newest"),
	Oldest UMETA(DisplayName = "Oldest")
};

USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FItemData : public FTableRowBase
{
public:
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InventoryOrder;

	// Constructors / Destructors
	FItemData();
	FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack);
	FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack, int InInventOrder);
	~FItemData();

	// Additional Functions
	int AddItems(FItemData ItemsToAdd);
	int RemoveItems(int InAmount);
	bool GetItemAtMaxStack();
};
