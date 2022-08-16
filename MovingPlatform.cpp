// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();


	//* converst fString to string
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"),* Name);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime) // Tells us how long each frame took to execute(frame rate independent)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
	
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Reverse direction if gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal(); // Get normal direction
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// Move platform forwards
		// Get current location
		FVector CurrentLocation = GetActorLocation();
		// Add vector to that location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		// set the location
		SetActorLocation(CurrentLocation);
	}

}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("This method will move the platform"));
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	// Send player backwards if too far . :: is a scope resolution operator specific to C++
	// Returns a positive number
	return FVector::Dist(StartLocation, GetActorLocation());
}
