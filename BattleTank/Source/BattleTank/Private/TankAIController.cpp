// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
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
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank && ControlledTank)){
	AimAtPlayer();	
	ControlledTank->Fire();
	}

	MoveToActor(PlayerTank, AcceptanceRadius);
}

bool ATankAIController::AimAtPlayer() const
{
	if (ensure(PlayerTank && ControlledTank)) { 
		FVector AimPoint = PlayerTank->GetTransform().GetTranslation();
		ControlledTank->AimAt(AimPoint);
		return true;
	}
	/*
	Other way to do the same as previous
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	*/
	return false;
}