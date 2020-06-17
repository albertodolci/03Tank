// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshCingolo.h"


UMeshCingolo::UMeshCingolo()
{
	ForzaMaxCingolo = 25000000.f;

}


void UMeshCingolo::RichiestaMovimento(float Movimento)
{
	if (Movimento != 0)
	{
	//UE_LOG(LogTemp, Warning, TEXT("input = %f"), Movimento);

	FVector ForzaApplicata = GetForwardVector() * ForzaMaxCingolo * Movimento;
	FVector ForzaLocazione = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );

	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(ForzaApplicata, ForzaLocazione);
	}//AddForceAtLocationLocal

	}
}