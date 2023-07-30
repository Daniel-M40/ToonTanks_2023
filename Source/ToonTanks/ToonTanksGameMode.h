// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;


public:

	void ActorDied(AActor* DeadActor);

	class ATank* Tank;

	class AToonTanksPlayerController* PlayerController;

	class ATower* Tower;
};
