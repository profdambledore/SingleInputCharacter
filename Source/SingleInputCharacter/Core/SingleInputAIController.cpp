// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputAIController.h"

#include "Core/ParentItem.h"
#include "Core/ParentStation.h"

ASingleInputAIController::ASingleInputAIController()
{
	// Find and store the Behaviour Tree
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/Core/AI/BT_Player"));
	if (BTObject.Succeeded()) { BT = BTObject.Object; }

	// Create the components for the AI
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ASingleInputAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ASingleInputAIController::OnPossess(APawn* InPawn)
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

void ASingleInputAIController::SetPCBlackboardValue(UObject* InController)
{
	BBC->SetValueAsObject(FName("PlayerController"), InController);
}

void ASingleInputAIController::MoveState(FVector InLoc)
{
	// Clear the state to stop any other commands currently firing
	BBC->SetValueAsString(FName("State"), "");

	BBC->SetValueAsVector(FName("TargetLocation"), InLoc);
	BBC->SetValueAsString(FName("State"), "Move");
}

void ASingleInputAIController::PickupItemState(AParentItem* ItemToCollect)
{
	BBC->SetValueAsString(FName("State"), "PickupItem");
	BBC->SetValueAsObject(FName("PickupItem"), ItemToCollect);

}

void ASingleInputAIController::CraftStationState(AParentStation* StationToAccess)
{
	BBC->SetValueAsString(FName("State"), "CraftAtStation");
	BBC->SetValueAsObject(FName("PickupItem"), StationToAccess);
}
