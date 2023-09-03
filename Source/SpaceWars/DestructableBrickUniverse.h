// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructableBrickShape.h"
#include "DestructableBrickUniverse.generated.h"

UCLASS()
class SPACEWARS_API ADestructableBrickUniverse : public ADestructableBrickShape
{
	GENERATED_BODY()

private:

	virtual void InitialiseBrickLocations() override;

public:	
	// Sets default values for this actor's properties
	ADestructableBrickUniverse();

};
