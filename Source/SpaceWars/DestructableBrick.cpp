// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructableBrick.h"
#include "DestructableBrickShape.h"

// Sets default values
ADestructableBrick::ADestructableBrick()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	BrickMesh->SetupAttachment(Root);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADestructableBrick::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADestructableBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableBrick::SetupBrick(ADestructableBrickShape* parentShape, UStaticMesh* meshToUse, FIntVector location)
{
	ParentShape = parentShape;
	BrickLocation = location;

	BrickMesh->SetStaticMesh(meshToUse);

	BrickMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ADestructableBrick::BrickHit()
{
	ParentShape->BrickHit(BrickLocation);
}

