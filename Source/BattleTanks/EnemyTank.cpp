// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"

#include "Tower.h"
#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

#include "DrawDebugHelpers.h"

// Called when the game starts or when spawned
void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Setting the Timer
	GetWorldTimerManager().SetTimer(
		FireTimerHandle,
		this,								// The object for which this timer is called
		&AEnemyTank::CheckIfFireConditionIsMet,
		FireRate,
		true								// Do we want the timer to loop?
	);

}

// Called every frame
void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Rotating the Tower Turret
	if (CheckIfWithinRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}

}

void AEnemyTank::CheckIfFireConditionIsMet()
{
	FHitResult HitResult;

	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false, // Use Complex or Simple Collision
		GetOwner() // The Actor that the Ray-Cast will ignore
	);

	bool bHitSomething = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetProjectileSpawnPoint()->GetComponentLocation(),
		GetProjectileSpawnPoint()->GetComponentLocation() + GetProjectileSpawnPoint()->GetComponentRotation().Vector() * FireDistance,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);

	if (HitResult.Actor == PlayerTank && CheckIfWithinRange() && PlayerTank->bIsPlayerAlive)
	{
		Fire();
	}
}

float AEnemyTank::CheckIfWithinRange()
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

void AEnemyTank::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}