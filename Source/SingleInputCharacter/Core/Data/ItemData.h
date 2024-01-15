// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Texture2D.h"


#include "ItemData.generated.h"

// Enum denoting the type of item
UENUM(BlueprintType, Category = "Items")
enum EItemType
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armour UMETA(DisplayName = "Armour"),
	Material UMETA(DisplayName = "Material")
};

// Enum denoting the context stat of the item
UENUM(BlueprintType, Category = "Items")
enum EContextStat
{
	Default UMETA(DisplayName = "Default"),
	Damage UMETA(DisplayName = "Damage"),
	Defence UMETA(DisplayName = "Defence")
};

// Enum denoting how the inventory should be sorted
UENUM(BlueprintType, Category = "Items")
enum EInventorySortType
{
	Alphabetically UMETA(DisplayName = "Alphabetically"),
	Newest UMETA(DisplayName = "Newest"),
	Oldest UMETA(DisplayName = "Oldest")
};

// Struct holding the data of items
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FItemData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Item Data --
	// The ID of the item (this matches the row name in the data table)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FName ID;

	// The display name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString Name;

	// The context stat type of an item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TEnumAsByte<EContextStat> StatType;

	// The amount tied to the context stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int StatAmount;

	// The description of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString Desc;

	// The type of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TEnumAsByte<EItemType> Type;

	// The class of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TSubclassOf<class AParentItem> Class;

	// The maximum amount an FItemData struct can hold.  Use -1 for infinite stacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int MaxStack;

	/// -- Item Upgrades --
	// Any upgrade tags applied to the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Upgrades")
	TArray<FString> UpgradeTags;

	/// -- Item Actives --
	// The current amount of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actives")
	int Amount;

	// The order this item is placed in an inventory (useful for sorting by newest/oldest)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actives")
	int InventoryOrder;

	/// -- Item Display --
	// The static mesh of the item (if valid SkelMesh won't be used)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Display")
	UStaticMesh* StaticMesh = nullptr;

	// The skeletal mesh of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Display")
	USkeletalMesh* SkelMesh = nullptr;

	// The icon of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Display")
	UTexture2D* Icon = nullptr;


	/// -- Constructors / Destructors --
	// Defaults
	FItemData();
	~FItemData();

	// Constructor used to directly set the data stats
	FItemData(FName InID, FString InName, TEnumAsByte<EItemType> InType, int InAmount, int InMaxStack);

	// Constructor to set the data stats from an existing FItemData, alongside a new amount and inventory order
	FItemData(FItemData InItemData, int InAmount, int InInventOrder);

	/// -- Additional Functions --
	// Called to add items to an existing FItemData
	int AddItems(FName NewItemID, int AmountToAdd);

	// Called to remove items from an existing FItemData
	int RemoveItems(int InAmount);

	// Called to check if an existing FItemData's Amount is at its MaxStack
	bool GetItemAtMaxStack();
};
