// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

#include "SingleInputUI.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USingleInputUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable)
	void SwapToCraftingUI();

	// Button event to swap to the Inventory State
	UFUNCTION()
	void OnInventoryButtonRelased();

	// Button event to swap to the Crafting State
	UFUNCTION()
	void OnCraftingStateReleased();

	// Called to swap to the InGame State (no active UI)
	void CloseMenuUI();

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

public:
	/// -- References --
	// Reference to the SingleInputPerson
	UPROPERTY(BlueprintReadOnly, Category = "References")
	class ASingleInputPerson* SingleInputPerson = nullptr;

	// Pointer to the current active state
	class UParentState* CurrentUIState = nullptr;

	/// -- Components --
	// Widget switcher that allows the UI to swap between different states
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* UISwitcher = nullptr;

	/// -- UI States --
	// The inventory state
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	class UInventoryUI* InventoryState = nullptr;

	// The crafting state
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	class UCraftingUI* CraftingState = nullptr;

	/// -- In Game Components
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
