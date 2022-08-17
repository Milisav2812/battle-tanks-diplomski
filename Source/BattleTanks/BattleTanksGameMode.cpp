// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "EnemyTank.h"
#include "BattleTanksPlayerController.h"
#include "EnemyCharacterTank.h"

// Called when the game starts or when spawned
void ABattleTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleStartGame();
	
}

void ABattleTanksGameMode::ActorDied(AActor* ActorThatDied)
{
	// Check if the dead actor is the player tank
	if (ActorThatDied == PlayerTank)
	{
		PlayerTank->HandleDestruction();

		// Verify that the controller is not NULL
		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}
		
		// End the game
		GameOver(false);
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(ActorThatDied)) // Try to cast to Tower
	{
		DestroyedTower->HandleDestruction();
		TowersLeft--;
		if (TowersLeft == 0)
		{
			GameOver(true);
		}
	}
	else if (AEnemyCharacterTank* DestroyedEnemy = Cast<AEnemyCharacterTank>(ActorThatDied)) // Try to cast to Tower
	{
		DestroyedEnemy->HandleDestruction();
	}
}

void ABattleTanksGameMode::HandleStartGame()
{
	// Initialize number of towers
	TowersLeft = CalculateNumberOfTowers();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<ABattleTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);

		// Setting up a timer to countdown 3 seconds before player can move
		FTimerHandle StartTimerHandle;
		FTimerDelegate StartTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &ABattleTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(StartTimerHandle, StartTimerDelegate, TimeBeforeStart, false);
	}
}

int32 ABattleTanksGameMode::CalculateNumberOfTowers()
{
	TArray<AActor*> ArrayOfTowers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), ArrayOfTowers);

	return ArrayOfTowers.Num();
}

ATank* ABattleTanksGameMode::getPlayerTank()
{
	return PlayerTank;
}