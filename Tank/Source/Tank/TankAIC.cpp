// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIC.h"
#include "TankC.h"
#include "Engine/World.h"
#include "TankPC.h"

ATankC * ATankAIC::GetPlayerTank() const
{

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	return Cast<ATankC>(controller->GetPawn());
	
}

void ATankAIC::BeginPlay()
{
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

	if ( GetPlayerTank() && GetTank() )
	{

     	GetTank()->AimAt(GetPlayerTank()->GetActorLocation());

		if (Timer > 0) Timer -= DeltaTime;
		else
		{
			GetTank()->Spara();
			Timer = FMath::FRandRange(3.f, 6.f);
		}
	}

}


ATankAIC::ATankAIC()
{
	Timer = FMath::FRandRange(3.f,6.f);


}

ATankC* ATankAIC::GetTank() const
{
	return Cast<ATankC>(GetPawn());
}
