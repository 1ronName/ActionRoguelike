// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

ASTeleportProjectile::ASTeleportProjectile()
{
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Explodes, this, &ASTeleportProjectile::Explodes_TimeElapsed, 0.2f);

	SphereComp->OnComponentHit.AddDynamic(this, &ASTeleportProjectile::OnActorHit);
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
}

void ASTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Explodes);
	Explodes_TimeElapsed();
}

void ASTeleportProjectile::Explodes_TimeElapsed()
{
	MovementComp->StopMovementImmediately();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplodeEffect,GetActorLocation(),GetActorRotation(),true);
	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ASTeleportProjectile::Teleport_TimeElapsed, 0.2f);

}

void ASTeleportProjectile::Teleport_TimeElapsed()
{
	AActor* MyActor = GetInstigator();
	MyActor->SetActorLocation(GetActorLocation());

	Destroy();
}
