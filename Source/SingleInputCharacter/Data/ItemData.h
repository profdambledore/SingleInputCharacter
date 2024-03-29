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
	Item UMETA(DisplayName = "Item"),
	Weapon UMETA(DisplayName = "Weapon"),
	Armour UMETA(DisplayName = "Armour"),
	Material UMETA(DisplayName = "Material"),
	Consumable UMETA(DisplayName = "Consumable")
};

ENUM_RANGE_BY_COUNT(EItemType, EItemType::Consumable);

// Enum denoting the consumable type
UENUM(BlueprintType, Category = "Items")
enum EConsumableType
{
	Healing UMETA(DisplayName = "Healing"),
	Regen UMETA(DisplayName = "Regen"),
	StatBuff UMETA(DisplayName = "StatBuff"),
	StatPercent UMETA(DisplayName = "StatPercent"),
};

// Enum denoting how the inventory should be sorted
UENUM(BlueprintType, Category = "Items")
enum EInventorySortType
{
	Alphabetically UMETA(DisplayName = "Alphabetically"),
	Newest UMETA(DisplayName = "Newest"),
	Oldest UMETA(DisplayName = "Oldest")
};

// Struct holding the data of an item
// This struct can never be modified
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FItemConst : public FTableRowBase
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

	// The description of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString Desc;

	// The type of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TEnumAsByte<EItemType> Type;

	// The class of the item
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	//TSubclassOf<class AParentItem> Class;

	// The maximum amount an FItemData struct can hold.  Use -1 for infinite stacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int MaxStack;

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
	FItemConst();
	~FItemConst();
};

// Struct used to store the data of items in the world
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FItemData
{
public:
	GENERATED_BODY();

	/// -- Item Data --
	// The ID of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ItemID;

	// The display name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString Name;

	/// -- Item Actives --
	// The current amount of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actives")
	int Amount;

	// The order this item is placed in an inventory (useful for sorting by newest/oldest)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actives")
	int Order = -1;

	/// -- Item Upgrades --
	// Any upgrade tags applied to the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Upgrades")
	TArray<FString> UpgradeTags;

	/// -- Constructors
	FItemData();
	~FItemData();
	FItemData(FName InItemID, FString InName, int InAmount, int InOrder);

	/// -- Additional Functions --
	// Called to add items to an existing FItemData
	int AddItems(FName NewItemID, int AmountToAdd, int MaxStack);

	// Called to remove items from an existing FItemData
	int RemoveItems(int InAmount);
};

// Struct used to store the data of items in the inventory
// Useful for sorted containers
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FInventoryTypeData
{
public:
	GENERATED_BODY();

	/// -- Item Data --
	// The main data of the items in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TArray<FItemData> Items;

	/// -- Constructors
	FInventoryTypeData();
	~FInventoryTypeData();
	FInventoryTypeData(TArray<FItemData> NewData);
};

// Struct holding the data of items
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FWeaponData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Item Data --
	// The main data of the item
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	//FItemData ItemData;

	/// -- Weapon Stats --
	// The ID of the ammo this weapon uses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	FName AmmoID;

	// The damage of the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	int Damage;

	// Float denoting the units crit chance (chance to increase weapon damage) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float CritChance = 0.0f;

	// Float denoting the units crit damage (the amount to increase the base damage by when criting) 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float CritDamage = 1.0f;

	// Float denoting the duration the unit takes to reach maximum accuracy 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float AccuracyChargeTime = 0.0f;

	// Float denoting the minimum (empty charge) accuracy chance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float MinAccuracy = 0.0f;

	// Float denoting the maximum (full charge) accuracy chance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float MaxAccuracy = 0.0f;

	// Int denoting the unit's maximum range (in uu)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	int Range = 0;

	// Float denoting the duration of time between each shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float FireRate = 0.0f;
};

// Struct holding the data of items
USTRUCT(BlueprintType, Category = "Items")
struct SINGLEINPUTCHARACTER_API FConsumableData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Consumable Stats --
	// The type of consumable this item is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	TEnumAsByte<EConsumableType> BuffType;

	// The stat type of the consumable (health, armour, damage)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	FString StatTag = "None";

	// The base stat modification of the buff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	float BaseStat;

	// The multiplier/percent of the base stat modification buff 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	float Multiplier;

	// The duration of the buff (-1 for instant)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	float Duration;

	// The tick rate of the buff (how long between each buff additions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable Data")
	float TickRate;
};
