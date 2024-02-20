// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ParentStorage.h"

#include "Core/SI_PlayerController.h"
#include "Core/SI_PlayerCharacter.h"
#include "UI/SI_PlayerUI.h"
#include "UI/SI_StorageState.h"

// Sets default values
AParentStorage::AParentStorage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Station Mesh"));

	// Add the InventoryComponent to the character
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryComponent->InventoryOwner = this;
}

// Called when the game starts or when spawned
void AParentStorage::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AParentStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentStorage::UseInteractable(class AController* User)
{
	// Figure out if the user is a AI or a Player
	if (User->IsA(ASI_PlayerController::StaticClass())) {
		// Cast to the PlayerController
		ASI_PlayerController* PC = Cast<ASI_PlayerController>(User);
		PC->GetPlayerUI()->SwapActiveUIState("Storage");
		PC->GetPlayerUI()->StorageState->DisplayInventoryItems(InventoryComponent);
	}
}