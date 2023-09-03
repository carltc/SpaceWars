// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template <class ObjectType>
class SPACEWARS_API Grid3D
{

public:

	// A pointer to a Map of 3D grid locations with the pointer to an Object at that location
	TMap<FIntVector, ObjectType*> Objects;

private:

	int32 SizeX;
	int32 SizeY;
	int32 SizeZ;

	void InitialiseGrid(int32 sizeX, int32 sizeY, int32 sizeZ)
	{
		SizeX = sizeX;
		SizeY = sizeY;
		SizeZ = sizeZ;

		for (int32 i = 0; i < SizeX; i++)
		{
			for (int32 j = 0; j < SizeY; j++)
			{
				for (int32 k = 0; k < SizeZ; k++)
				{
					ObjectType newObject = ObjectType();
					FIntVector newLocation = FIntVector(i, j, k);
					Objects.Add(newLocation, &newObject);
				}
			}
		}
	}

public:
	Grid3D<ObjectType>() {
		
	}
	Grid3D<ObjectType>(int32 sizeX, int32 sizeY, int32 sizeZ) {
		InitialiseGrid(sizeX, sizeY, sizeZ);
	}
	~Grid3D<ObjectType>() {

	}

	ObjectType* operator[] (FIntVector key) { return Objects[key]; }

	bool IsEdgeObject(FIntVector *location) {
		
		if (location->X == 0 || location->X == SizeX - 1)
		{
			return true;
		}

		if (location->Y == 0 || location->Y == SizeY - 1)
		{
			return true;
		}

		if (location->Z == 0 || location->Z == SizeZ - 1)
		{
			return true;
		}

		return false;

	}

	TArray<ObjectType*> GetNeighbours(FIntVector *location)
	{
		TArray<ObjectType*> neighbours = TArray<ObjectType>();

		// Check X neighbours
		if (location->X > 0)
		{
			neighbours.Add(*(Objects)[FIntVector(location->X - 1, location->Y, location->Z)]);
		}
		if (location->X < SizeX - 1)
		{
			neighbours.Add(*(Objects)[FIntVector(location->X + 1, location->Y, location->Z)]);
		}
		
		// Check Y neighbours
		if (location->Y > 0)
		{
			neighbours.Add(*(Objects)[FIntVector(location->X, location->Y - 1, location->Z)]);
		}
		if (location->Y < SizeY - 1)
		{
			neighbours.Add(*(Objects)[FIntVector(location->X, location->Y + 1, location->Z)]);
		}
		
		// Check Z neighbours
		if (location->Z > 0)
		{
			neighbours.Add(*(Objects)[FIntVector(location->X, location->Y, location->Z - 1)]);
		}
		if (location->Z < SizeZ - 1)
		{
			neighbours.Add(*(Objects)[FIntVector(location->Z, location->Y, location->Z + 1)]);
		}
		
		return neighbours;
	}
};
