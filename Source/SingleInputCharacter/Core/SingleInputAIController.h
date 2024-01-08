// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SingleInputAIController.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEINPUTCHARACTER_API ASingleInputAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};