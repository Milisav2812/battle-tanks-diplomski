#include "BasePawn.h"

#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"

ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create capsule collision
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	
	// Create Base Mesh and attach it to the Root Component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	// Create Turret Mesh and attach it to the Base Mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// Create Projectile Spawn Point and attach it to the Turret Mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
}

void ABasePawn::RotateTurret(FVector LookAtLocation) 
{
	FVector TargetVector = LookAtLocation - TurretMesh->GetComponentLocation();

	// Turret will only rotate in Yaw(Z Axis)
	FRotator TargetRotation = FRotator(0, TargetVector.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(TargetRotation);
}

void ABasePawn::Fire()
{

	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
		);

	// Important to have when destroying the Projectile
	SpawnedProjectile->SetOwner(this);

	if (ensure(SpawnedProjectile->GetLaunchSound()))
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			SpawnedProjectile->GetLaunchSound(),
			SpawnedProjectile->GetActorLocation()
		);
	}
}

void ABasePawn::HandleDestruction()
{
	// Destroy Visual Effects
	if (ensure(DeathParticles))
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			DeathParticles,
			RootComponent->GetRelativeTransform()
		);
	}

	// Camera Shake Effect
	if (ensure(PawnDeathCameraShake))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (ensure(PlayerController))
		{
			PlayerController->ClientStartCameraShake(PawnDeathCameraShake);
		}
	}

	// Destroy Sounds
	if (ensure(DestroySound))
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DestroySound,
			GetActorLocation()
		);
	}
	
}

USceneComponent* ABasePawn::GetProjectileSpawnPoint()
{
	return ProjectileSpawnPoint;
}

UStaticMeshComponent* ABasePawn::GetBaseMesh()
{
	return BaseMesh;
}


