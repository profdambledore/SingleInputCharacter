// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SingleInputPerson.h"
#include "Core/SingleInputAIController.h"
#include "Core/SingleInputInventory.h"
#include "Core/SingleInputCraftingComponent.h"
#include "Core/ParentItem.h"
#include "UI/ItemDisplay.h"

// Sets default values
ASingleInputPerson::ASingleInputPerson()
{
	// Setup Mesh 
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Setup the spring arm for the SingleInputPlayer to attach to
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Character Spring Arm"));
	CameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CameraSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 2000.0f;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetupAttachment(GetCapsuleComponent(), "");
	CameraSpringArm->bInheritPitch = false; CameraSpringArm->bInheritYaw = false; CameraSpringArm->bInheritRoll = false;

	// Add the InventoryComponent to the character
	InventoryComponent = CreateDefaultSubobject<USingleInputInventory>(TEXT("Inventory Component"));

	// Add the crafting component to the character
	CraftingComponent = CreateDefaultSubobject<USingleInputCraftingComponent>(TEXT("Crafting Component"));
	CraftingComponent->IC = InventoryComponent;

	// Find and store the test mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh>SMObject(TEXT("/Game/PolygonApocalypse/Meshes/Characters/SK_Chr_Biker_Male_01"));
	if (SMObject.Succeeded()) { GetMesh()->SetSkeletalMesh(SMObject.Object); }

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the default AI Class
	AIControllerClass = ASingleInputAIController::StaticClass();
}

// Called when the game starts or when spawned
void ASingleInputPerson::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemDisplay) {
		ItemDisplay = GetWorld()->SpawnActor<AItemDisplay>(AItemDisplay::StaticClass(), FVector(0.0f, 0.0f, 10000.0f), FRotator(), FActorSpawnParameters());
	}
}

// Called every frame
void ASingleInputPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASingleInputPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to swap between the two camera angles.  Call SetCameraAngle to directly set to a certain angle.
void ASingleInputPerson::SwapCameraAngle()
{
	// Store the Current Yaw
	float NewYaw = CameraSpringArm->GetRelativeRotation().Yaw;
	// If in overhead view, then swap to the standard angle
	if (bInOverheadView) {
		bInOverheadView = false;
		CameraSpringArm->SetRelativeRotation(FRotator(StandardCameraAngle, CurrentStep * RotationStep, 0));
	}
	// Else, swap vice versa
	else {
		bInOverheadView = true;
		CameraSpringArm->SetRelativeRotation(FRotator(OverheadCameraAngle, CurrentStep * RotationStep, 0));
	}
}

// Called to rotate the camera by CameraRotationStep in a direction.  True if rotation is clockwise.
void ASingleInputPerson::RotateCameraByStep(bool bRotateClockwise)
{
	// If the camera is to rotate counter clockwise, decrement the current step
	if (!bRotateClockwise) {
		CurrentStep--;
	}
	// Else, increment the step if the camera is to rotate clockwise
	else {
		CurrentStep++;
	}
	// Then set the rotation based on the current step * the rotation step
	CameraSpringArm->SetRelativeRotation(FRotator(CameraSpringArm->GetRelativeRotation().Pitch, CurrentStep * RotationStep, 0.0f));
}

// Called to move the character to a position in the world
void ASingleInputPerson::MoveToLocation(FVector NewLocation, FVector NewDirection)
{
	// Calculate where a trace hits and move the character to the hit location if valid 
	FHitResult TraceHit;
	bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, NewLocation, NewLocation + (NewDirection * 4000), ECC_WorldDynamic, FCollisionQueryParams(FName("DistTrace"), true));

	// Compare what the trace hit
	// If the trace hit a item, check that it doesn't have a owner already
	if (TraceHit.GetActor()->IsA(AParentItem::StaticClass())) {
		AParentItem* HitItem = Cast<AParentItem>(TraceHit.GetActor());
		if (HitItem->Owner == nullptr) {
			// Move to the item and pick it up
			AI->PickupItemState(HitItem);
		}
	}
	else {
		AI->MoveState(TraceHit.Location);
	}
}

