// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Public/CrickBall.h"
#include "Kismet/GameplayStatics.h"
//#include "Components/ArrowComponent.h"

// Sets default values
ACrickBall::ACrickBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	//RootComponent = ArrowComponent; // Attach it to the RootComponent (change as needed)

	BallBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	BallBody->SetupAttachment(RootComponent);
	RootComponent = BallBody;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Megascans/3D_Assets/Cricket_Ball_udqlcjbva/S_Cricket_Ball_udqlcjbva_lod3_Var1.S_Cricket_Ball_udqlcjbva_lod3_Var1'"));
	if (MeshAsset.Succeeded())
	{
		BallBody->SetStaticMesh(MeshAsset.Object);
		//BallBody->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

}

// Called when the game starts or when spawned
void ACrickBall::BeginPlay()
{
	Super::BeginPlay();


	
	if (BallBody)
	{
		BallBody->OnComponentHit.AddDynamic(this, &ACrickBall::BallOnHit);

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		//FName SocketName = NAME_None;
		//BallBody->AttachToComponent(RootComponent, AttachmentRules);

	}

}

void ACrickBall::BallOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& FHitResult)
{
	

	//FVector SphereCenter = FVector(0.0f, 0.0f, 100.0f); // Center of the sphere
	//float SphereRadius = 50.0f; // Radius of the sphere
	//FColor SphereColor = FColor::Red; // Color of the sphere

	//// Draw the debug sphere
	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FHitResult.Location);

	//UE_LOG(LogTemp, Warning, TEXT("Your message goes here"));

	
}

// Called every frame
void ACrickBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACrickBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

