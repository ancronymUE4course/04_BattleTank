// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be the last include!

// Forward declarations




UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:	
	// Sets default values for this pawn's properties
	ATank();	
	
};
