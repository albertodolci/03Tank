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

	ReloadTime = 2.f;

}

// Called when the game starts or when spawned
void ATankC::BeginPlay()
{
	Super::BeginPlay();

	Reload = 0;


}

void ATankC::AimAt(FVector HitLocation)
{
	AimingC->AimAt(HitLocation);
}


void ATankC::Spara()
{
	//	UE_LOG(LogTemp, Error, (TEXT("Sparo a Salve!!")));

	if (Projectile  && GetWorld() && Reload <= 0)
	{
	
	    auto Bullet = GetWorld()->SpawnActor<AProiettile>(
		Projectile,
		AimingC->GetCannone()->GetSocketLocation(FName("Proiettile")),
		AimingC->GetCannone()->GetSocketRotation(FName("Proiettile"))
		);

	    Bullet->Lancio(AimingC->VelLancio);

		Reload = ReloadTime;
    }

}

// Called every frame
void ATankC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Reload > 0) Reload -= DeltaTime;

}

// Called to bind functionality to input
void ATankC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

