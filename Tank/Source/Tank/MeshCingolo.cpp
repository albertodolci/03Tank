// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshCingolo.h"
#include "Ammortizzatore.h"
#include "SpawnPoint.h"


UMeshCingolo::UMeshCingolo()
{
	ForzaMaxCingolo  = 25000000.f;
	//MovimentoAttualeRG = 0.f;
	//MovimentoAttualeFW = 0.f;
}


void UMeshCingolo::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UMeshCingolo::OnHit);
}

/*
void UMeshCingolo::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Error, TEXT("onhit"));

	MovimentoReale(MovimentoAttualeFW);
	MovimentoReale(MovimentoAttualeRG);

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
    auto VelScivolamento = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	auto Correzione = -VelScivolamento * GetRightVector() * DeltaTime;
	auto ForzaCorrezione = TankRoot->GetMass()*Correzione;

	TankRoot->AddForce(ForzaCorrezione);
	

	
}*/

void UMeshCingolo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	 Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMeshCingolo::RichiestaMovimento(float Movimento)
{
	MovimentoReale(Movimento);
}



void UMeshCingolo::MovimentoReale(float & Movimento)
{
	/*
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

	}*/

	
	//Movimento = FMath::Clamp<float>(Movimento, -1, 1);

	float ForzaApplicata = Movimento * ForzaMaxCingolo;
	auto Wheels = GetWheels();

	float ForzaperRuota = ForzaApplicata / Wheels.Num();

	for (int i = 0; i < Wheels.Num(); i++)
	{
		Wheels[i]->ApplicaForzadiGuida(ForzaperRuota);
	}
	


}

TArray<class AAmmortizzatore*> UMeshCingolo::GetWheels()
{
	TArray<AAmmortizzatore*> ResultArray;
	TArray<USceneComponent*>    Children;

	GetChildrenComponents(true, Children);

	for (int i = 0; i < Children.Num(); i++)
	{
		auto MySpawn = Cast<USpawnPoint>(Children[i]);
		if (MySpawn) ResultArray.Add(Cast<AAmmortizzatore>(MySpawn->GetAbsorber()));
	}

	return ResultArray;
}

