// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

// Forward Includes
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BATTLETANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera Components")
	USpringArmComponent* SpringArm;

	// Movement & Rotation Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float Speed = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float RotationSpeed = 80;

	void MoveForward(float Value);
	void Turn(float Value);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerController* PlayerController;

	// Used to implement Delay to Fire
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ReloadTime = 1.f;
	bool bCanFire = true;
	FTimerHandle FireTimerHandle;
	void ModifiedFireMechanic();
	void SetCanFireToTrue();
};
