// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	// if(ControlledTank){ UE_LOG(LogTemp, Warning, TEXT("Own Tank found.")); }
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// if (PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("Player found.")); }
}

void ATankAIController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	
	if (PlayerTank && ControlledTank){
	AimAtPlayer();	
	ControlledTank->Fire();
	}
}

bool ATankAIController::AimAtPlayer() const
{
	if (PlayerTank && ControlledTank) { 
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