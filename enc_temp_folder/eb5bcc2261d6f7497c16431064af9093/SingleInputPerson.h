// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#include "SingleInputPerson.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASingleInputPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASingleInputPerson();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// -- Camera --
	// Called to swap between the two camera angles.  Call SetCameraAngle to directly set to a certain angle.
	void SwapCameraAngle();

	// Called to swap to a set camera angle.  Call SwapCameraAngle to flip-flop between the two angles.
	// void SetCameraAngle(bool bOverheadView);

	// Called to rotate the camera by CameraRotationStep in a direction.  True if rotation is clockwise.
	void RotateCameraByStep(bool bRotateClockwise);

	// Called to set the camera rotation to a direct value, then round to the nearest step.
	// void RotateCameraToAngle(float NewAngle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	// Camera Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraSpringArm = nullptr;

protected:
	/// -- Camera --
	// Bool to denote if the camera is currently in overhead view
	bool bInOverheadView = false;

	// Float to denote the overhead camera angle's pitch
	float OverheadCameraAngle = -90.0f;

	// Float to denote the 2.5D (or standard) camera angle's pitch
	float StandardCameraAngle = -50.0f;

	// Float to denote rotation speed
	float CameraRotationSpeed = 3.0f;

	// Float to denote rotation step value
	float RotationStep = 10;
};
