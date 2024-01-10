// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "Core/Data/ItemData.h"

#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to un-select this slot
	void UnSelectSlot();

protected:
	/// -- Button Functions --
	UFUNCTION()
	void OnInventorySlotButtonRelease();

public:
	/// -- Components --
	// Button to update the currently selected item to this one
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Components")
	UButton* SelectItemButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	FItemData SlotItem;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Item")
	class UInventoryUI* InventoryUI = nullptr;
};
