// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Core/Data/ItemData.h"

#include "ParentItem.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AParentItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// -- Setup --
	// Called to setup a new item
	virtual void SetupItem(FItemData NewItemData);

	// -- As Pickup --
	// Called to collect the item and add it to the player's inventory
	UFUNCTION(BlueprintCallable)
	void PickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- References --
	// Pointer to the owner if one exists - if this pointer is nullptr it is classed as a pickup instead
	AActor* Owner = nullptr;

	// -- Item Data --
	// FItemData which contains the item data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FItemData ItemData;

};
