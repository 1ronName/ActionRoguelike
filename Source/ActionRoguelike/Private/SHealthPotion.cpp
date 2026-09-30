// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"
// 这样就可以用 LOCTEXT, 而不是 NSLOCTEXT 了。（少写一个参数

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

FText ASHealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		//return NSLOCTEXT("InteractableActors","HealthPotion_FullHealthWarning","Already at full health.");
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}
	
	return FText::Format(LOCTEXT("HealthPotion_InteractMessage","Cost {0} Credits. Restores health to maximum."), CreditCost);
}

#undef LOCTEXT_NAMESPACE
