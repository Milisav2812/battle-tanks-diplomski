// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"

#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank) 
	{
		FVector PlayerLocation = PlayerTank->GetActorLocation();
		FVector TowerLocation = this->GetActorLocation();
		
		float Distance = FVector::Dist(TowerLocation, PlayerLocation);
		
		//UE_LOG(LogTemp, Warning, TEXT("Tower Location: %f, %f, %f"), TowerLocation.X, TowerLocation.Y, TowerLocation.Z)
		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance)

		if (Distance <= FireDistance)
		{
			RotateTurret(PlayerLocation);
		}
	}
	
}
