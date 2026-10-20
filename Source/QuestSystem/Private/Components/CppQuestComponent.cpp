#include "Public/Components/CppQuestComponent.h"
#include "Public/GameState/CppQuestGameState.h"
#include "Engine/World.h"
#include "Public/CppQuestDefinition.h"

DEFINE_LOG_CATEGORY_STATIC(LogCppQuest, Log, All);

UCppQuestComponent::UCppQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCppQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		if (ACppQuestGameState* QuestGameState = World->GetGameState<ACppQuestGameState>())
		{
			QuestGameState->OnGameplayObjectiveEvent.AddUniqueDynamic(this, &UCppQuestComponent::HandleGameplayObjective);
		}
		else
		{
			UE_LOG(LogCppQuest, Warning, TEXT("El GameState no es ACppQuestGameState: revisar el GameMode del mapa"));
		}
	}
}

void UCppQuestComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (ACppQuestGameState* QuestGameState = World->GetGameState<ACppQuestGameState>())
		{
			QuestGameState->OnGameplayObjectiveEvent.RemoveDynamic(this, &UCppQuestComponent::HandleGameplayObjective);
		}
	}

	Super::EndPlay(EndPlayReason);
}

int32 UCppQuestComponent::FindQuestIndex(FName QuestID) const
{
	return ActiveQuests.IndexOfByPredicate([QuestID](const FCppQuestRuntime& Quest)
	{
		return Quest.QuestID == QuestID;
	});
}

bool UCppQuestComponent::FindQuestByID(FName QuestID, FCppQuestRuntime& OutQuestData, int32& OutQuestIndex) const
{
	OutQuestIndex = FindQuestIndex(QuestID);
	if (OutQuestIndex == INDEX_NONE)
	{
		OutQuestData = FCppQuestRuntime();
		return false;
	}

	OutQuestData = ActiveQuests[OutQuestIndex];
	return true;
}

bool UCppQuestComponent::AddQuest(UCppQuestDefinition* QuestDefinition)
{
	if (!IsValid(QuestDefinition) || QuestDefinition->QuestID.IsNone())
	{
		UE_LOG(LogCppQuest, Warning, TEXT("AddQuest: definicion invalida o sin QuestID"));
		return false;
	}

	if (FindQuestIndex(QuestDefinition->QuestID) != INDEX_NONE)
	{
		UE_LOG(LogCppQuest, Log, TEXT("AddQuest: la mision %s ya existe"), *QuestDefinition->QuestID.ToString());
		return false;
	}

	FCppQuestRuntime NewQuest;
	NewQuest.QuestID = QuestDefinition->QuestID;
	NewQuest.QuestDefinition = QuestDefinition;
	NewQuest.Objectives = QuestDefinition->Objectives; // copia: el Data Asset no se modifica
	NewQuest.bIsActive = true;
	NewQuest.bIsCompleted = false;

	for (FCppQuestObjective& Objective : NewQuest.Objectives)
	{
		Objective.CurrentAmount = 0;
	}

	ActiveQuests.Add(NewQuest);
	OnQuestStarted.Broadcast(NewQuest);
	return true;
}

void UCppQuestComponent::HandleGameplayObjective(ECppQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	for (int32 QuestIndex = 0; QuestIndex < ActiveQuests.Num(); ++QuestIndex)
	{
		if (!ActiveQuests[QuestIndex].bIsActive || ActiveQuests[QuestIndex].bIsCompleted)
		{
			continue;
		}

		const int32 ObjectiveCount = ActiveQuests[QuestIndex].Objectives.Num();
		for (int32 ObjectiveIndex = 0; ObjectiveIndex < ObjectiveCount; ++ObjectiveIndex)
		{
			const FCppQuestObjective& Objective = ActiveQuests[QuestIndex].Objectives[ObjectiveIndex];

			if (Objective.ObjectiveType == ObjectiveType && Objective.TargetID == TargetID && !Objective.IsComplete())
			{
				UpdateObjectiveProgress(QuestIndex, ObjectiveIndex, Amount);
			}
		}
	}
}

void UCppQuestComponent::UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount)
{
	if (Amount <= 0 || !ActiveQuests.IsValidIndex(QuestIndex))
	{
		return;
	}

	FCppQuestRuntime& Quest = ActiveQuests[QuestIndex];
	if (!Quest.Objectives.IsValidIndex(ObjectiveIndex))
	{
		return;
	}

	FCppQuestObjective& Objective = Quest.Objectives[ObjectiveIndex];
	Objective.CurrentAmount = FMath::Min(Objective.CurrentAmount + Amount, Objective.RequiredAmount);

	CheckQuestCompleted(QuestIndex);
}

void UCppQuestComponent::CheckQuestCompleted(int32 QuestIndex)
{
	if (!ActiveQuests.IsValidIndex(QuestIndex))
	{
		return;
	}

	FCppQuestRuntime& Quest = ActiveQuests[QuestIndex];

	bool bAllCompleted = true;
	for (const FCppQuestObjective& Objective : Quest.Objectives)
	{
		if (!Objective.IsComplete())
		{
			bAllCompleted = false;
			break;
		}
	}

	if (bAllCompleted)
	{
		Quest.bIsCompleted = true;
		Quest.bIsActive = false;
	}
	
	const FCppQuestRuntime QuestSnapshot = Quest;

	OnQuestProgressChanged.Broadcast(QuestSnapshot);
	if (bAllCompleted)
	{
		OnQuestCompleted.Broadcast(QuestSnapshot);
	}
}