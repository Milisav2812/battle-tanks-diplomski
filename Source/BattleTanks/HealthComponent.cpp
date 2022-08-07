// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	// Bind DamageTaken to the OnTakeAnyDamage of the Owner
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(
	AActor* DamagedActor,			
	float Damage,					
	const UDamageType* DamageType,	
	AController* Instagator,		
	AActor* DamageCauser			
)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Actor %s took damage %f"), *GetOwner()->GetName(), Damage)*/

	if (Damage > 0.f)
	{
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0.f && this->GetOwner())
		{
			// Destroy the Healt Component Owner (Tank, Turret)
			this->GetOwner()->Destroy();
		}
	}

}

