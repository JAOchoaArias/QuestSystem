#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Interfaces/CppInteractable.h"
#include "CppQuestGiver.generated.h"

class UCppQuestDefinition;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class QUESTSYSTEM_API ACppQuestGiver : public AActor, public ICppInteractable
{
	GENERATED_BODY()

public:
	ACppQuestGiver();

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<USphereComponent> InteractionVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UCppQuestDefinition> QuestDefinition;
};