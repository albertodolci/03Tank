// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	class UMeshTorretta* Cannone;
	class UMeshTorretta* Torre;

public:	
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	

	UPROPERTY(EditAnywhere, Category = "Fuoco")
	float VelLancio;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	void RuotaCannone(FVector &Velocity);
	
	FORCEINLINE UMeshTorretta* GetCannone() { return Cannone; }

	UFUNCTION(BlueprintCallable)
		void SetCannone(UMeshTorretta* Cannon);

	FORCEINLINE UMeshTorretta* GetTorre() { return Torre; }

	UFUNCTION(BlueprintCallable)
		void SetTorre(UMeshTorretta* Turret);


};
