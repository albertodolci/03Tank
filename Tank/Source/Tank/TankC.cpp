// Fill out your copyright notice in the Description page of Project Settings.


#include "TankC.h"
#include "AimingComponent.h"

// Sets default values

ATankC::ATankC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimingC = CreateDefaultSubobject<UAimingComponent>(TEXT("AimingC"));
	Resistenza = 50.f;
	ismorto = false;
}

// Called when the game starts or when spawned
void ATankC::BeginPlay()
{
	Super::BeginPlay();
	ResistenzaAttaule = Resistenza;
}

float ATankC::GetPercent()
{
	return  ResistenzaAttaule / Resistenza;
}

float ATankC::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int16 Danni = FPlatformMath::RoundToInt(DamageAmount);
	Danni = FMath::Clamp<int16>(Danni, 0, ResistenzaAttaule);

	ResistenzaAttaule -= Danni;

	if (ResistenzaAttaule <= 0  && !ismorto) 
	{
		ismorto = true;
		UE_LOG(LogTemp, Error, TEXT("Sono Morto"));
		OnDeath.Broadcast();
	}
		

	return Danni;
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

