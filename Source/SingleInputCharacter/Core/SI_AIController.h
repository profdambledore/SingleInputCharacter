// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SI_AIController.generated.h"

UCLASS()
class SINGLEINPUTCHARACTER_API ASI_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Constructor
	ASI_AIController();

	// Called when the AI Possesses a character
	virtual void OnPossess(APawn* InPawn) override;

	// Called to update the BehavoirTree with the PlayerController value
	//void SetPCBlackboardValue(UObject* InController);

	/// -- States --
	// Called to change the AI state to Move
	void SetActiveStateToMove(FVector InLoc);

	// Called to change the AI state to PickupItem
	void SetActiveStateToPickup(class AParentItem* ItemToCollect);

	// Called to change the AI state to MoveToCraftingStation
	void SetActiveStateToStation(class AParentCraftingStation* StationToAccess);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// -- AI Assets --
	// Behaviour Tree for the Person
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Assets")
	UBehaviorTree* BT = nullptr;

	// Behavior Tree Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
	UBehaviorTreeComponent* BTC = nullptr;

	// Blackboard Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
	UBlackboardComponent* BBC = nullptr;
};
