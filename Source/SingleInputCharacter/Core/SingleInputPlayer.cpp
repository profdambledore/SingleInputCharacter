// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SingleInputPlayer.h"

// Sets default values
ASingleInputPlayer::ASingleInputPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the Player's Cameras
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
}

// Called when the game starts or when spawned
void ASingleInputPlayer::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ASingleInputPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASingleInputPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


