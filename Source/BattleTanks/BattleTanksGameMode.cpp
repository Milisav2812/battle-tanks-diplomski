// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

// Called when the game starts or when spawned
void ABattleTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void ABattleTanksGameMode::ActorDied(AActor* ActorThatDied)
{
	// Check if the dead actor is the player tank
	if (ActorThatDied == PlayerTank)
	{
		PlayerTank->HandleDestruction();

		// Verify that the controller is not NULL
		if (PlayerTank->GetPlayerController())
		{
			PlayerTank->DisableInput(PlayerTank->GetPlayerController());

			// Disable mouse cursor
			PlayerTank->GetPlayerController()->bShowMouseCursor = false;
		}
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(ActorThatDied)) // Try to cast to Tower
	{
		DestroyedTower->HandleDestruction();
	}
}