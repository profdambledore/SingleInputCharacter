// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InGameState.h"

#include "Core/SI_PlayerCharacter.h"
#include "UI/SI_PlayerUI.h"

void USI_InGameState::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Camera Button Binds
	CameraAngleButton->OnReleased.AddDynamic(this, &USI_InGameState::OnCameraAngleButtonReleased);
	CWRotateCameraButton->OnReleased.AddDynamic(this, &USI_InGameState::OnCWRotateCameraButtonReleased);
	ACRotateCameraButton->OnReleased.AddDynamic(this, &USI_InGameState::OnACRotateCameraButtonReleased);
	
	// Inventopry Button Release
	InventoryButton->OnReleased.AddDynamic(this, &USI_InGameState::OnInventoryButtonReleased);

	// Inventopry Button Release
	CraftingButton->OnReleased.AddDynamic(this, &USI_InGameState::OnCraftingButtonReleased);
}

void USI_InGameState::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USI_InGameState::OnStateActive()
{
}

void USI_InGameState::OnStateDeactivate()
{
}

void USI_InGameState::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	PlayerHealthBar->SetPercent(CurrentHealth / MaxHealth);
	PlayerHealthText->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), FMath::FloorToInt(CurrentHealth), FMath::FloorToInt(MaxHealth))));
}

void USI_InGameState::UpdateAmmoCount(int AmmoTotal)
{
	if (AmmoTotal != -1) {
		WeaponAmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%i"), AmmoTotal)));
	}
	else {
		WeaponAmmoCount->SetText(FText::FromString(FString::Printf(TEXT(""))));
	}
}

void USI_InGameState::OnCameraAngleButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (PlayerCharacter) {
		// Swap the camera angles
		PlayerCharacter->SwapCameraAngle();
	}
}

void USI_InGameState::OnCWRotateCameraButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (PlayerCharacter) {
		// Rotate the camera clockwise
		PlayerCharacter->RotateCameraByStep(true);
	}
}

void USI_InGameState::OnACRotateCameraButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (PlayerCharacter) {
		// Rotate the camera counterclockwise
		PlayerCharacter->RotateCameraByStep(false);
	}
}

void USI_InGameState::OnInventoryButtonReleased()
{
	if (PlayerUI) {
		PlayerUI->SwapActiveUIState("Inventory");
	}
}

void USI_InGameState::OnCraftingButtonReleased()
{
	if (PlayerUI) {
		PlayerUI->SwapActiveUIState("Crafting");
	}
}
