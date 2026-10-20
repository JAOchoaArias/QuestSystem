#pragma once

#include "CoreMinimal.h"
#include "QuestSystemCharacter.h" // <- ajustar
#include "ACppQuestCharacter.generated.h"

class UCppQuestComponent;
class UCppQuestTrackerWidget;
class USphereComponent;
class UInputAction;

UCLASS()
class QUESTSYSTEM_API ACppQuestCharacter : public AQuestSystemCharacter // <- ajustar
{
	GENERATED_BODY()

public:
	ACppQuestCharacter();

	UCppQuestComponent* GetQuestComponent() const { return QuestComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UCppQuestComponent> QuestComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<USphereComponent> InteractionSphere;

	/** Se asigna en el Blueprint hijo (IA_Interact) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	/** Se asigna en el Blueprint hijo (WBP_QuestTrackerCPP) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|UI")
	TSubclassOf<UCppQuestTrackerWidget> QuestTrackerClass;

private:
	void TryInteract();

	UPROPERTY()
	TObjectPtr<UCppQuestTrackerWidget> QuestTrackerWidget;
};