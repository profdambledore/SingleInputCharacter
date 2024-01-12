// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"

#include "ItemDisplay.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AItemDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDisplay();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Mesh Target --
	// Called to set a new mesh as the Display's target
	UFUNCTION()
	void SetNewMeshTarget(UStaticMesh* InStaticMesh, USkeletalMesh* InSkelMesh, float InSpringArmLength);

	// Called to clear both mesh components
	void ClearMeshTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	// Static Mesh Component used to display static mesh items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshDisplay_Static = nullptr;

	// Skeletal Mesh Component used to display skeletal mesh items
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshDisplay_Skel = nullptr;

	// Spring Arm Component used to move the display capture back from the meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* DisplaySpringArm = nullptr;

	// SceneCaptureComponent used to record and save the icon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneCaptureComponent2D* DisplayCapture = nullptr;



};
