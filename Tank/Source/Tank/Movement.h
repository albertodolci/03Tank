// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Movement.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANK_API UMovement : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:

	//UMovement();

	class UMeshCingolo* CingoloDX;

	class UMeshCingolo* CingoloSX;

	UFUNCTION(BlueprintCallable, Category = "Controlli")
	void MovimentoLaterale(float movimentoA);

	UFUNCTION(BlueprintCallable, Category = "Controlli")
	void MovimentoAvanti(float movimentoA);

	UFUNCTION(BlueprintCallable, Category = "Controlli")
	void SetCingoli(UMeshCingolo* refSX , UMeshCingolo* refDX);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
