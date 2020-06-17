// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIC.h"
#include "TankC.h"
#include "Engine/World.h"
#include "TankPC.h"



ATankAIC::ATankAIC()
{
	Timer = FMath::FRandRange(3.f, 6.f);
	RaggioMax = 1000.f;
	PrimaryActorTick.bCanEverTick = true;
}



ATankC * ATankAIC::GetPlayerTank() const
{

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	return Cast<ATankC>(controller->GetPawn());
	
}

void ATankAIC::BeginPlay()
{

	Super::BeginPlay();

	auto CarroControllato = GetTank();
	auto CarroNemico = GetPlayerTank();

	if (!CarroControllato || !CarroNemico) return;

	if (CarroControllato)
	{
		UE_LOG(LogTemp, Warning, TEXT("trovato! %s"), *CarroControllato->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non trovato!") );
	}

}

void ATankAIC::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	auto Bersaglio = GetPlayerTank();

	if (Bersaglio && GetTank() )
	{

     	GetTank()->AimAt(Bersaglio->GetActorLocation());
		
		MoveToActor(Bersaglio, RaggioMax);
		//UE_LOG(LogTemp, Error, TEXT("path = %i"), path);



		//MoveToActor(Bersaglio, 0);
		//path =  MoveToLocation(Bersaglio->GetActorLocation());

		//UE_LOG(LogTemp, Error, TEXT("path = %i"), path);

		if (Timer > 0) Timer -= DeltaTime;
		else
		{
			GetTank()->Spara();
			Timer = FMath::FRandRange(3.f, 6.f);
		}

		

	}

}

ATankC* ATankAIC::GetTank() const
{
	return Cast<ATankC>(GetPawn());
}
