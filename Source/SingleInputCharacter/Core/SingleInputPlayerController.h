// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "SingleInputPlayerController.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASingleInputPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	// Default Construcot
	ASingleInputPlayerController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	/// -- Inputs --
	// Called to make the player interact with the world
	void PlayerInteract(const FInputActionValue& Value);

	/// -- Debug Inputs --
	// Debug - Rotate Camera by a set step
	void DEBUG_RotateCamera(const FInputActionValue& Value);

	// Debug - Change camera pitch between the two bounds
	void DEBUG_AngleCamera(const FInputActionValue& Value);


protected:
	/// -- Player --
	// Pointer to the pawn that this player controller possesses
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASingleInputPlayer* OwnedPawn = nullptr;

	// Pointer to the character that the player controls
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASingleInputPerson* AICharacter = nullptr;

	// Pointer to the AIController controlling the AICharacter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASingleInputAIController* AIControl = nullptr;

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

private:


};
