// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SI_PlayerClass.h"

// Sets default values
ASI_PlayerClass::ASI_PlayerClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup the Player's Cameras
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
}

// Called when the game starts or when spawned
void ASI_PlayerClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_PlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASI_PlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

