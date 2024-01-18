// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/CraftingData.h"
#include "Core/ParentItem.h"

/// -- Crafting Item Data --
FCraftingItemData::FCraftingItemData()
{
}

FCraftingItemData::~FCraftingItemData()
{
}


FCraftingData::FCraftingData()
{
}

FCraftingData::FCraftingData(FCraftingData InData, bool bInActive)
{
	ID = InData.ID;
	Inputs = InData.Inputs;
	Output = InData.Output;
	Station = InData.Station;
	bRecipeActive = bInActive;
}

FCraftingData::~FCraftingData()
{
}

