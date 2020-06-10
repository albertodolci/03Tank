// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankC.generated.h"

UCLASS()
class TANK_API ATankC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SetUp")
		TSubclassOf<class AProiettile>  Projectile;
 
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	      class UAimingComponent* AimingC;

	UPROPERTY(EditAnywhere, Category = "SetUp")
	float ReloadTime;

	float Reload;


	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable,Category = "Fuoco")
	void Spara();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
