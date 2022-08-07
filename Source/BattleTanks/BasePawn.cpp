// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"

#include "Components/CapsuleComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// Vector that has a starting position in the tank turret and an end position at our mouse cursor
	FVector TargetVector = LookAtLocation - TurretMesh->GetComponentLocation();

	// Turret will only rotate in Yaw 
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

	SpawnedProjectile->SetOwner(this);

	// Draw Debug Sphere
	/*DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		20,
		12,
		FColor::Red,
		false,
		3.f
	);*/

}

void ABasePawn::HandleDestruction()
{
	// Visual / Sound Effects go here


}



