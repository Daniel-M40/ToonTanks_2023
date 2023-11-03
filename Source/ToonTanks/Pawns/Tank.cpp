 // Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	PlayerInputComponent->BindAxis(mTurnAction, this, &ATank::Rotate);
	PlayerInputComponent->BindAxis(mCloseGame, this, &ATank::CloseGame);
	PlayerInputComponent->BindAction(mFireAction, IE_Pressed, this, &ATank::Fire);
 }


 void ATank::BeginPlay()
 {
	 Super::BeginPlay();

	 mPlayerController = Cast<APlayerController>(GetController());
 }


 // Called every frame
 void ATank::Tick(float DeltaTime)
 {
	 Super::Tick(DeltaTime);


	 if (mPlayerController)
	 {
		 const float SphereRadius = 25.f;
		 const int SphereSegments = 12;

		 FHitResult HitResult;

		 mPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		 if (mShowDebugSphere)
			 DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SphereRadius, SphereSegments, FColor::Red);

		RotateTurret(HitResult.ImpactPoint, mTurretRotationSpeed);

	}
 }

 void ATank::HandleDestruction()
 {
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
 	bAlive = false;
 }



 void ATank::Move(float value)
 {
	 //UE_LOG(LogTemp, Warning, TEXT("Move: %f"), value);

	 FVector DeltaLocation = FVector::ZeroVector;

	 DeltaLocation.X = (UGameplayStatics::GetWorldDeltaSeconds(this) * value * mMovementSpeed);

	 AddActorLocalOffset(DeltaLocation, true);
 }


 void ATank::Rotate(float value)
 {
	 FRotator DeltaRotation = FRotator::ZeroRotator;

	DeltaRotation.Yaw = (UGameplayStatics::GetWorldDeltaSeconds(this) * value * mRotationSpeed);

	AddActorLocalRotation(DeltaRotation, true);
 }

 void ATank::CloseGame(float value)
 {
 	FGenericPlatformMisc::RequestExit(false);
 }
