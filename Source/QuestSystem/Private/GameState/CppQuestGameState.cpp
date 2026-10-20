#include "Public/GameState/CppQuestGameState.h"

void ACppQuestGameState::ReportGameplayObjective(ECppQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	OnGameplayObjectiveEvent.Broadcast(ObjectiveType, TargetID, Amount);
}
