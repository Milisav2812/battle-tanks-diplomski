 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AController;
class ABattleTanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	UFUNCTION()
	void DamageTaken(
		AActor* DamagedActor,			// The Actor taking the damage
		float Damage,					// The Damage amount
		const UDamageType* DamageType,	// Do something based on the kind of damage(fire, poison, etc.)
		AController* Instagator,		// The controller responsible for the damage
		AActor* DamageCauser			// Actor causing the damage
	);

	ABattleTanksGameMode* BattleTanksGameMode;

		
};
