// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MeshTorretta.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANK_API UMeshTorretta : public UStaticMeshComponent
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float RotMaxSec;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ElevazioneMax;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ElevazioneMin;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float RotHMaxSec;

public:

	UMeshTorretta();

	void Eleva(float velrelativa);


	void Ruota(float velrelativa);


};
