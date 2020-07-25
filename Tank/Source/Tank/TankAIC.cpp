// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIC.h"
#include "TankC.h"
#include "Engine/World.h"
#include "TankPC.h"
#include "AimingComponent.h"


ATankAIC::ATankAIC()
{
	Timer = FMath::FRandRange(3.f, 6.f);
	RaggioMin = 1000.f;
	RaggioFuoco = 30000.f;
	PrimaryActorTick.bCanEverTick = true;

	R_MIN = 3.f;
	R_MAX = 6.f;

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

void ATankAIC::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto CarroControllato = GetTank();
		if (!CarroControllato) return;
		CarroControllato->OnDeath.AddUniqueDynamic(this, &ATankAIC::OnPossessedTankDeath);
		UE_LOG(LogTemp, Warning, TEXT("Set Pawn abilitato!"));
	}

}

void ATankAIC::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	auto Bersaglio = GetPlayerTank();

	if (Bersaglio && GetTank() )
	{

     	GetTank()->AimingC->AimAt(Bersaglio->GetActorLocation());
		
		float dist = FVector::Dist(Bersaglio->GetActorLocation(), GetTank()->GetActorLocation());

		MoveToActor(Bersaglio, RaggioMin);
		
		if (Timer > 0) Timer -= DeltaTime;
		else
		{
			if (GetTank()->AimingC->GetStato() == EAimingStatus::mira && dist < RaggioFuoco)
			{
				GetTank()->AimingC->Spara();
				Timer = FMath::FRandRange(R_MIN, R_MAX);
				//UE_LOG(LogTemp, Warning, TEXT("Distancex %f"), dist);
			}

		}
	}
}

void ATankAIC::OnPossessedTankDeath()
{

	//UE_LOG(LogTemp, Warning, TEXT("Evento On  Death"));
	GetTank()->DestroyDelay();
	//GetTank()->DetachFromControllerPendingDestroy();
	DetachFromPawn();
}

ATankC* ATankAIC::GetTank() const
{
	return Cast<ATankC>(GetPawn());
}
