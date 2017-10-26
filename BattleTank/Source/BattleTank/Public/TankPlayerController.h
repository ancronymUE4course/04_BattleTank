// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // MUST BE THE LAST INCLUDE!!!

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override; // Oehh, saaks aru siis. Aga override checkib vist üles pärimusteed pidi.
	virtual void Tick(float DeltaTime) override;

private:
	void LogTankName();
	// Move the tank barrel, so that a shot would hit the crosshair intersect with world
	void AimTowardsCrosshair();
	
};
