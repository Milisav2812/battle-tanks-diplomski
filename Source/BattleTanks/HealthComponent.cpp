#include "HealthComponent.h"
#include "GameFramework/Controller.h"
#include "BattleTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	// Bind DamageTaken to the OnTakeAnyDamage of the Owner
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	// Declare the Game Mode
	BattleTanksGameMode = Cast<ABattleTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(
	AActor* DamagedActor,			
	float Damage,					
	const UDamageType* DamageType,	
	AController* Instagator,		
	AActor* DamageCauser			
)
{

	if (Damage > 0.f)
	{
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0.f && ensure(BattleTanksGameMode))
		{
			BattleTanksGameMode->ActorDied(DamagedActor);
		}
	}

}

