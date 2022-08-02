// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Constructor
ATank::ATank() 
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind functionality to MoveForward Axis
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);

	// Bind functionality to Turn Axis
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

}

void ATank::MoveForward(float Value) {
	//UE_LOG(LogTemp, Warning, TEXT("MoveForward Axis Value: %f"), Value)

	FVector DeltaLocation(0);

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = Value * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) {
	//UE_LOG(LogTemp, Warning, TEXT("MoveForward Axis Value: %f"), Value)

	FRotator DeltaRotation(0);

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * DeltaTime * RotationSpeed;
	AddActorLocalRotation(DeltaRotation, true);
}



