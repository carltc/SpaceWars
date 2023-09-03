// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableBrickUniverse.h"
#include "DestructableBrick.h"

// Sets default values
ADestructableBrickUniverse::ADestructableBrickUniverse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADestructableBrickUniverse::InitialiseBrickLocations()
{
	ClearAllBrickLocations();

	// Create new set of bricklocations
	for (int32 i = -(Size.X / 2); i < Size.X / 2; i++)
	{
		for (int32 j = -(Size.Y / 2); j < Size.Y / 2; j++)
		{
			for (int32 k = -(Size.Z / 2); k < Size.Z / 2; k++)
			{
				// Check if this location is within the distance to the centre
				if (FVector::Dist(FVector(i, j, k), FVector(0, 0, 0)) < Size.X / 2)
				{
					KnownLocations.Emplace(FIntVector(i, j, k));
				}
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
		else
		{
			int p = 0;
		}
	}
}

