// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_ParentState.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "SI_InGameState.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USI_InGameState : public USI_ParentState
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	/// -- Parent State --
	virtual void OnStateActive() override;

	virtual void OnStateDeactivate() override;

	// Called to update the health bar percent based on the SingleInputPerson's current health
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	// Called to update the weapon slot
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWeaponSlot(UTexture* InWeaponIcon);

	// Called to update the bullet count
	void UpdateAmmoCount(int AmmoTotal);

protected:
	/// -- Button Functions --
	// Button event to swap between the two camera angles
	UFUNCTION()
	void OnCameraAngleButtonReleased();

	// Button event to rotate the camera clockwise
	UFUNCTION()
	void OnCWRotateCameraButtonReleased();

	// Button event to rotate the camera counterclockwise
	UFUNCTION()
	void OnACRotateCameraButtonReleased();

	// Button event to rotate the camera counterclockwise
	UFUNCTION()
	void OnInventoryButtonReleased();

	// Button event to rotate the camera counterclockwise
	UFUNCTION()
	void OnCraftingButtonReleased();


public:
	/// -- Pointers
	// Reference to the SI_PlayerCharacter
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class ASI_PlayerCharacter* PlayerCharacter = nullptr;

	// Pointer to the PlayerUI, or the UI that this state is contained in
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class USI_PlayerUI* PlayerUI = nullptr;

	/// -- Components --
	// Button to toggle the camera angle
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CameraAngleButton = nullptr;

	// Button to rotate the camera clockwise
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CWRotateCameraButton = nullptr;

	// Button to rotate the camera clockwise
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* ACRotateCameraButton = nullptr;

	// Progress Bar to display the player's health
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UProgressBar* PlayerHealthBar = nullptr;

	// Text Box to display the player's health
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerHealthText = nullptr;

	/// -- Weapon Slot --
	// Text Box to display the weapons current ammo count
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* WeaponAmmoCount = nullptr;

	// Image to display the icon of the weapon
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UImage* WeaponIcon = nullptr;

	// Button to open the inventory state
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* InventoryButton = nullptr;

	// Button to open the inventory state
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* CraftingButton = nullptr;
};
