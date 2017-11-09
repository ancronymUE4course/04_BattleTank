// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay(); // needed for BP beginplay to be called!

	Barrel = FindComponentByClass<UTankBarrel>();
	auto name = Barrel->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Barrel on tank named %s"), *name)
}

void ATank::AimAt(FVector HitLocation) {
	auto TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimForFire(HitLocation, LaunchSpeed);	
	
	return;
}

void ATank::Fire()
{
	// FPlatformTime is not really documented and even the tech does not know what it is, but it is good to use
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (!ensure(Barrel)) {	return;	}

		// spawn projectile at socket location
	if (isReloaded){
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barrel->GetSocketLocation(FName("Projectile")), 
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	return;
}
