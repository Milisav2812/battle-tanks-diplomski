// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// Forward Includes
class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	virtual void Tick(float DeltaTime) override;

	USoundBase* GetLaunchSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Combat")
	float Damage = 100.f;

	// Bluepirnt Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UParticleSystemComponent* SmokeTrailComponent;

	// Called when Projectile hits something
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,	// The component doing the hitting - Projectile Mesh
		AActor* OtherActor,				// The Actor that got hit
		UPrimitiveComponent* OtherComp,	// The component that was hit (belongs to OtherActor)
		FVector NormalImpulse,			// The Physics engine will apply an impulse in response to the collision
		const FHitResult& Hit			// More info about the Hit
	);  

	// Sound & Visual Effects
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShake;
};
