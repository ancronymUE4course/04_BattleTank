// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; // Forward declaration, we can define more than one class in a header file ... wut
class UTurret;

class AProjectile;

// Enum for aiming class
UENUM()
enum class EFiringStatus : uint8{
	Reloading,
	Aiming,
	Locked
};

// Holds parameters for Barrels properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseAiming(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimForFire(FVector HitLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	void SetAim(FVector AimVector);
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// UClass* ProjectileBlueprint; // Alternative in the lecture slides
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.f; //TODO find sensible value
	
	// EditDefaultsOnly - enables value editing only for the archetype e.g in BP only, not whilst running
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 5;

	double LastFireTime = 0;

	// FVector AimVector;
	
};
