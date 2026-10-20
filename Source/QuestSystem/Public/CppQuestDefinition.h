#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CppQuestTypes.h"
#include "CppQuestDefinition.generated.h"

UCLASS(BlueprintType)
class QUESTSYSTEM_API UCppQuestDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest", meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FCppQuestObjective> Objectives;
};