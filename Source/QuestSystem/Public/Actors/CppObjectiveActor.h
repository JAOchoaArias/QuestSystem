#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/CppQuestTypes.h"
#include "CppObjectiveActor.generated.h"

UCLASS(Abstract)
class QUESTSYSTEM_API ACppObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	ACppObjectiveActor();

protected:
	
	bool ReportObjective();
	
	bool IsQuestPlayerBody(AActor* Actor, UPrimitiveComponent* Component) const;

	bool IsQuestPlayer(const AActor* Actor) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Objective")
	ECppQuestObjectiveType ObjectiveType = ECppQuestObjectiveType::Collect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Objective")
	FName TargetID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Objective", meta = (ClampMin = "1"))
	int32 Amount = 1;
};