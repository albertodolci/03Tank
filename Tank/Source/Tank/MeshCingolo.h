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

	virtual void BeginPlay() override;

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnyWhere, Category = "Controls")
		float ForzaMaxCingolo;

	UFUNCTION(BlueprintCallable, Category = "Controls")
		void  RichiestaMovimento(float Movimento);

	//UFUNCTION(BlueprintCallable, Category = "Controls")
	//	void  RichiestaMovimento(float Movimento);

	void MovimentoReale(float &Movimento);

	TArray<class AAmmortizzatore*> GetWheels();

private:

//	float MovimentoAttualeFW;
//	float MovimentoAttualeRG;

};
