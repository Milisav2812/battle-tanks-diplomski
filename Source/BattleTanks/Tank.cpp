// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"

// Constructor
ATank::ATank() 
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); 

	// Get the Player Controller and store it
	PlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate Turret towards Hit Object
	if (ensure(PlayerController)) {

		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		ABasePawn::RotateTurret(HitResult.ImpactPoint);
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind functionality to MoveForward Axis
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);

	// Bind functionality to Turn Axis
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::ModifiedFireMechanic);

}

void ATank::MoveForward(float Value) 
{
	FVector DeltaLocation(0);

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = Value * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) 
{
	FRotator DeltaRotation(0);

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * DeltaTime * RotationSpeed;
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::ModifiedFireMechanic()
{
	// Fire & Set Timer for ReloadTime
	if (bCanFire)
	{
		Fire();
		bCanFire = false;

		// Setting the Timer
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			this,								// The object for which this timer is called
			&ATank::SetCanFireToTrue,
			ReloadTime,
			false								// Do we want the timer to loop?
		);

	}
}

void ATank::SetCanFireToTrue()
{
	bCanFire = true;
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
}

APlayerController* ATank::GetPlayerController()
{
	return PlayerController;
}




