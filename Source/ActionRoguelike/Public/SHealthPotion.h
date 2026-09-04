// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.h"
#include "SHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
	
public:	

	ASHealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

};
