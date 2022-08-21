// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMeshComponent;

	SmokeTrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail Component"));
	SmokeTrailComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")); 
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
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
	auto MyOwner = GetOwner();
	if (!ensure(MyOwner))
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Owner is NULL"))
		Destroy();
		return;
	}
	AController* EventInstigator = MyOwner->GetInstigatorController();

	// Getting UClass from UDamageType
	static UClass* DamageTypeClass = UDamageType::StaticClass();

	// Do not deal damage IF
		// The Actor that was hit is NULL
		// The Actor that was hit is the Actor that fired the projectile
		// The Projectile hits itself
	if (ensure(OtherActor) && OtherActor != this && OtherActor != MyOwner)
	{
		// Will call HealthComponent DamageTaken function
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			EventInstigator,
			this,
			DamageTypeClass 
		);

		// Play Sound
		if (ensure(HitSound))
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation()
			);
		}

		// Shake the camera
		if (ensure(HitCameraShake))
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (ensure(PlayerController))
			{
				PlayerController->ClientStartCameraShake(HitCameraShake);
			}
		}

	}

	// Spawn Particle System
	if (ensure(HitParticles))
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ProjectileMeshComponent->GetRelativeTransform()
		);
	}

	Destroy();
}

USoundBase* AProjectile::GetLaunchSound()
{
	return LaunchSound;
}

