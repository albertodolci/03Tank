// Fill out your copyright notice in the Description page of Project Settings.


#include "TankC.h"
#include "AimingComponent.h"
#include "Proiettile.h"
#include "MeshTorretta.h"

// Sets default values
ATankC::ATankC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimingC = CreateDefaultSubobject<UAimingComponent>(TEXT("AimingC"));
}

// Called when the game starts or when spawned
void ATankC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankC::AimAt(FVector HitLocation)
{
	AimingC->AimAt(HitLocation);

}

void ATankC::SetCannone(UMeshTorretta* Cannon)
{
	Cannone = Cannon;

}

void ATankC::Spara()
{
	UE_LOG(LogTemp, Error, (TEXT("Sparo a Salve!!")));

	auto Gianfranco = GetWorld()->SpawnActor<AProiettile>(
		Projectile,
		Cannone->GetSocketLocation(FName("Proiettile")),
		Cannone->GetSocketRotation(FName("Proiettile"))
		);

	Gianfranco->Lancio(AimingC->VelLancio);


}

// Called every frame
void ATankC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

