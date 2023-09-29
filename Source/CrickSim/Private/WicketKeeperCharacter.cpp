// Fill out your copyright notice in the Description page of Project Settings.


#include "WicketKeeperCharacter.h"
#include "Ball/Public/CrickBall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Animation/AnimInstance.h"
#include "MotionWarpingComponent.h"


void AWicketKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	NativeSetWarpTargetF(IncomingBallFromBowler);

	if (NewBall && bLerpMustStart == true)
	{
		FVector StartLocation = NewBallSpawnTrans.GetLocation();
		FVector EndLocation = GetMesh()->GetSocketLocation(FName("BallSocket"));
		FVector InterpolatedLocation = FMath::Lerp(StartLocation, EndLocation, LerpVar);
		
		NewBall->SetActorRelativeLocation(InterpolatedLocation);
		if (LerpVar == 1.f) 
		{ 
			NewBall->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BallSocket"));
			GetWorld()->GetTimerManager().SetTimer(EndLevelTimerHandle, this, &AWicketKeeperCharacter::EndLevelTimerFunc, 5.f, false);

			return;
		}
		LerpVar += 0.1;
		
	}


}

void AWicketKeeperCharacter::Defend(FName TagName)
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DefendWicketMontage)
	{
		AnimInstance->Montage_Play(DefendWicketMontage);
		AnimInstance->Montage_JumpToSection(TagName);
	}
}

void AWicketKeeperCharacter::NativeSetBall(ACrickBall* Ball_In)
{



}

void AWicketKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();


}



void AWicketKeeperCharacter::NativeOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACrickBall* IncommingCricBall = Cast<ACrickBall>(OtherActor);

	if (IncommingCricBall && IncommingCricBall->ActorHasTag(FName("ThrowBall")))
	{
		UStaticMeshComponent* BallMeshTemp = Cast<UStaticMeshComponent>(IncommingCricBall->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (BallMeshTemp)
		{
			BallMeshTemp->SetSimulatePhysics(false);

			NewBallSpawnTrans = BallMeshTemp->GetComponentTransform();
		}

		IncommingCricBall->Destroy(); 

		TArray<AActor*> FoundActors; 
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrickBall::StaticClass(), FoundActors);

		for (AActor* FoundActor : FoundActors) 
		{

			if (FoundActor && FoundActor->ActorHasTag(FName("WKBall"))) 
			{
				NewBall = Cast<ACrickBall>(FoundActor); 
			}
		}

		if (NewBall)
		{
			BallMeshTemp = Cast<UStaticMeshComponent>(NewBall->GetComponentByClass(UStaticMeshComponent::StaticClass())); 
			if (BallMeshTemp)
			{
				BallMeshTemp->SetSimulatePhysics(false); 
				NewBall->SetActorTransform(NewBallSpawnTrans); 
			}

			UWidgetComponent* RedMarkerTemp = Cast<UWidgetComponent>(NewBall->GetComponentByClass(UWidgetComponent::StaticClass()));
			if (RedMarkerTemp)
			{
				RedMarkerTemp->SetHiddenInGame(false);

			}

			bLerpMustStart = true;

		}

	}

}

void AWicketKeeperCharacter::EndLevelTimerFunc()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));

}

void AWicketKeeperCharacter::NativeSetWarpTargetF(ACrickBall* Ball_In)
{
	if(IncomingBallFromBowler == nullptr){ IncomingBallFromBowler = Ball_In; }
	if (IsBallWithinRange(5000.f, IncomingBallFromBowler) == false) { return; }
	if (IsBallInFrontOfPlayer(IncomingBallFromBowler) == true)
	{
		MotionWarpingActorComponent->AddOrUpdateWarpTargetFromTransform(FName("BallTarget"), IncomingBallFromBowler->GetActorTransform());
	}

	



}

bool AWicketKeeperCharacter::IsBallWithinRange(int32 In_Range, ACrickBall* Ball_In)
{
	if (Ball_In == nullptr) { return false; }

	FVector BallLoc = Ball_In->GetActorLocation();
	FVector WKLoc = GetActorLocation();

	int32 Distance = FVector::Distance(BallLoc, WKLoc);

	if (Distance <= In_Range)
	{
		return true;
	}

	return false;
}

bool AWicketKeeperCharacter::IsBallInFrontOfPlayer(ACrickBall* Ball_In)
{
	if (Ball_In == nullptr) { return false ; }

	FVector BallLoc = Ball_In->GetActorLocation();
	FVector WKLoc = GetActorLocation();

	if (BallLoc.X >= WKLoc.X) { return true; }

	return false;
}
