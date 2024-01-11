// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SingleInputPerson.h"
#include "Core/SingleInputAIController.h"
#include "Core/SingleInputInventory.h"

// Sets default values
ASingleInputPerson::ASingleInputPerson()
{
	// Cameras
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Character Spring Arm"));
	CameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CameraSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 2000.0f;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetupAttachment(GetCapsuleComponent(), "");
	CameraSpringArm->bInheritPitch = false; CameraSpringArm->bInheritYaw = false; CameraSpringArm->bInheritRoll = false;

	// Inventory
	InventoryComponent = CreateDefaultSubobject<USingleInputInventory>(TEXT("Inventory Component"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the default AI Class
	AIControllerClass = ASingleInputAIController::StaticClass();
}

// Called when the game starts or when spawned
void ASingleInputPerson::BeginPlay()
{
	Super::BeginPlay();
	
	// Test - Add items to thhe inventory
	InventoryComponent->AddItemToArray(FItemData("SIP_TestWeapn", "Meme Item", EItemType::Weapon, 32, 20));
	InventoryComponent->AddItemToArray(FItemData("SIP_TestArmour", "YES Item", EItemType::Armour, 32, 20));
	InventoryComponent->AddItemToArray(FItemData("SIP_TestMaterial", "Dore Item", EItemType::Material, 32,200));
	InventoryComponent->SortInventory(EInventorySortType::Alphabetically);
	

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

void ASingleInputPerson::SwapCameraAngle()
{
	float NewYaw = CameraSpringArm->GetRelativeRotation().Yaw;
	if (bInOverheadView) {
		bInOverheadView = false;
		CameraSpringArm->SetRelativeRotation(FRotator(StandardCameraAngle, CurrentStep * RotationStep, 0));
	}
	else {
		bInOverheadView = true;
		CameraSpringArm->SetRelativeRotation(FRotator(OverheadCameraAngle, CurrentStep * RotationStep, 0));
	}
}

void ASingleInputPerson::RotateCameraByStep(bool bRotateClockwise)
{
	if (!bRotateClockwise) {
		CurrentStep--;
	}
	else {
		CurrentStep++;
	}
	CameraSpringArm->SetRelativeRotation(FRotator(CameraSpringArm->GetRelativeRotation().Pitch, CurrentStep * RotationStep, 0.0f));
}

void ASingleInputPerson::MoveToLocation(FVector NewLocation, FVector NewDirection)
{
	FHitResult TraceHit;
	bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, NewLocation, NewLocation + (NewDirection * 4000), ECC_WorldStatic, FCollisionQueryParams(FName("DistTrace"), true));
	AI->MoveToLocation(TraceHit.Location);
}

