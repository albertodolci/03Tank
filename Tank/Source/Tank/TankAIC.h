// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIC.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankAIC : public AAIController
{
	GENERATED_BODY()

	float Timer;

public:

	ATankAIC();

	UPROPERTY(EditAnyWhere,Category = "AI")
	float RaggioMin;

	UPROPERTY(EditAnyWhere, Category = "AI")
	float RaggioFuoco;

	class ATankC* GetTank() const;

	class ATankC* GetPlayerTank() const;

	virtual void  BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "AI")
	float R_MIN;

	UPROPERTY(EditAnyWhere, Category = "AI")
	float R_MAX;

	virtual void  SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void  Tick(float DeltaTime) override;

	

};
