// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // MUST BE THE LAST INCLUDE!!!

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override; // Oehh, saaks aru siis. Aga override checkib vist üles pärimusteed pidi.
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	UPROPERTY(EditAnywhere)
	float CrossHairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairLocationY = 0.3333333f;

	void LogTankName();

	// Move the tank barrel, so that a shot would hit the crosshair intersect with world
	void AimTowardsCrosshair();

	// Aiming methods
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;	
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
};
