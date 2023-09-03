// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructableBrickShape.h"
#include "DestructableBrick.h"

// Sets default values
ADestructableBrickShape::ADestructableBrickShape()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> DefaultBrick;
		FConstructorStatics()
			: DefaultBrick(TEXT("/Game/Models/Cube.Cube"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	BrickToUse = ConstructorStatics.DefaultBrick.Get();
	Size = FIntVector(5, 5, 5);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Bricks = CreateDefaultSubobject<USceneComponent>(TEXT("Bricks"));
	Bricks->SetupAttachment(Root);

	// Get size of the brick to use
	BrickSize = BrickToUse->GetBounds().BoxExtent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADestructableBrickShape::BeginPlay()
{
	Super::BeginPlay();

	InitialiseBrickLocations();

}

// Called every frame
void ADestructableBrickShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ADestructableBrickShape::PostEditChangeProperty(struct FPropertyChangedEvent& e)
//{
//	Super::PostEditChangeProperty(e);
//
//	//FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
//	//if (PropertyName == GET_MEMBER_NAME_CHECKED(ADestructableBrickShape, BrickToUse))
//	//{
//	//	// Brick Mesh updated. Re-initialise the entire shape
//	//	InitialiseBrickLocations();
//	//}
//	//else if (PropertyName == GET_MEMBER_NAME_CHECKED(ADestructableBrickShape, Size))
//	//{
//	//	// Shape Size updated. Re-initialise the entire shape
//	//	InitialiseBrickLocations();
//	//}
//}


void ADestructableBrickShape::InitialiseBrickLocations()
{
	ClearAllBrickLocations();

	// Create new set of bricklocations
	for (int32 i = 0; i < Size.X; i++)
	{
		for (int32 j = 0; j < Size.Y; j++)
		{
			for (int32 k = 0; k < Size.Z; k++)
			{
				FIntVector newLocation = FIntVector(i, j, k);
				KnownLocations.Emplace(newLocation);
			}
		}
	}

	// Spawn bricks on the edge
	for (FIntVector location : KnownLocations)
	{
		if (IsEdgeBrick(location))
		{
			AddDestructableBrick(location);
		}
	}
}

void ADestructableBrickShape::ClearAllBrickLocations()
{
	// Destroy all existing brick actors
	for (FIntVector location : KnownLocations)
	{
		RemoveDestructableBrick(location);
	}

	KnownLocations.Empty();
}

void ADestructableBrickShape::AddDestructableBrick(FIntVector location)
{
	if (!DestructableBricks.Contains(location))
	{
		// If so then create actor and add it to arrays
		FString brickName = FString::Printf(TEXT("Brick %d-%d-%d"), location.X, location.Y, location.Z);
		UBrickStaticMeshComponent* Brick = NewObject<UBrickStaticMeshComponent>(this, UBrickStaticMeshComponent::StaticClass(), FName(brickName));
		Brick->RegisterComponent();
		Brick->AttachToComponent(Bricks, FAttachmentTransformRules::KeepRelativeTransform);
		Brick->SetStaticMesh(BrickToUse);
		Brick->CreationMethod = EComponentCreationMethod::Instance;
		Brick->Location = location;
		Brick->SetWorldLocation(LocationToWorldLocation(location));
		Brick->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		Brick->SetGenerateOverlapEvents(true);
		Brick->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Brick->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
		Brick->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
		DestructableBricks.Add(location, Brick);

		//ADestructableBrick* brick = GetWorld()->SpawnActor<ADestructableBrick>(ADestructableBrick::StaticClass(), LocationToWorldLocation(location) + this->GetActorLocation(), FRotator(1, 1, 1), FActorSpawnParameters());
		//DestructableBricks.Add(location, brick);
		//brick->SetupBrick(this, BrickToUse, location);yout
	}
}

void ADestructableBrickShape::RemoveDestructableBrick(FIntVector location)
{
	// Check if a brick exists at this location
	if (DestructableBricks.Contains(location))
	{
		UBrickStaticMeshComponent* brick = DestructableBricks[location];
		brick->DestroyComponent();

		// If so then destroy actor and remove it from arrays
		//ADestructableBrick* brick = DestructableBricks[location];
		//brick->Destroy();

		DestructableBricks.Remove(location);
	}
}

bool ADestructableBrickShape::IsEdgeBrick(FIntVector location)
{
	return GetKnownNeighbourLocations(location).Num() != 6;
}

FVector ADestructableBrickShape::LocationToWorldLocation(FIntVector location)
{
	return FVector(
		location.X * (BrickSize.X * 2),
		location.Y * (BrickSize.Y * 2),
		location.Z* (BrickSize.Z * 2)
	);
}

TArray<FIntVector> ADestructableBrickShape::GetKnownNeighbourLocations(FIntVector location)
{
	TArray<FIntVector> neighbours;

	for (int32 i = 0; i < 6; i++)
	{
		FIntVector neighbourLocation = location + NeighbourCoords[i];
		if (KnownLocations.Contains(neighbourLocation))
		{
			neighbours.Add(neighbourLocation);
		}
	}

	return neighbours;
}

void ADestructableBrickShape::BrickHit(FIntVector location)
{
	RemoveDestructableBrick(location);

	// Add bricks at all neighbour locations
	for (int32 i = 0; i < 6; i++)
	{
		FIntVector neighourLocation = location + NeighbourCoords[i];
		// If this is already a location then don't add a brick here
		if (!KnownLocations.Contains(neighourLocation))
		{
			KnownLocations.Emplace(neighourLocation);
			AddDestructableBrick(neighourLocation);
		}
	}
}


