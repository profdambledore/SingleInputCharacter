// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ParentItem.h"

#include "Components/SkeletalMeshComponent.h"

#include "WeaponItem.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AWeaponItem : public AParentItem
{
	GENERATED_BODY()
	
public:
	// Constructor
	AWeaponItem();

	// -- Setup --
	// Called to setup a new item
	virtual void SetupItem(FItemData NewItemData) override;

	// Called to clear the weapon data
	void ClearWeapon();

	// -- Weapon Functions --
	// Called to return the weapon range
	float GetWeaponRange();

	// Called to return the ID of this weapon's ammo
	FName GetWeaponAmmoID();

	// Called to fire the weapon
	void FireWeapon(AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// -- Components --
	// Static Mesh Component for the items static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* ItemMesh = nullptr;

	/// -- Properties --
	// Weapon Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	FWeaponData WeaponData;

};
