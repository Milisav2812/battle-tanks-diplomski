// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleTanksGameMode.generated.h"

// Forward Includes
class ATank;
class ABattleTanksPlayerController;

UCLASS()
class BATTLETANKS_API ABattleTanksGameMode : public AGameModeBase
{
	GENERATED_BODY() 

public:
	// Called when an Actor gets Destroyed
	void ActorDied(AActor* ActorThatDied);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Blueprint Callable Events
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon);

private:
	// Player Tank Reference
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ATank* PlayerTank;

	// Player Controller Reference
	ABattleTanksPlayerController* PlayerController;

	// Properties for Game Rules
	UPROPERTY(EditAnywhere, Category = "Gameplay Options")
	float TimeBeforeStart = 3.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 TowersLeft = 0;

	void HandleStartGame();
	int32 CalculateNumberOfTowers();
};
