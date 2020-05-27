// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proiettile.generated.h"

UCLASS()
class TANK_API AProiettile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProiettile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category = "Sparo")
	class UProjectileMovementComponent* Movimento = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Lancio(float speed);

};
