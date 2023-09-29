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
	
public:
	virtual void Tick(float DeltaTime) override;

	//Plays Defend Anim montage based on the location of BP_BallHitBox
	void Defend(FName TagName);

	// Ball incoming after hit from BP_BallHitBox for setting MotionWarping target
	void NativeSetBall(class ACrickBall* Ball_In);

protected:

	virtual void BeginPlay() override;

	
	void NativeOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	// Ball incoming after hit from BP_BallHitBox
	class ACrickBall* IncomingBallFromBowler;

	class ACrickBall* BallTemp;

	class ACrickBall* NewBall;

	FTransform NewBallSpawnTrans;

	float LerpVar = 0.f;

	bool bLerpMustStart = false;

	bool bHasLerpEnded = false;

	FTimerHandle EndLevelTimerHandle;


	void EndLevelTimerFunc();

	UPROPERTY(EditAnywhere)
	UAnimMontage* DefendWicketMontage;

	void NativeSetWarpTargetF( ACrickBall* Ball_In);

	bool IsBallWithinRange(int32 In_Range, ACrickBall* Ball_In);

	bool IsBallInFrontOfPlayer(ACrickBall* Ball_In);
};
