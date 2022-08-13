// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterTank.h"

#include "Tower.h"
#include "Tank.h"
#include "BasePawn.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraShakeBase.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
AEnemyCharacterTank::AEnemyCharacterTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacterTank::BeginPlay()
{
	Super::BeginPlay();

	auto Comps = GetComponentsByClass(UStaticMeshComponent::StaticClass());

	for (auto Comp : Comps)
	{
		if (Comp->GetName() == "Base Mesh")
		{
			BaseMesh = Cast<UStaticMeshComponent>(Comp);
			// UE_LOG(LogTemp, Warning, TEXT("Found %s"), *BaseMesh->GetName())
		}
		else if (Comp->GetName() == "Turret Mesh")
		{
			TurretMesh = Cast<UStaticMeshComponent>(Comp);
			// UE_LOG(LogTemp, Warning, TEXT("Found %s"), *TurretMesh->GetName())
		}
	}

	auto SceneComps = GetComponentsByClass(USceneComponent::StaticClass());
	for (auto SceneComp : SceneComps)
	{
		if (SceneComp->GetName() == "Projectile Spawn Point")
		{
			ProjectileSpawnPoint = Cast<USceneComponent>(SceneComp);
			// UE_LOG(LogTemp, Warning, TEXT("Found %s"), *ProjectileSpawnPoint->GetName())
		}
	}

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Setting the Timer
	GetWorldTimerManager().SetTimer(
		FireTimerHandle,
		this,								// The object for which this timer is called
		&AEnemyCharacterTank::CheckIfFireConditionIsMet,
		FireRate,
		true								// Do we want the timer to loop?
	);
	
}

// Called every frame
void AEnemyCharacterTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotating the Tower Turret
	if (CheckIfWithinRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}

}

void AEnemyCharacterTank::RotateTurret(FVector LookAtLocation)
{
	// Vector that has a starting position in the tank turret and an end position at our mouse cursor
	FVector TargetVector = LookAtLocation - TurretMesh->GetComponentLocation();

	// Turret will only rotate in Yaw 
	FRotator TargetRotation = FRotator(0, TargetVector.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(TargetRotation);
}

void AEnemyCharacterTank::Fire()
{

	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
		);

	SpawnedProjectile->SetOwner(this);

	if (SpawnedProjectile->GetLaunchSound())
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			SpawnedProjectile->GetLaunchSound(),
			SpawnedProjectile->GetActorLocation()
		);
	}
}


void AEnemyCharacterTank::HandleDestruction()
{
	// Visual / Sound Effects go here

	// Spawn Death Particles
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			DeathParticles,
			RootComponent->GetRelativeTransform()
		);
	}

	if (PawnDeathCameraShake)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(PawnDeathCameraShake);
		}
	}

	if (DestroySound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DestroySound,
			GetActorLocation()
		);
	}

	Destroy();

}

void AEnemyCharacterTank::CheckIfFireConditionIsMet()
{
	FHitResult HitResult;

	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false, // Use Complex or Simple Collision
		GetOwner() // The Actor that the Ray-Cast will ignore
	);

	bool bHitSomething = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint->GetComponentRotation().Vector() * FireDistance,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);

	if (HitResult.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *HitResult.Actor->GetName())
	}

	if (HitResult.Actor == PlayerTank && CheckIfWithinRange() && PlayerTank->bIsPlayerAlive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"))
		Fire();
	}
}

float AEnemyCharacterTank::CheckIfWithinRange()
{
	if (PlayerTank)
	{
		FVector PlayerLocation = PlayerTank->GetActorLocation();
		FVector EnemyLocation = this->GetActorLocation();

		float Distance = FVector::Dist(EnemyLocation, PlayerLocation);

		if (Distance <= FireDistance)
		{
			return true;
		}
	}

	return false;
}

