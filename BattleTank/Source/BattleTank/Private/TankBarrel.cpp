// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Elevate called"))
	auto Speed = FMath::Clamp(RelativeSpeed, -1.0f,1.0f);
	auto ElevationChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;	
	
	auto Elevation = FMath::Clamp(RawNewElevation, MinAngle, MaxAngle);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	return;
}