// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#include "SI_PlayerCharacter.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASI_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASI_PlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// -- Camera --
	// Called to swap between the two camera angles.  Call SetCameraAngle to directly set to a certain angle.
	void SwapCameraAngle();

	// Called to rotate the camera by CameraRotationStep in a direction.  True if rotation is clockwise.
	void RotateCameraByStep(bool bRotateClockwise);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	// Camera Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraSpringArm = nullptr;

	// Inventory Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* InventoryComponent;

	// Crafting Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UCraftingComponent* CraftingComponent;


protected:
	/// -- Camera --
	// Bool to denote if the camera is currently in overhead view
	bool bInOverheadView = true;

	// Float to denote the overhead camera angle's pitch
	float OverheadCameraAngle = -90.0f;

	// Float to denote the 2.5D (or standard) camera angle's pitch
	float StandardCameraAngle = -45.0f;

	// Float to denote rotation step value
	float RotationStep = 10;

	// Int denoting the current rotation step multiplier
	// Incremented when rotating clockwise, or decremented when counterclockwise
	int CurrentStep = 0;
};
