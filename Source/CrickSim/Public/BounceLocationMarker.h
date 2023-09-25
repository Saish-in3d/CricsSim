// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BounceLocationMarker.generated.h"

UCLASS()
class CRICKSIM_API ABounceLocationMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABounceLocationMarker();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FText GetThrowType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int32  ShortLengthValue = 12711.239224f;

	int32 GoodLengthValue = 12400.116171f;

	int32 FullLengthValue = 12073.217824f;

	FText ThrowType = FText::FromString("SetType");



};
