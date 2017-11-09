// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle){

	// UE_LOG(LogTemp, Warning, TEXT("Throttle Set to %f."), Throttle)

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return;
}

