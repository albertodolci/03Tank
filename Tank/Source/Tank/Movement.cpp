// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement.h"
#include "MeshCingolo.h"

void UMovement::MovimentoLaterale(float movimentoA)
{
	//UE_LOG(LogTemp, Warning, TEXT("Avanti %f"), movimentoA);
	if (!CingoloDX || !CingoloSX) return;
	CingoloDX->RichiestaMovimento(-movimentoA);
	CingoloSX->RichiestaMovimento(movimentoA);

}

void UMovement::MovimentoAvanti(float movimentoA)
{
	//UE_LOG(LogTemp, Warning, TEXT("Laterale %f"), movimentoA);
	if (!CingoloDX || !CingoloSX) return;
	CingoloDX->RichiestaMovimento(movimentoA);
	CingoloSX->RichiestaMovimento(movimentoA);
}

void UMovement::SetCingoli(UMeshCingolo * refSX, UMeshCingolo * refDX)
{
	CingoloDX = refDX;
	CingoloSX = refSX;
}

void UMovement::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s velocity %s"),*GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString());

	FVector IntAvanti = MoveVelocity.GetSafeNormal();
	FVector TankAvanti = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float   prodottoscalare = FVector::DotProduct(IntAvanti, TankAvanti);
	MovimentoAvanti(prodottoscalare);

	float   prodottovettoriale = FVector::CrossProduct(IntAvanti, TankAvanti).Z;
	MovimentoLaterale(prodottovettoriale);

}

/*
void UMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp,Warning,TEXT("sono un movement di %s"), *GetOwner()->GetName());
}
*/