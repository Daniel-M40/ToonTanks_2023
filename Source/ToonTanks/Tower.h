// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;


protected:
	virtual void BeginPlay() override;


private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Range", AllowPrivateAccess = "true"))
		float mFireRange = 10.f;

	UPROPERTY(EditAnywhere, Category = "Tower Config", meta = (DisplayName = "Turret Rotation Speed", AllowPrivateAccess = "true"))
		float mTurretRotationSpeed = 10.f;

	FTimerHandle TimerHandle;
	float FireRate = 2.f;

	void CheckFireCondition();

	bool IsActorInRange(const FVector& Actor);


};
