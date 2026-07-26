#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APlayerCharacter;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ROGUELITE_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(APlayerCharacter* PlayerInteractor) = 0;
};
