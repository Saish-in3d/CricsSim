// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlerCharacter.h"
#include "Ball/Public/CrickBall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "BounceLocationMarker.h"

void ABowlerCharacter::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime);

}

void ABowlerCharacter::SetBallSpeed(int32 In_BallSpeed)
{

	BallSpeed = In_BallSpeed; 
	 
}

void ABowlerCharacter::SetStartBowling(bool In_bool)
{
	bAllowBowling = In_bool; 
}

void ABowlerCharacter::ThrowBall()
{
	if (BowlerInHandBall == nullptr) { return; }

	BallSpawnTransform = BowlerInHandBall->GetActorTransform();

	BowlerInHandBall->Destroy();

	if (BowlerToThrowBall == nullptr) { return; }

	BowlerToThrowBall->SetActorTransform(BallSpawnTransform);

	BowlerToThrowBall->ShowMarker(true);

	BowlerToThrowBall->EnablePhysics(true);

	BowlerToThrowBall->AddImpusleVector(CalculateImpulseVector());


}

void ABowlerCharacter::StartBowling()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && BowlingMontage)
	{
		AnimInstance->Montage_Play(BowlingMontage);
	}

}

void ABowlerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrickBall::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors)
	{

		if (FoundActor && FoundActor->ActorHasTag(FName("Ball")))
		{
			BowlerInHandBall = Cast<ACrickBall>(FoundActor);
		}
	}

	if (BowlerInHandBall)
	{
		BowlerInHandBall->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BallSocket"));

		UWidgetComponent* RedMarkerTemp = Cast<UWidgetComponent>(BowlerInHandBall->GetComponentByClass(UWidgetComponent::StaticClass()));
		if (RedMarkerTemp)
		{
			RedMarkerTemp->SetHiddenInGame(false);

		}

	}

	if (BowlerInHandBall)
	{
		UStaticMeshComponent* BallMeshTemp = Cast<UStaticMeshComponent>(BowlerInHandBall->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (BallMeshTemp)
		{
			BallMeshTemp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	SetStartBowling(false);

	TArray<AActor*> FoundMarkerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrickBall::StaticClass(), FoundMarkerActors);

	for (AActor* FoundMarkerActor : FoundMarkerActors)
	{
		 
		if (FoundMarkerActor && FoundMarkerActor->ActorHasTag(FName("BM")))
		{
			BounceLocationMarker = Cast<ABounceLocationMarker>(FoundMarkerActor); 
		}
	}

	TArray<AActor*> FoundThrowActors; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrickBall::StaticClass(), FoundThrowActors);

	for (AActor* FoundThrowActor : FoundThrowActors)
	{

		if (FoundThrowActor && FoundThrowActor->ActorHasTag(FName("ThrowBall")))
		{
			BowlerToThrowBall = Cast<ACrickBall>(FoundThrowActor);
		}
	}


}

FVector ABowlerCharacter::CalculateImpulseVector()
{
	if (BounceLocationMarker && BowlerToThrowBall)
	{
		FVector A = (BounceLocationMarker->GetActorLocation() - BowlerToThrowBall->GetActorLocation());
		A.Normalize()* BallSpeed;
		return A;
	}

	return FVector();
}
