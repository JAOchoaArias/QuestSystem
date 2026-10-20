#include "Public/Actors/CppObjectiveActor.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
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

bool ACppObjectiveActor::IsQuestPlayerBody(AActor* Actor, UPrimitiveComponent* Component) const
{
	const ACppQuestCharacter* Character = Cast<ACppQuestCharacter>(Actor);
	return Character && Component == Character->GetCapsuleComponent();
}

bool ACppObjectiveActor::IsQuestPlayer(const AActor* Actor) const
{
	return Actor && Actor->IsA<ACppQuestCharacter>();
}