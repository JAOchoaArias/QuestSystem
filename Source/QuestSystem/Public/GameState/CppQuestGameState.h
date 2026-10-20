#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Public/CppQuestDefinition.h"
#include "CppQuestGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnCppGameplayObjectiveEvent,
	ECppQuestObjectiveType, ObjectiveType,
	FName, TargetID,
	int32, Amount);


UCLASS()
class QUESTSYSTEM_API ACppQuestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Quest|Events")
	FOnCppGameplayObjectiveEvent OnGameplayObjectiveEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ReportGameplayObjective(ECppQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);
};