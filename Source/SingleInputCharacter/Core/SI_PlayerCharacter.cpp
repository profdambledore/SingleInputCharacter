// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SI_PlayerCharacter.h"

#include "Character/InventoryComponent.h"
#include "Character/CraftingComponent.h"
#include "Item/WeaponItem.h"

// Sets default values
ASI_PlayerCharacter::ASI_PlayerCharacter()
{
	// Setup Mesh 
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Setup the spring arm for the SingleInputPlayer to attach to
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Character Spring Arm"));
	CameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	CameraSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 2000.0f;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetupAttachment(GetCapsuleComponent(), "");
	CameraSpringArm->bInheritPitch = false; CameraSpringArm->bInheritYaw = false; CameraSpringArm->bInheritRoll = false;

	// Add the InventoryComponent to the character
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryComponent->InventoryOwner = this;

	// Add the crafting component to the character
	CraftingComponent = CreateDefaultSubobject<UCraftingComponent>(TEXT("Crafting Component"));
	CraftingComponent->InventoryComponent = InventoryComponent;

	// Find and store the test mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh>SMObject(TEXT("/Game/PolygonApocalypse/Meshes/Characters/SK_Chr_Biker_Male_01"));
	if (SMObject.Succeeded()) { GetMesh()->SetSkeletalMesh(SMObject.Object); }

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASI_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASI_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/// -- Camera --
// Called to swap between the two camera angles.  Call SetCameraAngle to directly set to a certain angle.
void ASI_PlayerCharacter::SwapCameraAngle()
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
void ASI_PlayerCharacter::RotateCameraByStep(bool bRotateClockwise)
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

void ASI_PlayerCharacter::EquipWeapon(FItemData WeaponData)
{
	// Check if a weapon object has been created.  If not, create one now
	if (!EquippedWeapon) {
		FActorSpawnParameters SpawnParams;
		EquippedWeapon = GetWorld()->SpawnActor<AWeaponItem>(AWeaponItem::StaticClass(), FVector(), FRotator(), SpawnParams);
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "");
	}

	// Setup the weapon with the new data
	EquippedWeapon->SetupItem(WeaponData);
}
