// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Public/CrickBall.h"
#include "Kismet/GameplayStatics.h"
//#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
ACrickBall::ACrickBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	//RootComponent = ArrowComponent; // Attach it to the RootComponent (change as needed)

	BallBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	//BallBody->SetupAttachment(RootComponent);
	RootComponent = BallBody;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Megascans/3D_Assets/Cricket_Ball_udqlcjbva/S_Cricket_Ball_udqlcjbva_lod3_Var1.S_Cricket_Ball_udqlcjbva_lod3_Var1'"));
	if (MeshAsset.Succeeded())
	{
		BallBody->SetStaticMesh(MeshAsset.Object);
		//BallBody->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	MarkerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MarkerWidgetComponent"));
	MarkerWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrickBall::BeginPlay()
{
	Super::BeginPlay();


	
	if (BallBody)
	{
		BallBody->OnComponentHit.AddDynamic(this, &ACrickBall::BallOnHit);
		EnablePhysics(false);

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

void ACrickBall::ShowMarker(bool In_bool)
{
	if (MarkerWidgetComponent && In_bool == true)
	{
		MarkerWidgetComponent->bHiddenInGame = false;
		return;
	}
	else if (MarkerWidgetComponent && In_bool == false)
	{
		MarkerWidgetComponent->bHiddenInGame = true;
		return;
	}
}

void ACrickBall::EnablePhysics(bool In_bool)
{
	if (BallBody )
	{
		BallBody->SetSimulatePhysics(In_bool); 
		
	}
	
}

void ACrickBall::AddImpusleVector(FVector In_Vec)
{
	if (BallBody)
	{
		BallBody->AddImpulse( In_Vec); 

	}

}

