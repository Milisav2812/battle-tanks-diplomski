// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleTanksGameMode.generated.h"

class ATank;
class ABattleTanksPlayerController;

UCLASS()
class BATTLETANKS_API ABattleTanksGameMode : public AGameModeBase
{
	GENERATED_BODY() 

public:
	void ActorDied(AActor* ActorThatDied);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon);

private:
	ATank* PlayerTank;
	ABattleTanksPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = "Start Timer")
	float TimeBeforeStart = 3.f;

	void HandleStartGame();

	int32 CalculateNumberOfTowers();
	int32 TowersLeft = 0;

};
