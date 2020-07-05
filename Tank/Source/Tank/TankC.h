// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankCDelegate);

UCLASS()
class TANK_API ATankC : public APawn
{
	GENERATED_BODY()

	bool ismorto;

public:
	// Sets default values for this pawn's properties
	ATankC();

	FTankCDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = "Stats")
	float Resistenza;

	float ResistenzaAttaule;
public:	

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetPercent();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyDelay();

	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor* DamageCauser) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	      class UAimingComponent* AimingC;

	//UFUNCTION(BlueprintCallable,Category = "Fuoco")
	//void Spara();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
