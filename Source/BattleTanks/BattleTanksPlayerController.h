// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTanksPlayerController.generated.h"

UCLASS()
class BATTLETANKS_API ABattleTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Enable/Disable Player input
	void SetPlayerEnabledState(bool bPlayerEnabled);

};
