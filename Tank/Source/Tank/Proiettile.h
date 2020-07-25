// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proiettile.generated.h"

UCLASS()
class TANK_API AProiettile : public AActor
{
	GENERATED_BODY()



		UPROPERTY(EditAnywhere, Category = "Sparo")
		float Damage;

public:	
	// Sets default values for this actor's properties
	AProiettile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category = "Sparo")
	class UProjectileMovementComponent* Movimento = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sparo")
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sparo")
	class UParticleSystemComponent* BlastLaunch = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sparo")
	class UParticleSystemComponent* BlastImpact = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Sparo")
	class URadialForceComponent* ForzaEsplosiva = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void VDestroy(UObject* ToDestroy);

	void SelfDestruction();

	FTimerHandle timer1;

	void Lancio(float speed);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
