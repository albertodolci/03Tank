// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIC.h"
#include "TankC.h"
#include "Engine/World.h"


ATankC * ATankAIC::GetPlayerTank() const
{
	auto controller = GetWorld()->GetFirstPlayerController();
	return Cast<ATankC>   (   controller->GetPawn()  );

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



ATankC* ATankAIC::GetTank() const
{
	return Cast<ATankC>(GetPawn());
}
