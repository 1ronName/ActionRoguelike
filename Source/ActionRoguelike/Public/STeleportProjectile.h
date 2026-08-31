// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASProjectileBase
{
	GENERATED_BODY()
public:
	
	ASTeleportProjectile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* ExplodeEffect;

	FTimerHandle TimerHandle_Explodes;

	FTimerHandle TimerHandle_Teleport;

	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Explodes_TimeElapsed();

	void Teleport_TimeElapsed();

public:
	
	virtual void Tick(float DeltaTime) override;

};
