// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:

	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//virtual void BeginPlay() override;

	//virtual void Tick(float DeltaSeconds) override;

private:

	void Move(float value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Config", meta = (DisplayName="Camera Component", AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Config", meta = (DisplayName = "Spring Arm Component", AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;


	const FName mMoveForwardAction = "MoveForward";


};
