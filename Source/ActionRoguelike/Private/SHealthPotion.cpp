// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetVisibility(true);

	ColdTime = 10.f;
	bIsTriggered = false;
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASHealthPotion::Cold_TimeElapsed()
{
	bIsTriggered = false;
	StaticMesh->SetVisibility(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp && AttributeComp->GetHealth() < AttributeComp->GetHealthMax())
		{
			AttributeComp->ApplyHealthChange(AttributeComp->GetHealthMax());

			StaticMesh->SetVisibility(false);
			bIsTriggered = true;
			
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			
			FTimerHandle TimerHandle_Cold;
			GetWorldTimerManager().SetTimer(TimerHandle_Cold, this, &ASHealthPotion::Cold_TimeElapsed, ColdTime);
		}
	}
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

