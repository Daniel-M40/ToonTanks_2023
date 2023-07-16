 // Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

 ATank::ATank()
{
	 SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	 SpringArmComp->SetupAttachment(RootComponent);

	 CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	 CameraComp->SetupAttachment(SpringArmComp);

}

 void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
 {
	 Super::SetupPlayerInputComponent(PlayerInputComponent);

	 PlayerInputComponent->BindAxis(mMoveForwardAction, this, &ATank::Move);
 }

 void ATank::Move(float value)
 {
	 UE_LOG(LogTemp, Warning, TEXT("Move: %f"), value);
 }
