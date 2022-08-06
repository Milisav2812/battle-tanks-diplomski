// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")); 
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnHit to the Delegate
	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComp,	
	AActor* OtherActor,				
	UPrimitiveComponent* OtherComp,	
	FVector NormalImpulse,			
	const FHitResult& Hit			
)
{

	UE_LOG(LogTemp, Warning, TEXT("HitComp Name: %s"), *HitComp->GetName())
	UE_LOG(LogTemp, Warning, TEXT("OtherActor Name: %s"), *OtherActor->GetName())
	UE_LOG(LogTemp, Warning, TEXT("OtherComp Name: %s"), *OtherComp->GetName())

}

