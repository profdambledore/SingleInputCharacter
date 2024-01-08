// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputPlayerController.h"
#include "Core/SingleInputPlayer.h"
#include "Core/SingleInputAIController.h"
#include "Core/SingleInputPerson.h"

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
}

void ASingleInputPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Cast to this controller's character
	//OwnedPawn = Cast<ASingleInputPlayer>(GetPawn());

	// Next, spawn the AICharacter
	//AICharacter = GetWorld()->SpawnActor<ASingleInputPerson>(ASingleInputPerson::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());

	// Then spawn it's controller and make it possess the person
	//AIControl = GetWorld()->SpawnActor<ASingleInputAIController>(ASingleInputAIController::StaticClass(), FVector(), FRotator(), FActorSpawnParameters());
	//AIControl->Possess(AICharacter);

	// Setup OwnedPawn on the AICharacter's spring arm
	//OwnedPawn->CharacterCamera->SetupAttachment(AICharacter->CameraSpringArm, "");
	
	// Set the mouse viewable on screen
	//bShowMouseCursor = true;

	/// Attempt One - Spawn Character, then set
	// Spawn this controllers Character
	//OwnedCharacter = GetWorld()->SpawnActor<ASingleInputPlayer>(ASingleInputPlayer::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator());
	//if (OwnedCharacter) {
		//SetViewTargetWithBlend(OwnedCharacter, 0.5f);
	//}
}

void ASingleInputPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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
		EnhancedInputComponent->BindAction(InputConfig->Debug_CameraRotate, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_RotateCamera);
		EnhancedInputComponent->BindAction(InputConfig->Debug_CameraAngle, ETriggerEvent::Triggered, this, &ASingleInputPlayerController::DEBUG_AngleCamera);
	}
}

void ASingleInputPlayerController::PlayerInteract(const FInputActionValue& Value)
{
	if (AICharacter) {
		FVector MouseWorldLocation; FVector MouseWorldDirection;
		DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		//AICharacter->MoveToLocation(MouseWorldLocation);
	}
}

void ASingleInputPlayerController::DEBUG_RotateCamera(const FInputActionValue& Value)
{
	if (bDebug && AICharacter) {
		const float InputValue = Value.Get<float>();

		UE_LOG(LogTemp, Warning, TEXT("%f"), InputValue);

		if (InputValue < 0) {
			AICharacter->RotateCameraByStep(false);
		}
		else if (InputValue > 0) {
			AICharacter->RotateCameraByStep(true);
		}
	}
}

void ASingleInputPlayerController::DEBUG_AngleCamera(const FInputActionValue& Value)
{
	if (bDebug && AICharacter) {
		AICharacter->SwapCameraAngle();
	}
}

///
/// https://unrealistic.dev/posts/binding-input-in-c
/// https://nightails.com/2022/10/16/unreal-engine-enhanced-input-system-in-c/
/// https://docs.unrealengine.com/5.3/en-US/API/Plugins/EnhancedInput/UEnhancedInputComponent/
/// https://docs.unrealengine.com/5.3/en-US/enhanced-input-in-unreal-engine/
///