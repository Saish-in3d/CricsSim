// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceLocationMarker.h"

// Sets default values
ABounceLocationMarker::ABounceLocationMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABounceLocationMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABounceLocationMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 MarkerLocX = GetActorLocation().X;

	if (MarkerLocX >> ShortLengthValue)
	{
		ThrowType = FText::FromString("Dead Ball");
	}

	if (MarkerLocX <= ShortLengthValue)
	{
		ThrowType = FText::FromString("Short Length");
	}

	if (MarkerLocX <= ShortLengthValue)
	{
		ThrowType = FText::FromString("Good Length");
	}

	if (MarkerLocX <= ShortLengthValue)
	{
		ThrowType = FText::FromString("Full Length");
	}

	if (MarkerLocX <= 0.0f)
	{
		ThrowType = FText::FromString("SetType");
	}

}

FText ABounceLocationMarker::GetThrowType()
{
	return ThrowType;
}

