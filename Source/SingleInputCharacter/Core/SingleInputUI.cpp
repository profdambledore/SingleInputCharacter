// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputUI.h"
#include "Core/SingleInputPerson.h"

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
}

void USingleInputUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USingleInputUI::OnCameraAngleButtonReleased()
{
	if (SingleInputPerson) {
		SingleInputPerson->SwapCameraAngle();
	}
}

void USingleInputUI::OnCWRotateCameraButtonReleased()
{
	if (SingleInputPerson) {
		SingleInputPerson->RotateCameraByStep(true);
	}
}

void USingleInputUI::OnACRotateCameraButtonReleased()
{
	if (SingleInputPerson) {
		SingleInputPerson->RotateCameraByStep(false);
	}
}
