// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = mProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = mInitialSpeed;
		ProjectileMovement->MaxSpeed = mMaxSpeed;
	}

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail particles"));
	TrailParticles->SetupAttachment(mProjectileMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	mProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	const AActor* CurrentOwner = GetOwner();

	if (!CurrentOwner)
	{
		Destroy();
		return;
	}

	AController* CurrentInstigator = CurrentOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	//If the actor is not it self apply damage
	if (OtherActor && OtherActor != this && OtherActor != CurrentOwner)
	{
		//Apply damage to the actor hit
		UGameplayStatics::ApplyDamage(OtherActor, Damage, CurrentInstigator, this, DamageTypeClass);

		if (HitParticles)
		{
			//Spawn hit particles at the location and rotation
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	//destroy the actor anyway
	Destroy();
	

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

