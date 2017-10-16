// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("AI Controller BeginPlay check."));
	// LogTankName();
	LogPlayerTankName();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);

}

void ATankAIController::LogTankName() const
{
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank name: %s"), *(ControlledTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Tank found."));
	}
	return;
}

void ATankAIController::LogPlayerTankName() const
{
	ATank* PlayerTank = GetPlayerTank();
	ATank* ControlledTank = GetControlledTank();
	if(PlayerTank && ControlledTank){
		UE_LOG(LogTemp, Warning, TEXT("AI %s reporting and found player tank named: %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI error."));
	}
	
}
