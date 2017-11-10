// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override; // Oehh, saaks aru siis. Aga override checkib vist üles pärimusteed pidi.
	virtual void Tick(float DeltaTime) override;

private:
	bool AimAtPlayer() const;

	APawn* ControlledTank = nullptr;
	APawn* PlayerTank = nullptr;

	float AcceptanceRadius = 2000.f; // How close does AI move to player
};
