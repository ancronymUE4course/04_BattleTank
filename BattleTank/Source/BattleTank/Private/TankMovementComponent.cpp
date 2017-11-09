// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	return;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	
	if (!ensure(LeftTrack || !RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
	return;
}

void UTankMovementComponent::IntendTurn(float Throw) {
	if (!ensure(LeftTrack || !RightTrack)) { return; }

	// auto TankName = GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s Turn Throw: %f"),*TankName,Throw)

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	return;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	
	// No need to call super, as we replace functionality of parent

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));
	
	float TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurn(TurnThrow);

	return;
}

void UTankMovementComponent::ResetTank() {

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator NewRotation = FRotator(0.f, CurrentYaw, 0.f);	
	GetOwner()->SetActorRotation(NewRotation);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 100.f);
	GetOwner()->SetActorLocation(NewLocation);
	
	return;
}



