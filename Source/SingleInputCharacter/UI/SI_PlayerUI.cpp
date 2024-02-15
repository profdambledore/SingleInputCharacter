// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_PlayerUI.h"

#include "UI/SI_InGameState.h"
#include "UI/SI_InventoryState.h"
#include "UI/SI_CraftingState.h"
#include "Core/SI_PlayerCharacter.h"
#include "Character/InventoryComponent.h"
#include "Character/CraftingComponent.h"

void USI_PlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void USI_PlayerUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void USI_PlayerUI::SetupUIStates(ASI_PlayerCharacter* PlayerCharacter)
{
	// Setup the In-Game State
	InGameState->PlayerCharacter = PlayerCharacter;
	InGameState->PlayerUI = this;

	// Setup the Inventory State
	InventoryState->PlayerUI = this;
	InventoryState->Inventory = PlayerCharacter->InventoryComponent;

	// Setup the Crating State
	CraftingState->PlayerUI = this;
	CraftingState->Crafting = PlayerCharacter->CraftingComponent;
	CraftingState->Inventory = PlayerCharacter->InventoryComponent;
}

void USI_PlayerUI::SwapActiveUIStateIndex(int Index)
{
	if (Index != StateSwitcher->GetActiveWidgetIndex()) {
		CurrentState->OnStateDeactivate();
		StateSwitcher->SetActiveWidgetIndex(Index);
		switch (Index) {
		case 0:
			InGameState->OnStateActive();
			break;

		case 1:
			InventoryState->OnStateActive();
			break;

		case 2:
			CraftingState->OnStateActive();
			break;

		default:
			break;
		}
	}
}

void USI_PlayerUI::SwapActiveUIState(FString StateName)
{
	if (StateName == "InGame") {
		if (CurrentState != InGameState) {
			if (CurrentState) {
				CurrentState->OnStateDeactivate();
			}
			StateSwitcher->SetActiveWidgetIndex(0);
			InGameState->OnStateActive();
		}
	}
	else if (StateName == "Inventory") {
		if (CurrentState != InventoryState) {
			if (CurrentState) {
				CurrentState->OnStateDeactivate();
			}
			StateSwitcher->SetActiveWidgetIndex(1);
			InventoryState->OnStateActive();
		}
	}
	else if (StateName == "Crafting") {
		if (CurrentState != CraftingState) {
			if (CurrentState) {
				CurrentState->OnStateDeactivate();
			}
			StateSwitcher->SetActiveWidgetIndex(2);
			CraftingState->OnStateActive();
		}
	}
}
