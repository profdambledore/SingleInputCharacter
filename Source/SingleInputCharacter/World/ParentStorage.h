// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ParentInteractable.h"

#include "Components/StaticMeshComponent.h"
#include "Character/InventoryComponent.h"

#include "ParentStorage.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AParentStorage : public AParentInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParentStorage();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseInteractable(class AController* User) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// -- Components --
	// Static Mesh Component for the items static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StationMesh = nullptr;

	// Inventory Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* InventoryComponent;

	/// -- Storage Properties --
	// String denoting the storages name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage Properties")
	FString StorageName;
	
};
