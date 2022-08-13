// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterTank.generated.h"

class UCapsuleComponent;
class AProjectile;
class UParticleSystem;
class USoundBase;
class UCameraShakeBase;
class ATank;

UCLASS()
class BATTLETANKS_API AEnemyCharacterTank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
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

	UStaticMeshComponent* BaseMesh;
	UStaticMeshComponent* TurretMesh;
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Death")
		UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Death")
		USoundBase* DestroySound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<UCameraShakeBase> PawnDeathCameraShake;

	// Fire Distance 
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireDistance = 1000;
	float CheckIfWithinRange();

	ATank* PlayerTank;

	// Timer and Fire functionality
	FTimerHandle FireTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;
	void CheckIfFireConditionIsMet();

};
