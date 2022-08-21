// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterTank.generated.h"

// Forward Includes 
class UCapsuleComponent;
class AProjectile;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;
class ATank;
class UMovementComponent;

UCLASS()
class BATTLETANKS_API AEnemyCharacterTank : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacterTank();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtLocation);
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Enemy Tank Parts
	UStaticMeshComponent* BaseMesh;
	UStaticMeshComponent* TurretMesh;
	USceneComponent* ProjectileSpawnPoint;
	UMovementComponent* MovementComponent;

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

	// ID of the enemy tank - Used for Patrol Logic
	UPROPERTY(EditInstanceOnly, Category = "Patrol ID", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
	int32 EnemyTankID;

	// Fire Distance 
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireDistance = 1000;
	float CheckIfWithinRange();

	// Player Tank Reference
	ATank* PlayerTank;

	// Timer and Fire functionality
	FTimerHandle FireTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;
	void CheckIfFireConditionIsMet();

};
