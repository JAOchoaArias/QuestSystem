#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/CppQuestTypes.h"
#include "CppQuestComponent.generated.h"

class UCppQuestDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCppQuestEvent, const FCppQuestRuntime&, QuestData);

UCLASS(ClassGroup = (Quests), meta = (BlueprintSpawnableComponent))
class QUESTSYSTEM_API UCppQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCppQuestComponent();
	
	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	TArray<FCppQuestRuntime> ActiveQuests;

	UPROPERTY(BlueprintAssignable, Category = "Quest|Events")
	FOnCppQuestEvent OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = "Quest|Events")
	FOnCppQuestEvent OnQuestProgressChanged;

	UPROPERTY(BlueprintAssignable, Category = "Quest|Events")
	FOnCppQuestEvent OnQuestCompleted;
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool FindQuestByID(FName QuestID, FCppQuestRuntime& OutQuestData, int32& OutQuestIndex) const;
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool AddQuest(UCppQuestDefinition* QuestDefinition);
	
	UFUNCTION()
	void HandleGameplayObjective(ECppQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);

protected:
	virtual void BeginPlay() override;

private:
	int32 FindQuestIndex(FName QuestID) const;
	void UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount);
	void CheckQuestCompleted(int32 QuestIndex);
};