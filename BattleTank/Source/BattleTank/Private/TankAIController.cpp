// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
// Depends on the movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
	// if(ControlledTank){ UE_LOG(LogTemp, Warning, TEXT("Own Tank found.")); }
	
	// if (PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("Player found.")); }
}

void ATankAIController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(AimingComponent)){
		AimAtPlayer();
		if (AimingComponent->FiringStatus == EFiringStatus::Locked) {
			AimingComponent->Fire();
		}
		
	}

	MoveToActor(PlayerTank, AcceptanceRadius);
}

bool ATankAIController::AimAtPlayer() const
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerTank && AimingComponent)) { 
		FVector AimPoint = PlayerTank->GetTransform().GetTranslation();
		AimingComponent->AimForFire(AimPoint);
		return true;
	}
	/*
	Other way to do the same as previous
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	*/
	return false;
}