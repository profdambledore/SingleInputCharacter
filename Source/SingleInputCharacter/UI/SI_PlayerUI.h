// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/WidgetSwitcher.h"

#include "SI_PlayerUI.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API USI_PlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to setup the UI states with their correct properties
	void SetupUIStates(class ASI_PlayerCharacter* PlayerCharacter);

	// Called to swap to a new state
	UFUNCTION(BlueprintCallable)
	void SwapActiveUIStateIndex(int Index);

	UFUNCTION(BlueprintCallable)
	void SwapActiveUIState(FString StateName);

public:
	/// -- Components --
	// Widget switcher that allows the UI to swap between different states
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* StateSwitcher = nullptr;

	/// -- UI States --
	// State displaying the in-game hud
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	class USI_InGameState* InGameState = nullptr;

	// State displaying the inventory menu
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	class USI_InventoryState* InventoryState = nullptr;

	// State displaying the crafing menu
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	class USI_CraftingState* CraftingState = nullptr;


protected:
	// Pointer to the current active state
	USI_ParentState* CurrentState = nullptr;
};
