// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ParentItem.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/Texture2D.h"

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

	// Called to start a timer for weapon fire cooldown
	UFUNCTION(BlueprintCallable)
	void StartFireRateCooldown();

	// Called to end the timer for the weapons fire rate cooldown
	void EndFireRateCooldown();

	// Called to start a timer for the accuracy chance
	UFUNCTION(BlueprintCallable)
	void StartAccuracyIncrease();

	// Called to pause the accuracy chance 
	UFUNCTION(BlueprintCallable)
	void PauseAccuracyIncrease();

	// Called to end the accuracy chance
	UFUNCTION(BlueprintCallable)
	void EndAccuracyIncrease();

	// Timer function that increases the accuracy chance each tick
	void AccuracyIncreaseTick();

	// Called to return the current accuracy amount
	UFUNCTION(BlueprintCallable)
	float GetCurrentAccuracy();

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

	/// -- Weapon Actives --
	FTimerHandle FireRateHandle;

	FTimerHandle AccuracyHandle;

	float CurrentAccuracy;

	float AccuracyPerTick;

	// Bool denoting if the weapon can fire or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanFire = true;

	UTexture2D* WeaponIcon = nullptr;

};
