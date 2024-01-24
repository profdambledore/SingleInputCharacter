// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputPlayerController.h"
#include "Core/SingleInputPlayer.h"
#include "Core/SingleInputAIController.h"
#include "Core/SingleInputPerson.h"
#include "Core/SingleInputUI.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/InputConfigData.h"

ASingleInputPlayerController::ASingleInputPlayerController()
{
	// Find the input objects
	// First, find the Input Context Data
	ConstructorHelpers::FObjectFinder<UInputConfigData>ICDObject(TEXT("/Game/Core/Inputs/ICD_SingleInput"));
	if (ICDObject.Succeeded()) { InputConfig = ICDObject.Object; }

	// Last, find the Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>IMCObject(TEXT("/Game/Core/Inputs/IMC_SingleInput"));
	if (IMCObject.Succeeded()) { InputMapping = IMCObject.Object; }

	// Find the UI object and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Core/UI/WBP_SingleInputUI"));
	if (UIClass.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("UI Found"));
		UI = CreateWidget<USingleInputUI>(GetWorld(), UIClass.Class);
	};
}

void ASingleInputPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cast to this controller's character
	OwnedPawn = Cast<ASingleInputPlayer>(GetPawn());

	// Next, spawn the AICharacter
	AICharacter = GetWorld()->SpawnActor<ASingleInputPerson>(ASingleInputPerson::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());

	// Then spawn it's controller and make it possess the person
	AIControl = GetWorld()->SpawnActor<ASingleInputAIController>(ASingleInputAIController::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());
	AIControl->Possess(AICharacter);
	AIControl->SetPCBlackboardValue(this);
	AICharacter->AI = AIControl;

	// Setup OwnedPawn on the AICharacter's spring arm
	OwnedPawn->AttachToComponent(AICharacter->CameraSpringArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "");
	// Set the mouse viewable on screen
	bShowMouseCursor = true;

	// Add the UI to thew viewport
	if (UI) {
		UI->AddToViewport();
		UI->SingleInputPerson = AICharacter;
	}
}

void ASingleInputPlayerController::SetupInputComponent()
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
		EnhancedInputComponent->BindAction(InputConfig->InputPlayerAction, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::PlayerInteract);

		// Bind any test actions
		EnhancedInputComponent->BindAction(InputConfig->Debug_CameraRotate, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_Inventory);
		EnhancedInputComponent->BindAction(InputConfig->Debug_CameraAngle, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_AngleCamera);
	}
}

void ASingleInputPlayerController::OpenCraftingMenu()
{
	UI->SwapToCraftingUI();
}

// Called to make the player interact with the world
void ASingleInputPlayerController::PlayerInteract(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Firing"));

	// Check that the AICharacter is valid
	if (AICharacter) {
		// If so, deproject the mouse to world space and call MoveToLocation on the AICharacter
		FVector MouseWorldLocation; FVector MouseWorldDirection;
		DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		AICharacter->MoveToLocation(MouseWorldLocation, MouseWorldDirection);
	}
}

// Debug - Rotate Camera by a set step
void ASingleInputPlayerController::DEBUG_RotateCamera(const FInputActionValue& Value)
{
	// Check if the player is in debug mode and AICharacter is valid
	if (bDebug && AICharacter) {
		// Get the float value from the FInputActionValue reference
		const float InputValue = Value.Get<float>();

		// If it is less than 0, rotate counterclockwise
		if (InputValue < 0) {
			AICharacter->RotateCameraByStep(false);
		}
		// Else, if it is greater than 0 rotate clockwise
		else if (InputValue > 0) {
			AICharacter->RotateCameraByStep(true);
		}
	}
}

// Debug - Change camera pitch between the two bounds
void ASingleInputPlayerController::DEBUG_AngleCamera(const FInputActionValue& Value)
{
	// Check if the player is in debug mode and AICharacter is valid
	if (bDebug && AICharacter) {
		// Call SwapCameraAngle in AICharacter
		AICharacter->SwapCameraAngle();
	}
}

// Debug - Open the inventory screen
void ASingleInputPlayerController::DEBUG_Inventory(const FInputActionValue& Value)
{
	// Check if the player is in debug mode and AICharacter is valid
	if (bDebug && AICharacter) {
		// Call OnInventoryButtonRelase in the UI to show the inventory state
		UI->OnInventoryButtonRelased();
	}
}


///
/// https://unrealistic.dev/posts/binding-input-in-c
/// https://nightails.com/2022/10/16/unreal-engine-enhanced-input-system-in-c/
/// https://docs.unrealengine.com/5.3/en-US/API/Plugins/EnhancedInput/UEnhancedInputComponent/
/// https://docs.unrealengine.com/5.3/en-US/enhanced-input-in-unreal-engine/
///