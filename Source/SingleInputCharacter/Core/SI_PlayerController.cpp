// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SI_PlayerController.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/SI_PlayerClass.h"
#include "Core/SI_PlayerCharacter.h"
#include "Core/SI_AIController.h"
#include "UI/SI_PlayerUI.h"
#include "Core/InputConfigData.h"
#include "Item/ParentItem.h"
#include "World/ParentInteractable.h"
#include "Character/StatsComponent.h"

// Constructor
ASI_PlayerController::ASI_PlayerController()
{
	// Find the input objects
	// First, find the Input Context Data
	ConstructorHelpers::FObjectFinder<UInputConfigData>ICDObject(TEXT("/Game/Core/Inputs/ICD_SingleInput"));
	if (ICDObject.Succeeded()) { InputConfig = ICDObject.Object; }

	// Last, find the Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>IMCObject(TEXT("/Game/Core/Inputs/IMC_SingleInput"));
	if (IMCObject.Succeeded()) { InputMapping = IMCObject.Object; }

	// Find the UI object and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Core/UI/WBP_PlayerUI"));
	if (UIClass.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("UI Found"));
		UI = CreateWidget<USI_PlayerUI>(GetWorld(), UIClass.Class);
	};
}

// Called when the game starts or when spawned
void ASI_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cast to this controller's character and store a pointer
	PlayerClass = Cast<ASI_PlayerClass>(GetPawn());

	// Next, spawn the AICharacter
	AICharacter = GetWorld()->SpawnActor<ASI_PlayerCharacter>(ASI_PlayerCharacter::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());

	// Then spawn it's controller and make it possess the person
	AIControl = GetWorld()->SpawnActor<ASI_AIController>(ASI_AIController::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());
	AIControl->Possess(AICharacter);
	AIControl->SetPCBlackboardValue(this);
	//AICharacter->AI = AIControl;

	// Setup the PlayerClass on the AICharacter's spring arm
	PlayerClass->AttachToComponent(AICharacter->CameraSpringArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "");

	// Add the UI to thew viewport
	if (UI) {
		UI->AddToViewport();
		UI->SetupUIStates(AICharacter);
		AICharacter->StatsComponent->PlayerUI = UI;
		AICharacter->StatsComponent->SetupStats();
	}

	// Set the mouse viewable on screen
	bShowMouseCursor = true;
}

// Called to setup the inputs for this player controller
void ASI_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if the input object pointers are valid
	if (InputConfig && InputMapping) {
		// Get and store the local player subsystem
		auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		// Then clear any existing mapping, then add the new mapping
		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

		// Get the EnhancedInputComponent
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		// Bind the click action
		EnhancedInputComponent->BindAction(InputConfig->InputPlayerAction, ETriggerEvent::Triggered, this, &ASI_PlayerController::InputAction);

		// Bind any test actions
		//EnhancedInputComponent->BindAction(InputConfig->Debug_CameraRotate, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_Inventory);
		//EnhancedInputComponent->BindAction(InputConfig->Debug_CameraAngle, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_AngleCamera);
	}
}

// Called to make the player interact with the world
void ASI_PlayerController::InputAction(const FInputActionValue& Value)
{
	// Check that the AICharacter is valid
	if (AICharacter) {
		// If so, deproject the mouse to world space and call MoveToLocation on the AICharacter
		FVector MouseWorldLocation; FVector MouseWorldDirection;
		DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		// Bool used to denote if a state change has happened during this trace
		bool bStateUpdate = false;

		// Calculate where a trace hits and move the character to the hit location if valid 
		FHitResult TraceHit;
		bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseWorldLocation, MouseWorldLocation + (MouseWorldDirection * 4000), ECC_WorldDynamic, FCollisionQueryParams(FName("DistTrace"), true));

		// Compare what the trace hit
		// If the trace hit a item, check that it doesn't have a owner already
		if (TraceHit.GetActor() != nullptr) {
			if (TraceHit.GetActor()->IsA(AParentItem::StaticClass())) {
				UE_LOG(LogTemp, Warning, TEXT("Hit Item"));
				AParentItem* HitItem = Cast<AParentItem>(TraceHit.GetActor());
				if (HitItem->Owner == nullptr) {
					// Move to the item and pick it up
					AIControl->SetActiveStateToPickup(HitItem);
					bStateUpdate = true;
				}
			}
			// Else, check if the trace hit a interactable
			if (TraceHit.GetActor()->IsA(AParentInteractable::StaticClass())) {
				//AParentInteractable* HitStation = Cast<AParentCraftingStation>(TraceHit.GetActor());
				AIControl->SetActiveStateToStation(TraceHit.GetActor());
				bStateUpdate = true;
			}
			else if (!bStateUpdate) {
				AIControl->SetActiveStateToMove(TraceHit.Location);
			}
		}
	}
}

ASI_PlayerCharacter* ASI_PlayerController::GetAICharacter()
{
	return AICharacter;
}

USI_PlayerUI* ASI_PlayerController::GetPlayerUI()
{
	return UI;
}

///
/// https://unrealistic.dev/posts/binding-input-in-c
/// https://nightails.com/2022/10/16/unreal-engine-enhanced-input-system-in-c/
/// https://docs.unrealengine.com/5.3/en-US/API/Plugins/EnhancedInput/UEnhancedInputComponent/
/// https://docs.unrealengine.com/5.3/en-US/enhanced-input-in-unreal-engine/
///