#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CppInteractable.generated.h"

UINTERFACE(BlueprintType)
class QUESTSYSTEM_API UCppInteractable : public UInterface
{
	GENERATED_BODY()
};

class QUESTSYSTEM_API ICppInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};