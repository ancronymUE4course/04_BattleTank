// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override; // Oehh, saaks aru siis. Aga override checkib vist üles pärimusteed pidi.

private:
	void LogTankName() const;	
	void LogPlayerTankName() const;
	
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
