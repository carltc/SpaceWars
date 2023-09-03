// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructableBrick.generated.h"

class ADestructableBrickShape;

UCLASS()
class SPACEWARS_API ADestructableBrick : public AActor
{
	GENERATED_BODY()

private:

	ADestructableBrickShape* ParentShape;

	FIntVector BrickLocation;

	USceneComponent* Root;

	UStaticMeshComponent* BrickMesh;

public:	
	// Sets default values for this actor's properties
	ADestructableBrick();

	void SetupBrick(ADestructableBrickShape* parentShape, UStaticMesh* meshToUse, FIntVector location);

	UFUNCTION(BlueprintCallable)
		void BrickHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
