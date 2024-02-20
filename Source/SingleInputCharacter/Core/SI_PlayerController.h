// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "SI_PlayerController.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASI_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Constructor
	ASI_PlayerController();

	// Called to setup the inputs for this player controller
	virtual void SetupInputComponent() override;

	/// -- Character --
	// Called to return the character pointer
	ASI_PlayerCharacter* GetAICharacter();

	/// -- UI --
	// Called to return the UI pointer
	UFUNCTION(BlueprintCallable)
	USI_PlayerUI* GetPlayerUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Inputs --
	// Called to make the player interact with the world
	void InputAction(const FInputActionValue& Value);

protected:
	/// -- Player --
	// Pointer to the pawn that this player controller possesses
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASI_PlayerClass* PlayerClass = nullptr;

	// Pointer to the character that the player controls
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASI_PlayerCharacter* AICharacter = nullptr;

	// Pointer to the AIController controlling the AICharacter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASI_AIController* AIControl = nullptr;

	/// -- UI --
	// Pointer to the UI added to the viewport
	class USI_PlayerUI* UI = nullptr;

	/// -- Inputs --
	// Pointer to the Input Config File
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping = nullptr;

	/// -- Debug Mode --
	// Bool denoting if this controller is in debug mode or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebug = true;
};
