// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

	AActor* MyAbsorber;

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	FORCEINLINE AActor* GetAbsorber() { return MyAbsorber; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AActor> SpawnClass;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
