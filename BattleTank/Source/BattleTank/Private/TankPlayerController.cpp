// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay check."));
	LogTankName();
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


