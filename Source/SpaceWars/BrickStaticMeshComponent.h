// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BrickStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWARS_API UBrickStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
		FIntVector Location;

};
