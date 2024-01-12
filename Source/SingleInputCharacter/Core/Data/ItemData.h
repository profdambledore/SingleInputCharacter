// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Texture2D.h"


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

	// -- Item Data
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

	// -- Item Display
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkelMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;


	// Constructors / Destructors
	FItemData();
	FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack);
	FItemData(FItemData InItemData, int InAmount, int InInventOrder);
	~FItemData();

	// Additional Functions
	int AddItems(FName NewItemID, int AmountToAdd);
	int RemoveItems(int InAmount);
	bool GetItemAtMaxStack();
};
