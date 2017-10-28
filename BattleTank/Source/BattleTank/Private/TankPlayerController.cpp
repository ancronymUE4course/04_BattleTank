// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay check."));
	LogTankName();
}

// Tick
void ATankPlayerController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::LogTankName()
{
	ATank* PlayerTank=GetControlledTank();
	FString TankName = PlayerTank->GetName();
	if (PlayerTank) {
		UE_LOG(LogTemp,Warning,TEXT("Player Tank name: %s"), *TankName);
	}
	else {
		UE_LOG(LogTemp,Warning,TEXT("No Tank found."));
	}
	return;
}

void ATankPlayerController::AimTowardsCrosshair() {
	if(!GetControlledTank()) { return; }
	FVector OutHitLocation;

	// get world location through crosshair with linetrace
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
	// if hits landscape
		// tell controlled tank to aim at this point
	
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX,ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairLocationX,ViewPortSizeY*CrossHairLocationY);
	
	// deproject crosshair position to a world direction
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString())
	};
		
	// linetrace along that look direction and see what we hit
	return GetLookVectorHitLocation(LookDirection, OutHitLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	auto ViewLocation = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = ViewLocation + LookDirection * LineTraceRange;
	FHitResult OutHit;

	// Here we left out the two last parameters asked for by LineTraceSingleByChannel(), but why?
	if (GetWorld()->LineTraceSingleByChannel(	
		OutHit,
		ViewLocation,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility
	)){
		OutHitLocation = OutHit.Location;
		return true;
	};
	OutHitLocation = FVector(0.f);
	return false;	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector WorldLocation; // will be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection
	);
}


