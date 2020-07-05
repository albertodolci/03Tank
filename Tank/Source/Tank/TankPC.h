// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPC.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankPC : public APlayerController
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnyWhere)
	float LineTraceRange;
	UPROPERTY(EditAnyWhere)
	float crossX;
	UPROPERTY(EditAnyWhere)
	float crossY;

public:

	ATankPC();

	UFUNCTION(BlueprintPure, Category = "SetUp")
	class UAimingComponent* GetMirino();

	class ATankC* GetTank() const;

	virtual void  BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Mira();

	bool TrovaVista(FVector& Location);

	bool TrovaDirezione(FVector2D ScreenLocation, FVector& Direzione);

	bool TrovaHit(FVector Direzione, FVector& HitLocation);

	virtual void  SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();


};
