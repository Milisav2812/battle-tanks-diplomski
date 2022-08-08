// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanksPlayerController.h"

void ABattleTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{

	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	// Show/Hide mouse cursor
	bShowMouseCursor = bPlayerEnabled;

}
