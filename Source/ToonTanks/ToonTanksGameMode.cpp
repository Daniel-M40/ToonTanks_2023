// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
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
