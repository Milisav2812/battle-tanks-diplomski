// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

// Forward Includes
class UCapsuleComponent;
class AProjectile;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class BATTLETANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	ABasePawn();

	void HandleDestruction();

	// Getters
	USceneComponent* GetProjectileSpawnPoint();
	UStaticMeshComponent* GetBaseMesh();

protected:
	void RotateTurret(FVector LookAtLocation);
	void Fire();

private:
	// Parts of the Tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Main Components")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Main Components")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Main Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Main Components")
	USceneComponent* ProjectileSpawnPoint;

	// Tank Projectile
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	// Sound & Visual Effects
	UPROPERTY(EditAnywhere, Category = "Death")
	UParticleSystem* DeathParticles;
	UPROPERTY(EditAnywhere, Category = "Death")
	USoundBase* DestroySound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> PawnDeathCameraShake;

};
