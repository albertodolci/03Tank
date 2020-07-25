// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammortizzatore.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AAmmortizzatore::AAmmortizzatore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Molla = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Molla"));
	SetRootComponent(Molla);

	Asse = CreateDefaultSubobject<USphereComponent>(FName("Asse"));
	Asse->SetupAttachment(Molla);

	Rotore = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Rotore"));
	Rotore->SetupAttachment(Asse);

	Ruota = CreateDefaultSubobject<USphereComponent>(FName("Ruota"));
	Ruota->SetupAttachment(Rotore);
	
	SpintaReale = 0;
}

// Called when the game starts or when spawned
void AAmmortizzatore::BeginPlay()
{
	Super::BeginPlay();
	SetUpConnessioni();
	Ruota->OnComponentHit.AddDynamic(this, &AAmmortizzatore::OnHit);
}

void AAmmortizzatore::SetUpConnessioni()
{
	auto parent = GetAttachParentActor();
	if (!parent) return;

	auto Body = Cast<UPrimitiveComponent>(parent->GetRootComponent());
	if (!Body) return;

	Molla->SetConstrainedComponents(Body, NAME_None, Asse, NAME_None);
	Rotore->SetConstrainedComponents(Asse, NAME_None, Ruota, NAME_None);
}



// Called every frame
void AAmmortizzatore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		SpintaReale = 0;
	}
}

void AAmmortizzatore::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("On Hit %f"), GetWorld()->GetTimeSeconds());
	Ruota->AddForce(Asse->GetForwardVector() * SpintaReale);
}


void AAmmortizzatore::ApplicaForzadiGuida(float spinta)
{

	SpintaReale+=spinta;
	//Ruota->AddForce(Asse->GetForwardVector() * spinta);

}