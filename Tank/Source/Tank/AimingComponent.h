// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

UENUM()
enum class EAimingStatus : uint8
{
	movimento,
	mira,
	ricarica,
	generico
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	class UMeshTorretta* Cannone;
	class UMeshTorretta* Torre;

	UPROPERTY(VisibleAnywhere, Category = "Enum")
	EAimingStatus miamira = EAimingStatus::movimento;

	UPROPERTY(EditAnywhere,Category = "Fuoco")
		int32 Munizioni;
public:	
	// Sets default values for this component's properties
	UAimingComponent();

	UFUNCTION(BlueprintPure, Category = "Enum")
	FORCEINLINE EAimingStatus GetStato(){ return miamira; }

	void SetStato(uint8 New_Status);

	UFUNCTION(BlueprintPure, Category = "Enum")
	FORCEINLINE int32 GetMunizioni() { return Munizioni; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SetUp")
		TSubclassOf<class AProiettile>  Projectile;

public:	

	UPROPERTY(EditAnywhere, Category = "SetUp")
	float ReloadTime;

	float Reload;

	UPROPERTY(EditAnywhere, Category = "Fuoco")
	float VelLancio;

	UFUNCTION(BlueprintCallable, Category = "Fuoco")
	void Spara();

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
