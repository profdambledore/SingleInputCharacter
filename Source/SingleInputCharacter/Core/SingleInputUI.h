// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "SingleInputUI.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USingleInputUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

protected:
	/// -- Button Functions --
	UFUNCTION()
	void OnCameraAngleButtonReleased();

	UFUNCTION()
	void OnCWRotateCameraButtonReleased();

	UFUNCTION()
	void OnACRotateCameraButtonReleased();

public:
	/// -- References --
	// Reference to the SingleInputPerson
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class ASingleInputPerson* SingleInputPerson = nullptr;

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
};
