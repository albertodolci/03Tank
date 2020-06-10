// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MeshTorretta.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	VelLancio = 100000.f;
	// ...
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AimingC Activate %s"), *GetOwner()->GetName());
	// ...
	
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

