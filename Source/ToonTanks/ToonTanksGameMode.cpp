// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	Tower = Cast<ATower>(DeadActor);

	if (Tank == DeadActor)
	{

		Tank->HandleDestruction();

		if (PlayerController)
		{
			PlayerController->SetPlayerEnableState(false);

		}

	}
	else if (Tower)
	{
		Tower->HandleDestruction();
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerController)
	{
		PlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;

		const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);

	}
}
