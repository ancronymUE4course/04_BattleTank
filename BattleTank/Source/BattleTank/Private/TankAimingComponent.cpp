// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void UTankAimingComponent::InitialiseAiming(UTankBarrel* BarrelToSet, UTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	UE_LOG(LogTemp, Warning, TEXT("Barrel and turret set in Aimingcomp"))
	return;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	
}

void UTankAimingComponent::AimForFire(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// We have omitted a lot of parameters which the method asks fore, cause the defaults are good aswell
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		6.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	)){ 
		auto AimVector = OutLaunchVelocity.GetSafeNormal();
		SetAim(AimVector);
		// auto Time = GetWorld()->GetTimeSeconds();
		
	}
	else {
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("Solution Failed: %f."), Time)

	}
	return;
}


void UTankAimingComponent::SetAim(FVector AimVector)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	// Getcurrent Barrel rotation and also Translate SafeVector to worldrotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimVector.Rotation();
	auto BarrelDeltaRotator = AimRotator - BarrelRotation;
	auto TurretDeltaRotator = AimRotator - TurretRotation;

	// if (BarrelDeltaRotator.Pitch < 0.1f || TurretDeltaRotator.Yaw < 0.1f) { FiringStatus = EFiringStatus::Locked; }

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	Turret->Rotate(TurretDeltaRotator.Yaw);

	return;
}

void UTankAimingComponent::Fire()
{
	// FPlatformTime is not really documented and even the tech does not know what it is, but it is good to use
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	// spawn projectile at socket location
	if (isReloaded) {
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

