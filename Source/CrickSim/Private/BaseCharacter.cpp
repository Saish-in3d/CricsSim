// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "MotionWarpingComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NativeBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("NativeBoxComponent"));
	NativeBoxComponent->SetupAttachment(RootComponent);

	MotionWarpingActorComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("NativeMotionWarpingActorComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(NativeBoxComponent)
	{
		NativeBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::NativeOnBeginOverlap);
	}


}


void ABaseCharacter::NativeOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

