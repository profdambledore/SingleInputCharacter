// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentInteractable.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API AParentInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentInteractable();

	/// -- Interactables --
	// Called to access the interactable
	UFUNCTION(BlueprintCallable)
	virtual void UseInteractable(class AController* User);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
