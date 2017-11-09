// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay check."));
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)){ FoundAimingComponent(AimingComponent); }
	else {UE_LOG(LogTemp, Warning, TEXT("PC cant find AC at BeginPlay")) }
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

void ATankPlayerController::AimTowardsCrosshair() {
	if(!ensure(GetControlledTank())) { return; }
	FVector OutHitLocation;

	// get world location through crosshair with linetrace
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
		auto OutHit = OutHitLocation.ToString();
		// UE_LOG(LogTemp, Warning, TEXT(" From TPC to Tank %s."), *OutHit)
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


