// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Setting the Timer
	GetWorldTimerManager().SetTimer(
		FireTimerHandle, 
		this,								// The object for which this timer is called
		&ATower::CheckIfFireConditionIsMet, 
		FireRate, 
		true								// Do we want the timer to loop?
	);

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotating the Tower Turret
	if (CheckIfWithinRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}

}

void ATower::CheckIfFireConditionIsMet()
{
	if (CheckIfWithinRange() && PlayerTank->bIsPlayerAlive)
	{
		Fire();
	}
}

float ATower::CheckIfWithinRange()
{
	if (PlayerTank)
	{
		FVector PlayerLocation = PlayerTank->GetActorLocation();
		FVector TowerLocation = this->GetActorLocation();

		float Distance = FVector::Dist(TowerLocation, PlayerLocation);

		if (Distance <= FireDistance)
		{
			return true;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Tower Location: %f, %f, %f"), TowerLocation.X, TowerLocation.Y, TowerLocation.Z)
		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance)
	}

	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
