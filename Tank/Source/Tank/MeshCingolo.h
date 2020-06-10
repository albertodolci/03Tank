// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MeshCingolo.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANK_API UMeshCingolo : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UMeshCingolo();

	UPROPERTY(EditAnyWhere, Category = "Controls")
		float ForzaMaxCingolo;

	UFUNCTION(BlueprintCallable, Category = "Controls")
		void  RichiestaMovimento(float Movimento);

};
