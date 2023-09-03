// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickStaticMeshComponent.h"
#include "DestructableBrickShape.generated.h"

class ADestructableBrick;

UCLASS()
class SPACEWARS_API ADestructableBrickShape : public AActor
{
	GENERATED_BODY()

private:

	const FIntVector NeighbourCoords[6] = {
		FIntVector(-1, 0, 0),
		FIntVector(1, 0, 0),
		FIntVector(0, -1, 0),
		FIntVector(0, 1, 0),
		FIntVector(0, 0, -1),
		FIntVector(0, 0, 1)
	};

	FVector BrickSize;

public:	
	// Sets default values for this actor's properties
	ADestructableBrickShape();

protected:

	USceneComponent* Root;
	
	USceneComponent* Bricks;

	//TMap<FIntVector, ADestructableBrick*> DestructableBricks;
	TMap<FIntVector, UBrickStaticMeshComponent*> DestructableBricks;

	TSet<FIntVector> KnownLocations;

	virtual void InitialiseBrickLocations();

	void ClearAllBrickLocations();

	void AddDestructableBrick(FIntVector location);

	void RemoveDestructableBrick(FIntVector location);

	bool IsEdgeBrick(FIntVector location);

	FVector LocationToWorldLocation(FIntVector location);

	TArray<FIntVector> GetKnownNeighbourLocations(FIntVector location);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Event triggered when a property has been changed in the Unreal editor.
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:	

	UPROPERTY(EditAnywhere, Category = "Inputs")
		UStaticMesh* BrickToUse;

	UPROPERTY(EditAnywhere, Category = "Inputs")
		FIntVector Size;

	UFUNCTION(BlueprintCallable)
		void BrickHit(FIntVector location);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
