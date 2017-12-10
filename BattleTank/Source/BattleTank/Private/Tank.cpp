// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystemComponent.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

	//DeathBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Death Blast"));
	// DeathBlast->AttachToComponent(, FAttachmentTransformRules::KeepRelativeTransform);
	//DeathBlast->bAutoActivate =false;

}



// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay(); // needed for BP beginplay to be called!
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Dam amount: %d and Dam applied: %d and Health: %d"), DamagePoints, DamageToApply,CurrentHealth);

	if (CurrentHealth <= 0) { Death(); }
	return DamageToApply;	
}

void ATank::Death() {
	UE_LOG(LogTemp,Warning,TEXT("Death called."))
	OnDeath.Broadcast();	
}

float ATank::GetHealthPercent() const
{

	return (float)CurrentHealth/(float)StartingHealth;
}