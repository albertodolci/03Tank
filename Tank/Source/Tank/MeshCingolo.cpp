// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshCingolo.h"


UMeshCingolo::UMeshCingolo()
{
	ForzaMaxCingolo  = 25000000.f;
	MovimentoAttualeRG = 0.f;
	MovimentoAttualeFW = 0.f;
}


void UMeshCingolo::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UMeshCingolo::OnHit);
}

void UMeshCingolo::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Error, TEXT("onhit"));

	MovimentoReale(MovimentoAttualeFW);
	MovimentoReale(MovimentoAttualeRG);

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
    auto VelScivolamento = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	auto Correzione = -VelScivolamento * GetRightVector() / DeltaTime;
	auto ForzaCorrezione = TankRoot->GetMass()*Correzione / 2;

	TankRoot->AddForce(ForzaCorrezione);
	
	/*
	VelScivolamento = FVector::DotProduct(GetForwardVector(),GetComponentVelocity());
	Correzione = -VelScivolamento * GetForwardVector() / DeltaTime;
	ForzaCorrezione = TankRoot->GetMass()*Correzione / 2;

	TankRoot->AddForce(ForzaCorrezione);
	*/
	
}

void UMeshCingolo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	 Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMeshCingolo::RichiestaMovimentoRG(float Movimento)
{
	//MovimentoAttuale = FMath::Clamp<float>(MovimentoAttuale + Movimento, -1, 1);

	MovimentoAttualeRG = Movimento;
}

void UMeshCingolo::RichiestaMovimentoFW(float Movimento)
{
	//MovimentoAttuale = FMath::Clamp<float>(MovimentoAttuale + Movimento, -1, 1);

	MovimentoAttualeFW = Movimento;
}

void UMeshCingolo::MovimentoReale(float & Movimento)
{
	if (Movimento != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("input = %f"), Movimento);

		FVector ForzaApplicata = GetForwardVector() * ForzaMaxCingolo * Movimento;
		FVector ForzaLocazione = GetComponentLocation();
		UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

		if (TankRoot)
		{
			TankRoot->AddForceAtLocation(ForzaApplicata, ForzaLocazione);
		}//AddForceAtLocationLocal

	}

}

