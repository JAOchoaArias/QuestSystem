#pragma once

#include "CoreMinimal.h"
#include "QuestSystemCharacter.h"
#include "ACppQuestCharacter.generated.h"

class UCppQuestComponent;
class UCppQuestTrackerWidget;
class USphereComponent;
class UInputAction;

UCLASS()
class QUESTSYSTEM_API ACppQuestCharacter : public AQuestSystemCharacter 
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	float AttackDamage = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|UI")
	TSubclassOf<UCppQuestTrackerWidget> QuestTrackerClass;

private:
	void TryInteract();
	void TryAttack();

	UPROPERTY()
	TObjectPtr<UCppQuestTrackerWidget> QuestTrackerWidget;
};