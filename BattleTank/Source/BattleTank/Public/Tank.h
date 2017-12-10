// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be the last include!

// Forward declarations

class UParticleSystemComponent;
class UTankAimingComponent;
class UTankMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Will be called by the engine, if damage should be applied
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Returns healt between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// Public, because another class will need access to it
	FTankDeathDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
private:	
	// Sets default values for this pawn's properties
	ATank();

	void Death();	

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* DeathBlast = nullptr;
	
	UTankAimingComponent* AimingComponent = nullptr;
	UTankMovementComponent* MovementComponent = nullptr;
};
