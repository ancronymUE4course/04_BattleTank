// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UTankAimingComponent::AimForFire(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	
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
		// UE_LOG(LogTemp, Warning, TEXT("Found Solution! %f."), Time)
	}
	else {
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("Solution Failed: %f."), Time)

	}
	return;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	return;
}

void UTankAimingComponent::SetTurretReference(UTurret * TurretToSet)
{
	Turret = TurretToSet;
	return;
}

void UTankAimingComponent::SetAim(FVector AimVector)
{
	// Getcurrent Barrel rotation and also Translate SafeVector to worldrotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimVector.Rotation();
	auto BarrelDeltaRotator = AimRotator - BarrelRotation;
	auto TurretDeltaRotator = AimRotator - TurretRotation;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	Turret->Rotate(TurretDeltaRotator.Yaw);

	// UE_LOG(LogTemp, Warning, TEXT("Aim Rotation %s"), *AimRotator.ToString())

	return;
}

