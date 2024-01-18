// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemDisplay.h"

// Sets default values
AItemDisplay::AItemDisplay()
{
	// Setup Components
	MeshDisplay_Static = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Display Static"));
	MeshDisplay_Static->bVisibleInSceneCaptureOnly = true;
	MeshDisplay_Skel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Display Skel"));
	MeshDisplay_Skel->bVisibleInSceneCaptureOnly = true;
	MeshDisplay_Skel->SetupAttachment(MeshDisplay_Static, "");
	
	DisplaySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Display Spring Arm"));
	DisplaySpringArm->SetupAttachment(MeshDisplay_Static, "");

	DisplayCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("DisplayCapture"));
	DisplayCapture->SetupAttachment(DisplaySpringArm, "");
	DisplayCapture->ShowOnlyComponent(MeshDisplay_Static);
	DisplayCapture->ShowOnlyComponent(MeshDisplay_Skel);

	// Find the Render Texture
	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>RTObject(TEXT("/Game/Items/CRT_ItemDisplay"));
	if (RTObject.Succeeded()) { DisplayCapture->TextureTarget = RTObject.Object; }


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to set a new mesh as the Display's target
void AItemDisplay::SetNewMeshTarget(UStaticMesh* InStaticMesh, USkeletalMesh* InSkelMesh, float InSpringArmLength)
{
	// Set the spring arm length
	DisplaySpringArm->TargetArmLength = InSpringArmLength;

	// If a StaticMesh is inputted, then setup the static mesh
	if (InStaticMesh) {
		MeshDisplay_Skel->SetSkeletalMesh(nullptr);
		MeshDisplay_Static->SetStaticMesh(InStaticMesh);
	}
	// Else, if a SkeletalMesh is inputted, then setup the skel mesh
	else if (InSkelMesh) {
		MeshDisplay_Skel->SetSkeletalMesh(InSkelMesh);
		MeshDisplay_Static->SetStaticMesh(nullptr);
	}
}

// Called to clear both mesh components
void AItemDisplay::ClearMeshTarget()
{
	// Set both of the mesh component's meshes to nullptr
	MeshDisplay_Skel->SetSkeletalMesh(nullptr);
	MeshDisplay_Static->SetStaticMesh(nullptr);
}

