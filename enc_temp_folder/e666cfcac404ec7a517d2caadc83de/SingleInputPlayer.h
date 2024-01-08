// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "SingleInputPlayer.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASingleInputPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASingleInputPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// -- Character --
	// Called to move the character to a position in the world
	void MoveToLocation(FVector NewLocation);

	// Called to rotate the character to face a direction.  Useful when interacting with items or shooting weapons
	// void RotateToFaceLocation(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	// Camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CharacterCamera = nullptr;

	/// -- Character --
	// Float to denote movement range (maximum distance a input can be before it is registered as an iteract rather than a move command)
	// float MovementRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ref")
	class ASingleInputAIController* AI = nullptr;

protected:

};
