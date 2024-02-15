// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SI_ParentState.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API USI_ParentState : public UUserWidget
{
	GENERATED_BODY()

public:
	/// -- Parent State --
	// Called when a state is activated
	virtual void OnStateActive();

	// Called when a state is deactivated
	virtual void OnStateDeactivate();

public:
	/// -- Pointers --
	// Pointer to the main PlayerUI that this state is a component of
	class USI_PlayerUI* StateOwner = nullptr;
};
