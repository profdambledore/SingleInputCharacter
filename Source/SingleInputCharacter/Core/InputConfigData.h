// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "InputAction.h"

#include "InputConfigData.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	/// -- In-Game --
	// Pointer to the only player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputPlayerAction = nullptr;

	/// -- Testing --
	// Pointer to camera rotation input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test Input")
	class UInputAction* Debug_CameraRotate = nullptr;

	// Pointer to camera angle input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test Input")
	class UInputAction* Debug_CameraAngle = nullptr;
	
};
