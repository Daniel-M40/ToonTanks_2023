// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (DisplayName = "Projectile Mesh", AllowPrivateAccess = true))
		UStaticMeshComponent* mProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (DisplayName = "Initial Speed", AllowPrivateAccess = true))
		float mInitialSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (DisplayName = "Max Speed", AllowPrivateAccess = true))
		float mMaxSpeed = 1300.f;


	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (DisplayName = "Projectile Mesh"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
