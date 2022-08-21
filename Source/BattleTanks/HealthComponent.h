#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Forward Includes
class AController;
class ABattleTanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Health Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MaxHealth = 100.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float CurrentHealth = 0.f;

	// Called when Event ApplyDamage ticks (ApplyDamage is called by Projectile when it hits something)
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
