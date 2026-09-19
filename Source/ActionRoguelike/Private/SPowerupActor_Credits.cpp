#include "SPowerupActor_Credits.h"
#include "SPlayerState.h"



ASPowerupActor_Credits::ASPowerupActor_Credits()
{

	CreditsAmount = 80;
}


void ASPowerupActor_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerup();
	}
}
