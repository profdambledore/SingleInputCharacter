// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputUI.h"
#include "Core/SingleInputPerson.h"
#include "UI/InventoryUI.h"

// Called on construct to setup the widget
void USingleInputUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup the button binds
	// Camera Angle Button
	CameraAngleButton->OnReleased.AddDynamic(this, &USingleInputUI::OnCameraAngleButtonReleased);

	// Clockwise Rotate Button
	CWRotateCameraButton->OnReleased.AddDynamic(this, &USingleInputUI::OnCWRotateCameraButtonReleased);

	// Anti-Clockwise Rotate Button
	ACRotateCameraButton->OnReleased.AddDynamic(this, &USingleInputUI::OnACRotateCameraButtonReleased);

	InventoryState->MainUI = this;
}

// Called to update the properties of the widget
void USingleInputUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

/// -- Button Events --
// Button event to swap between the two camera angles
void USingleInputUI::OnCameraAngleButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (SingleInputPerson) {
		// Swap the camera angles
		SingleInputPerson->SwapCameraAngle();
	}
}

// Button event to rotate the camera clockwise
void USingleInputUI::OnCWRotateCameraButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (SingleInputPerson) {
		// Rotate the camera clockwise
		SingleInputPerson->RotateCameraByStep(true);
	}
}

// Button event to rotate the camera counterclockwise
void USingleInputUI::OnACRotateCameraButtonReleased()
{
	// Check if the SingleInputPerson is valid
	if (SingleInputPerson) {
		// Rotate the camera counterclockwise
		SingleInputPerson->RotateCameraByStep(false);
	}
}

// Called to swap to the Inventory State
void USingleInputUI::OnInventoryButtonRelased()
{
	// Check if the SingleInputPerson is valid
	if (SingleInputPerson) {
		// Syncronize the properties in the Inventory and update the active widget
		InventoryState->SynchronizeProperties();
		UISwitcher->SetActiveWidgetIndex(1);
	}
}
