// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{

	CreditCost = 50;
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
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
			{
				HideAndCooldownPowerup();
			}
		}

	}
}

