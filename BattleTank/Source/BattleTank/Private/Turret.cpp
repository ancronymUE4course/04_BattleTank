// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTurret::Rotate(float RelativeSpeed){
	// UE_LOG(LogTemp, Warning, TEXT("Rotate called"))
	auto Speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto DirectionChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewYaw = RelativeRotation.Yaw + DirectionChange;

	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
	return;

}


