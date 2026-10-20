#pragma once

#include "CoreMinimal.h"
#include "CppObjectiveActor.h"
#include "Public/Interfaces/CppInteractable.h"
#include "CppInteractableObject.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class QUESTSYSTEM_API ACppInteractableObject : public ACppObjectiveActor, public ICppInteractable
{
	GENERATED_BODY()

public:
	ACppInteractableObject();

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<USphereComponent> InteractionVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UStaticMeshComponent> Mesh;
};