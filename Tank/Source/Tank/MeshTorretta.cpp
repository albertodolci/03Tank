// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshTorretta.h"

UMeshTorretta::UMeshTorretta()
{
	RotMaxSec = 20.f;

	RotHMaxSec = 30.f;

	ElevazioneMax = 90.f;

	ElevazioneMin = 0.f;

}

void UMeshTorretta::Eleva(float velrelativa)
{

	//UE_LOG(LogTemp, Warning, TEXT("rotazione verso %f"), velrelativa);

	velrelativa = FMath::Clamp<float>(velrelativa, -1, 1);

	float CambioLevatura = velrelativa * RotMaxSec * GetWorld()->DeltaTimeSeconds;

	float NuovaLevatura = GetRelativeRotation().Pitch + CambioLevatura;

	NuovaLevatura = FMath::Clamp<float>(NuovaLevatura, ElevazioneMin, ElevazioneMax);

	SetRelativeRotation(FRotator(NuovaLevatura, 0, 0));

}


void UMeshTorretta::Ruota(float velrelativa)
{

	//UE_LOG(LogTemp, Warning, TEXT("rotazione verso %f"), velrelativa);

	velrelativa = FMath::Clamp<float>(velrelativa, -1, 1);

	float CambioRotazione = velrelativa * RotHMaxSec * GetWorld()->DeltaTimeSeconds;

	float NuovaRotazione = GetRelativeRotation().Yaw + CambioRotazione;

	SetRelativeRotation(FRotator(0, NuovaRotazione, 0));

}