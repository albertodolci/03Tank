// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPC.h"
#include "TankC.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "AimingComponent.h"

void ATankPC::BeginPlay()
{
	Super::BeginPlay();

    auto CarroControllato = GetTank();
	if (CarroControllato)
	{
    UE_LOG(LogTemp, Warning, TEXT("trovato! %s"), *CarroControllato->GetName());
    }
	else 
	{
	UE_LOG(LogTemp, Warning, TEXT("Non trovato!"));
	}

}


void ATankPC::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto CarroControllato = GetTank();
		if (!CarroControllato) return;
		CarroControllato->OnDeath.AddUniqueDynamic(this, &ATankPC::OnPossessedTankDeath);
		UE_LOG(LogTemp, Warning, TEXT("Set Pawn abilitato!"));
	}

}

void ATankPC::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Evento On  Death"));

	GetTank()->DestroyDelay();
	StartSpectatingOnly();

	

}


void ATankPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mira();
}

void ATankPC::Mira()
{
	if (!GetTank()) return;

	FVector HitLocation;

	if ( TrovaVista( HitLocation ) )
	{
		GetTank()->AimingC->AimAt(HitLocation);
    }

}

bool ATankPC::TrovaVista(FVector & Location)
{
	//individuare la zona mirata
	int32 viewX, viewY;
	GetViewportSize(viewX,viewY);
	FVector2D AimZone = FVector2D(viewX*crossX, viewY*crossY);

	//convertire tale zona in un vettore 3D	//FVector rrrrr;
	FVector Direzione;

	TrovaDirezione(AimZone, Direzione);

	//creare un line trace in quella direzione
	FVector HitLocation;

	if ( !TrovaHit( Direzione , HitLocation ) ) return false;

	Location = HitLocation;

	return true;
}

bool ATankPC::TrovaDirezione(FVector2D ScreenLocation, FVector & Direzione)
{
	FVector WorldLocation;
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		Direzione
	);

}

bool ATankPC::TrovaHit(FVector Direzione, FVector & HitLocation)
{
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	FHitResult Hit;

	FVector Endline = StartLocation + Direzione * LineTraceRange;

	if ( GetWorld()->LineTraceSingleByChannel(
		  
		 Hit,
		 StartLocation,
		 Endline,
		 ECollisionChannel::ECC_Visibility) )
	{

		HitLocation = Hit.Location;
		return true;
	}

	HitLocation = FVector(0, 0, 0);
	return false;
}


ATankPC::ATankPC()
{

	 LineTraceRange = 100000.f;
	 crossX = 0.5;
	 crossY = 0.3;

}

UAimingComponent * ATankPC::GetMirino()
{
	return GetTank()->AimingC;
}

ATankC* ATankPC::GetTank() const
{
	return Cast<ATankC>(GetPawn());
}