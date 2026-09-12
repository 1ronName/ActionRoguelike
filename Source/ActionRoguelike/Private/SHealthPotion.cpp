// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//Disable collision,instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	//check ifnot already atmax health
	if(ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		//Only activate if healed successfully
		if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
		{
			HideAndCooldownPowerup();
		}

	}
}

