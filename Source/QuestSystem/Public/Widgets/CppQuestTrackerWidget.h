#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Public/CppQuestTypes.h"
#include "CppQuestTrackerWidget.generated.h"

class UCppQuestComponent;
class UVerticalBox;

UCLASS()
class QUESTSYSTEM_API UCppQuestTrackerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Quest|UI")
	void InitTracker(UCppQuestComponent* InQuestComponent);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> QuestList;

	UFUNCTION()
	void HandleQuestEvent(const FCppQuestRuntime& QuestData);

private:
	void RefreshQuests();

	TWeakObjectPtr<UCppQuestComponent> QuestComponent;
};