// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	Tower = Cast<ATower>(DeadActor);

	if (Tank == DeadActor)
	{
		APlayerController* TankPlayerController = Tank->GetPlayerController();

		Tank->HandleDestruction();

		if (TankPlayerController)
		{
			Tank->DisableInput(TankPlayerController);
			TankPlayerController->bShowMouseCursor = false;

			Tank->SetPlayerController(TankPlayerController);
		}

	}
	else if (Tower)
	{
		Tower->HandleDestruction();
	}
}
