// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterTank.h"

#include "Tower.h"
#include "Tank.h"
#include "BasePawn.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/MovementComponent.h"

AEnemyCharacterTank::AEnemyCharacterTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacterTank::BeginPlay()
{
	Super::BeginPlay();

	// Getting all UStaticMeshComponents and Initialization
	auto Comps = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (auto Comp : Comps)
	{
		if (Comp->GetName() == "Base Mesh")
		{
			BaseMesh = Cast<UStaticMeshComponent>(Comp);
		}
		else if (Comp->GetName() == "Turret Mesh")
		{
			TurretMesh = Cast<UStaticMeshComponent>(Comp);
		}
	}

	// Getting all USceneComponent and Initialization
	auto SceneComps = GetComponentsByClass(USceneComponent::StaticClass());
	for (auto SceneComp : SceneComps)
	{
		if (SceneComp->GetName() == "Projectile Spawn Point")
		{
			ProjectileSpawnPoint = Cast<USceneComponent>(SceneComp);
		}
	}

	// Getting all UMovementComponent and Initialization
	auto MoveComps = GetComponentsByClass(UMovementComponent::StaticClass());
	for (auto MoveComp : MoveComps)
	{
		if (MoveComp->GetName() == "CharMoveComp")
		{
			MovementComponent = Cast<UMovementComponent>(MoveComp);
		}
	}

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Setting the Timer
	GetWorldTimerManager().SetTimer(
		FireTimerHandle,
		this,								
		&AEnemyCharacterTank::CheckIfFireConditionIsMet,
		FireRate,
		true								
	);
	
}

// Called every frame
void AEnemyCharacterTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (CheckIfWithinRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}

	if (MovementComponent->IsActive() == false)
	{
		MovementComponent->SetActive(true);
	}
}

float AEnemyCharacterTank::CheckIfWithinRange()
{
	if (ensure(PlayerTank))
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

void AEnemyCharacterTank::RotateTurret(FVector LookAtLocation)
{
	FVector TargetVector = LookAtLocation - TurretMesh->GetComponentLocation();

	// Turret will only rotate in Yaw 
	FRotator TargetRotation = FRotator(0, TargetVector.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(TargetRotation);
}

void AEnemyCharacterTank::CheckIfFireConditionIsMet()
{
	FHitResult HitResult;

	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false, // Use Complex or Simple Collision
		GetOwner() // The Actor that the Ray-Cast will ignore
	);

	// Creates an Imaginary line from the Projectile Spawn Point
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint->GetComponentRotation().Vector() * FireDistance,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);

	if (HitResult.Actor == PlayerTank && CheckIfWithinRange())
	{
		// Disable movement if the player is in view - Stop Enemy Tank
		if (ensure(MovementComponent) && MovementComponent->IsActive())
		{
			MovementComponent->SetActive(false);
		}

		Fire();
	}
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
	if (ensure(DeathParticles))
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			DeathParticles,
			RootComponent->GetRelativeTransform()
		);
	}

	if (ensure(PawnDeathCameraShake))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(PawnDeathCameraShake);
		}
	}

	if (ensure(DestroySound))
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DestroySound,
			GetActorLocation()
		);
	}

	Destroy();
}



