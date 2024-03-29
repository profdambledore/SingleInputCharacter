// Fill out your copyright notice in the Description page of Project Settings.

#include "World/ParentCraftingStation.h"

#include "Core/SI_PlayerController.h"
#include "Character/CraftingComponent.h"
#include "Core/SI_PlayerCharacter.h"
#include "UI/SI_PlayerUI.h"

// Sets default values
AParentCraftingStation::AParentCraftingStation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Station Mesh"));
}

// Called when the game starts or when spawned
void AParentCraftingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentCraftingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentCraftingStation::UseInteractable(class AController* User)
{
	// Figure out if the user is a AI or a Player
	if (User->IsA(ASI_PlayerController::StaticClass())) {
		// Cast to the PlayerController
		ASI_PlayerController* PC = Cast<ASI_PlayerController>(User);
		PC->GetAICharacter()->CraftingComponent->SetActiveStation(Type);
		PC->GetPlayerUI()->SwapActiveUIState("Crafting");
	}
}

