// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Damage")
	float Damage = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Damage")
	UParticleSystemComponent* SmokeTrailComponent;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,	// The component doing the hitting - Projectile Mesh
		AActor* OtherActor,				// The Actor that got hit
		UPrimitiveComponent* OtherComp,	// The component that was hit (belongs to OtherActor)
		FVector NormalImpulse,			// The Physics engine will apply an impulse in response to the collision
		const FHitResult& Hit			// More info about the Hit
	);  

	UPROPERTY(EditAnywhere, Category = "Damage")
	UParticleSystem* HitParticles;


};
