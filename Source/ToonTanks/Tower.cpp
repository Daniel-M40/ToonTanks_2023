// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		const FVector tankCurrentLocation = Tank->GetActorLocation();

		if (IsActorInRange(tankCurrentLocation))
		{
			//Rotate the turret to the tank
			RotateTurret(tankCurrentLocation, mTurretRotationSpeed);
		}
	}




}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank)
	{
		const FVector tankCurrentLocation = Tank->GetActorLocation();


		if (IsActorInRange(tankCurrentLocation))
		{
			//Rotate the turret to the tank
			Fire();
		}
	}
}

bool ATower::IsActorInRange(const FVector& ActorLocation)
{
	const FVector towerCurrentLocation = GetActorLocation();

	//Find the distance of the tank
	const float Distance = FVector::Dist(towerCurrentLocation, ActorLocation);

	//Check if the tank is in range
	return Distance <= mFireRange;
}
