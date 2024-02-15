// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ParentItem.h"

#include "Components/StaticMeshComponent.h"

#include "CommonItem.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ACommonItem : public AParentItem
{
	GENERATED_BODY()

public:
	// Constructor
	ACommonItem();

	// -- Setup --
	// Called to setup a new item
	virtual void SetupItem(FItemData NewItemData) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// -- Components --
	// Static Mesh Component for the items static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh = nullptr;

};
