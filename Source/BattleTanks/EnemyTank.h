// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTank.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API AEnemyTank : public ABasePawn
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
	// Movement Speed & Rotation Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float Speed = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float RotationSpeed = 100;

	// Fire Distance 
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireDistance = 1000;
	float CheckIfWithinRange();

	ATank* PlayerTank;

	// Timer and Fire functionality
	FTimerHandle FireTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;
	void CheckIfFireConditionIsMet();
};
