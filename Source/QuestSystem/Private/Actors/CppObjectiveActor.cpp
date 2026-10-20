#include "Public/Actors/CppObjectiveActor.h"
#include "Engine/World.h"
#include "Public/Character/ACppQuestCharacter.h"
#include "Public/GameState/CppQuestGameState.h"

DEFINE_LOG_CATEGORY_STATIC(LogCppObjectiveActor, Log, All);

ACppObjectiveActor::ACppObjectiveActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ACppObjectiveActor::ReportObjective()
{
	UWorld* World = GetWorld();
	ACppQuestGameState* QuestGameState = World ? World->GetGameState<ACppQuestGameState>() : nullptr;

	if (!QuestGameState)
	{
		UE_LOG(LogCppObjectiveActor, Warning, TEXT("%s: el GameState no es ACppQuestGameState"), *GetName());
		return false;
	}

	QuestGameState->ReportGameplayObjective(ObjectiveType, TargetID, Amount);
	return true;
}

bool ACppObjectiveActor::IsQuestPlayer(const AActor* Actor) const
{
	return Actor && Actor->IsA<ACppQuestCharacter>();
}