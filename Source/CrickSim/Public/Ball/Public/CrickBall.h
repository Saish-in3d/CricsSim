// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CrickBall.generated.h"

UCLASS()
class CRICKSIM_API ACrickBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACrickBall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//GetballMesh

	//GetMarker

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallBody;

private:	

	UFUNCTION()
	void BallOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent;
};
