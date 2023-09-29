// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BowlerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRICKSIM_API ABowlerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void SetBallSpeed(int32 In_BallSpeed);

	void SetStartBowling(bool In_bool);

	void ThrowBall();

	void StartBowling();

protected:

	virtual void BeginPlay() override;


private:
	
	class ACrickBall* BowlerInHandBall;

	class ACrickBall* BowlerToThrowBall;

	class ABounceLocationMarker* BounceLocationMarker;

	FTransform BallSpawnTransform;

	int32 BallSpeed;

	bool bAllowBowling = false;

	FVector CalculateImpulseVector();

	UPROPERTY(EditAnywhere)
	UAnimMontage* BowlingMontage;

	

};
