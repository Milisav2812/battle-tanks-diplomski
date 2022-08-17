// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
class ABattleTanksGameMode;

UCLASS()
class BATTLETANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireDistance = 1000;

	float CheckIfWithinRange();

	ATank* PlayerTank;

	ABattleTanksGameMode* GameMode;

	// Timer and Fire functionality
	FTimerHandle FireTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;
	void CheckIfFireConditionIsMet();
	
};
