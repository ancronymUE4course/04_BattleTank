// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay check."));
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)){ FoundAimingComponent(AimingComponent); }
	else {UE_LOG(LogTemp, Warning, TEXT("PC cant find AC at BeginPlay")) }
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe to the tanks death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerDeath);
	}
}

// Tick
void ATankPlayerController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// You do need a one line method, because of delegate. It would not work without it.
void ATankPlayerController::OnPlayerDeath()
{	
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent)) { return; }
	FVector OutHitLocation;

	// get world location through crosshair with linetrace
	if (GetSightRayHitLocation(OutHitLocation))
	{		
		AimingComponent->AimForFire(OutHitLocation);
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	};
		
	// linetrace along that look direction and see what we hit
	return false;
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
		ECollisionChannel::ECC_Camera
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


