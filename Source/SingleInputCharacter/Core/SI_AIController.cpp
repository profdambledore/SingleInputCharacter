// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SI_AIController.h"

#include "Item/ParentItem.h"
#include "World/ParentCraftingStation.h"

ASI_AIController::ASI_AIController()
{
	// Find and store the Behaviour Tree
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/Core/AI/BT_Player"));
	if (BTObject.Succeeded()) { BT = BTObject.Object; }

	// Create the components for the AI
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ASI_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASI_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Check if the InPawn is valid and that the BT has been set
	if (InPawn && BT) {
		// Initialize the BlackboardComponent with BT's BlackboardAsset
		BBC->InitializeBlackboard(*BT->BlackboardAsset);

		// Set the SelfActor in the Blackboard
		BBC->SetValueAsObject(FName("SelfActor"), InPawn);

		// Start the BT BehaviorTree
		BTC->StartTree(*BT);
	}
}

void ASI_AIController::SetPCBlackboardValue(UObject* InController)
{
	BBC->SetValueAsObject(FName("PlayerController"), InController);
}

void ASI_AIController::SetActiveStateToMove(FVector InLoc)
{
	// Clear the state to stop any other commands currently firing
	BBC->SetValueAsString(FName("State"), "");

	BBC->SetValueAsVector(FName("TargetLocation"), InLoc);
	BBC->SetValueAsString(FName("State"), "Move");
}

void ASI_AIController::SetActiveStateToPickup(AParentItem* ItemToCollect)
{
	BBC->SetValueAsString(FName("State"), "PickupItem");
	BBC->SetValueAsObject(FName("ObjectInUse"), ItemToCollect);
}

void ASI_AIController::SetActiveStateToStation(AActor* StationToAccess)
{
	BBC->SetValueAsString(FName("State"), "UseInteractable");
	BBC->SetValueAsObject(FName("ObjectInUse"), StationToAccess);
}
