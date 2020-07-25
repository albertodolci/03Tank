// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammortizzatore.generated.h"

UCLASS()
class TANK_API AAmmortizzatore : public AActor
{
	GENERATED_BODY()
	

    UPROPERTY(VisibleAnywhere, Category = "Fisica")
		class USphereComponent* Asse = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Fisica")
		      USphereComponent* Ruota = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Fisica")
		class UPhysicsConstraintComponent* Molla = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Fisica")
		      UPhysicsConstraintComponent* Rotore = nullptr;

	float  SpintaReale;

public:	
	// Sets default values for this actor's properties
	AAmmortizzatore();

	void ApplicaForzadiGuida(float spinta);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetUpConnessioni();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
