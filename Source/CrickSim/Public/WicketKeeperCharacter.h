// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "WicketKeeperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRICKSIM_API AWicketKeeperCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	




private:

	class ACrickBall* Ball;

	class ACrickBall* BallTemp;

	class ACrickBall* NewBall;

	FTransform NewBallSpawnTrans;

	float LerpVar;
};
