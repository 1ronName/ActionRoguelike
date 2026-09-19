#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerupActor_Credits.generated.h"

class UStaticMeshComponent;

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor_Credits : public ASPowerupActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsAmount;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASPowerupActor_Credits();
};