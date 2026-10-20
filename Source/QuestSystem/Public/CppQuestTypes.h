#pragma once

#include "CoreMinimal.h"
#include "CppQuestTypes.generated.h"

class UCppQuestDefinition;

UENUM(BlueprintType)
enum class ECppQuestObjectiveType : uint8
{
	Kill,
	Collect,
	Interact,
	ReachLocation
};

USTRUCT(BlueprintType)
struct FCppQuestObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECppQuestObjectiveType ObjectiveType = ECppQuestObjectiveType::Kill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
	int32 RequiredAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount = 0;

	bool IsComplete() const { return CurrentAmount >= RequiredAmount; }
};

USTRUCT(BlueprintType)
struct FCppQuestRuntime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCppQuestDefinition> QuestDefinition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCppQuestObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCompleted = false;
};