// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemManager.h"
#include "Character/InventoryComponent.h"

// Sets default values
AItemManager::AItemManager()
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

	// Get a reference to the item data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Items/DT_ItemConst"));
	if (DTObject.Succeeded()) { ItemDataTable = DTObject.Object; }

	// Get a reference to the crafting data table
	ConstructorHelpers::FObjectFinder<UDataTable>CDTObject(TEXT("/Game/Core/Items/DT_CraftingConst"));
	if (CDTObject.Succeeded()) { CraftingDataTable = CDTObject.Object; }


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemManager::SetNewMeshTarget(UStaticMesh* InStaticMesh, USkeletalMesh* InSkelMesh, float InSpringArmLength)
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

void AItemManager::ClearMeshTarget()
{
	// Set both of the mesh component's meshes to nullptr
	MeshDisplay_Skel->SetSkeletalMesh(nullptr);
	MeshDisplay_Static->SetStaticMesh(nullptr);
}

FItemConst AItemManager::GetItemData(FName InID)
{
	return GetItemDataFromID<FItemConst>(InID, EItemType::Item);
}

FCraftingConst AItemManager::GetRecipeDataFromID(FName InID)
{
	return *CraftingDataTable->FindRow<FCraftingConst>(InID, "", true);
}

TArray<FCraftingConst> AItemManager::GetRecipeData()
{
	TArray<FName> OutRows = CraftingDataTable->GetRowNames();
	FCraftingConst* CurrentRow;

	TArray<FCraftingConst> MatchingItems;

	// For each recipe in the data table, check if it has the matching station or "None" station
	for (FName i : OutRows) {
		CurrentRow = CraftingDataTable->FindRow<FCraftingConst>(i, "", true);
		MatchingItems.Add(*CurrentRow);
	}

	return MatchingItems;
}

TArray<FCraftingConst> AItemManager::GetRecipeDataOfStation(TEnumAsByte<EStationType> InStation)
{
	TArray<FName> OutRows = CraftingDataTable->GetRowNames();
	FCraftingConst* CurrentRow;

	TArray<FCraftingConst> MatchingItems;

	// For each recipe in the data table, check if it has the matching station or "None" station
	for (FName i : OutRows) {
		CurrentRow = CraftingDataTable->FindRow<FCraftingConst>(i, "", true);
		if (CurrentRow->Station == EStationType::None || CurrentRow->Station == InStation) {
			MatchingItems.Add(*CurrentRow);
		}
	}

	return MatchingItems;
}

TArray<FCraftingConst> AItemManager::GetRecipeDataOfStationAndType(TEnumAsByte<EItemType> InType, TEnumAsByte<EStationType> InStation)
{
	TArray<FName> OutRows = CraftingDataTable->GetRowNames();
	FCraftingConst* CurrentRow;

	TArray<FCraftingConst> MatchingItems;

	//UE_LOG(LogTemp, Warning, TEXT("InType = %s"), *UEnum::GetValueAsString(InType));

	// For each recipe in the data table, check if it has the matching station or "None" station
	for (FName i : OutRows) {
		CurrentRow = CraftingDataTable->FindRow<FCraftingConst>(i, "", true);
		if (CurrentRow->Station == EStationType::None || CurrentRow->Station == InStation) {
			// If it does, check if the output item matches the InType
			if (GetItemDataFromID<FItemConst>(CurrentRow->Output.ID, EItemType::Item).Type == InType) {
					MatchingItems.Add(*CurrentRow);
			}
		}
	}

	return MatchingItems;
}

void AItemManager::CraftItem(FName InID, UInventoryComponent* Inventory)
{
	UE_LOG(LogTemp, Warning, TEXT("In ItemManager"));
	FCraftingConst* Recipe = CraftingDataTable->FindRow<FCraftingConst>(InID, "", true);
	if (Recipe->ID != "") {
		for (FCraftingItemData i : Recipe->Inputs) {
			if (i.bConsumed) {
				Inventory->RemoveItemFromInventory(i.ID, i.Amount);
			}
		}
		Inventory->AddItemToInventory(Recipe->Output.ID, Recipe->Output.Amount);
	}
}