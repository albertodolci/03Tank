// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MeshTorretta.h"
#include "Proiettile.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	VelLancio = 100000.f;
	ReloadTime = 2.f;
	Munizioni  = 10;
}

void UAimingComponent::SetStato(uint8 New_Status)
{
	switch (New_Status)
	{
	case 0:
		miamira = EAimingStatus::movimento;
	break;

	case 1:
		miamira = EAimingStatus::mira;
	break;

	case 2:
		miamira = EAimingStatus::ricarica;
	break;

	}
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Reload = 0;
	SetStato(0);
	//UE_LOG(LogTemp, Warning, TEXT("AimingC Activate %s"), *GetOwner()->GetName());
	// ...
	
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Reload > 0) Reload -= DeltaTime;
	// ...
}



void UAimingComponent::Spara()
{
	//	UE_LOG(LogTemp, Error, (TEXT("Sparo a Salve!!")));

	if (Projectile  && GetWorld() && Reload <= 0 && Munizioni > 0)
	{

		auto Bullet = GetWorld()->SpawnActor<AProiettile>(
			Projectile,
			GetCannone()->GetSocketLocation(FName("Proiettile")),
			GetCannone()->GetSocketRotation(FName("Proiettile"))
			);

		Munizioni--;

		UE_LOG(LogTemp, Error, TEXT("ammo = %i"), Munizioni);

		Bullet->Lancio(VelLancio);

		Reload = ReloadTime;
	}

}

void UAimingComponent::AimAt(FVector HitLocation)
{
	// GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("AimingC Activate %s"), *GetOwner()->GetName());
    // UE_LOG(LogTemp, Warning, TEXT("Il Tank  %s"),  *GetOwner()->GetName());
	if (!Cannone)  return;

	FVector Velocity;
	FVector StartLocation = Cannone->GetSocketLocation(FName("Proiettile"));

	bool results = UGameplayStatics::SuggestProjectileVelocity
	(this,          //l'oggetto che esegue 
	 Velocity,      //passata per riferimento direzione da cacolare
	 StartLocation,  
	 HitLocation,   
	 VelLancio,     // forza di lancio
	 false,         // arco alto si o no
     0,             // eventuale raggio di collisione
	 0,             // sovrascrivi gravità
	 ESuggestProjVelocityTraceOption::DoNotTrace  // parametri del trace
     );

	if (results)
	{
		RuotaCannone(Velocity);
	}
}

void UAimingComponent::RuotaCannone(FVector &Velocity)
{
	FVector AimDirection = Velocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("Angolazione %s"), *AimDirection.ToString());

	FRotator RotAttuale = Cannone->GetForwardVector().Rotation();
	FRotator RotObbiettivo = AimDirection.Rotation();
	FRotator DeltaRot = RotObbiettivo - RotAttuale;

	if (Reload>0.1) SetStato(2);
	else
	{
		if (RotAttuale.Equals(RotObbiettivo, 4)) SetStato(1);
		else SetStato(0);
	}

	Cannone->Eleva(DeltaRot.Pitch);

	if (FMath::Abs(DeltaRot.Yaw) < 180)
	{
		Torre->Ruota(DeltaRot.Yaw);
    }
	else
	{
		Torre->Ruota(-DeltaRot.Yaw);
	}	
}

void UAimingComponent::SetCannone(UMeshTorretta* Cannon)
{	
	Cannone = Cannon;

}

void UAimingComponent::SetTorre(UMeshTorretta* Turret)
{
	Torre = Turret;

}

