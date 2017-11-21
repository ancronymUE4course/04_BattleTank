// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

// I ROCK FOR WRITING THIS!!!
void UTurret::Rotate(float RelativeSpeed){
	auto Speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	// UE_LOG(LogTemp, Warning, TEXT("Rotate called: %f"), RelativeSpeed)

	/* 
	This is my fix for the situation, another way would be to use FMath::Abs in the aiming component before passing
	in the RelativeSpeed value
	*/

	if (RelativeSpeed <= 180.f && RelativeSpeed >= -180.f) { 
		auto DirectionChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
		auto RawNewYaw = RelativeRotation.Yaw + DirectionChange;
		
		
		SetRelativeRotation(FRotator(0, RawNewYaw, 0)); 	
	}
	else if (RelativeSpeed > 180.f || RelativeSpeed < -180.f){ 
		auto DirectionChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
		auto RawNewYaw = RelativeRotation.Yaw - DirectionChange;
		
		SetRelativeRotation(FRotator(0, RawNewYaw, 0)); 
	}
	return;

}


