// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SingleInputPerson.h"
#include "Core/SingleInputAIController.h"

// Sets default values
ASingleInputPerson::ASingleInputPerson()
{
	// Cameras
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Character Spring Arm"));
	CameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	CameraSpringArm->TargetArmLength = 2000.0f;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->SetupAttachment(GetCapsuleComponent(), "");

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the default AI Class
	AIControllerClass = ASingleInputAIController::StaticClass();

	SwapCameraAngle();
}

// Called when the game starts or when spawned
void ASingleInputPerson::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (bInOverheadView) {
		bInOverheadView = false;
		CameraSpringArm->SetRelativeRotation(FRotator(StandardCameraAngle, CameraSpringArm->GetRelativeRotation().Yaw, 0));
	}
	else {
		bInOverheadView = true;
		CameraSpringArm->SetRelativeRotation(FRotator(OverheadCameraAngle, CameraSpringArm->GetRelativeRotation().Yaw, 0));
	}
}

void ASingleInputPerson::RotateCameraByStep(bool bRotateClockwise)
{
	UE_LOG(LogTemp, Warning, TEXT("Rotate Camera"));
	int NewStep = RotationStep;
	if (!bRotateClockwise) {
		NewStep = NewStep * -1;
	}

	CameraSpringArm->AddRelativeRotation(FRotator(0.0f, NewStep, 0.0f));
}

void ASingleInputPerson::MoveToLocation(FVector NewLocation, FVector NewDirection)
{
	FHitResult TraceHit;
	bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, NewLocation, NewLocation + (NewDirection * 2000), ECC_WorldStatic, FCollisionQueryParams(FName("DistTrace"), true));
	AI->MoveToLocation(TraceHit.Location);
}

