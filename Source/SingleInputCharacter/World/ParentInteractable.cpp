// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ParentInteractable.h"



// Sets default values
AParentInteractable::AParentInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AParentInteractable::UseInteractable(class AController* User)
{

}

// Called when the game starts or when spawned
void AParentInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

