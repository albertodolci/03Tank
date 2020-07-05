// Fill out your copyright notice in the Description page of Project Settings.


#include "Proiettile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProiettile::AProiettile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	BlastLaunch = CreateDefaultSubobject<UParticleSystemComponent>(FName("BlastLaunch"));
	BlastImpact = CreateDefaultSubobject<UParticleSystemComponent>(FName("BlastImpact"));

	Movimento = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movimento"));
	Movimento->bAutoActivate = false;

	ForzaEsplosiva = CreateDefaultSubobject<URadialForceComponent>(FName("ForzaEsplosiva"));

	Damage = 10.f;

}


// Called when the game starts or when spawned
void AProiettile::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AProiettile::OnHit);

	BlastLaunch->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
	BlastImpact->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	ForzaEsplosiva->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	BlastImpact->Deactivate();
}


// Called every frame
void AProiettile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProiettile::Lancio(float speed)
{
	Movimento->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	Movimento->Activate();
}


void AProiettile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

	BlastImpact->Activate();
	BlastLaunch->Deactivate();
	Mesh->SetVisibility(false);
	ForzaEsplosiva->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(
		this,
		Damage,
		GetActorLocation(),
		ForzaEsplosiva->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()

	);


}

