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

	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();


	APlayerController* GetPlayerController() const	{ return mPlayerController;	}
	void SetPlayerController(APlayerController* PlayerController) { mPlayerController = PlayerController; }

protected:
	virtual void BeginPlay() override;

	

private:

	//Moves the tank forward and backwards
	void Move(float value);

	//Rotates the tank left and right
	void Rotate(float value);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Config", meta = (DisplayName="Camera Component", AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Config", meta = (DisplayName = "Spring Arm Component", AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;


	//Movement speed of the tank
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (DisplayName = "Movement Speed", AllowPrivateAccess = "true"))
		float mMovementSpeed = 400.f;

	//Rotation when turning round
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (DisplayName = "Rotation Speed", AllowPrivateAccess = "true"))
		float mRotationSpeed = 200.f;

	//Turrer rotation when using the mouse
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (DisplayName = "Turret Rotation Speed", AllowPrivateAccess = "true"))
		float mTurretRotationSpeed = 10.f;


	const FName mMoveForwardAction = "MoveForward";
	const FName mTurnAction = "Turn";
	const FName mFireAction = "Fire";
	
	APlayerController* mPlayerController;

public:
	bool bAlive = true;
};
