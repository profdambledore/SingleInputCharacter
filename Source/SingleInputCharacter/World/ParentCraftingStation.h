// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Data/CraftingData.h"

#include "ParentCraftingStation.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AParentCraftingStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentCraftingStation();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	// Static Mesh Component for the items static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StationMesh = nullptr;

	/// -- Station Data --
	// Enum denoting the type of station
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Stats")
	TEnumAsByte<EStationType> Type;

};
