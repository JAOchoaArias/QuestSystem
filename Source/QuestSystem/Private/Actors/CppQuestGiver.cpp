#include "Public/Actors/CppQuestGiver.h"
#include "Public/Components/CppQuestComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

DEFINE_LOG_CATEGORY_STATIC(LogCppQuestGiver, Log, All);

ACppQuestGiver::ACppQuestGiver()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionVolume"));
	InteractionVolume->InitSphereRadius(80.f);
	InteractionVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	InteractionVolume->SetGenerateOverlapEvents(true);
	RootComponent = InteractionVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
		Mesh->SetRelativeScale3D(FVector(0.6f));
	}
}

void ACppQuestGiver::Interact_Implementation(AActor* Interactor)
{
	if (!IsValid(Interactor))
	{
		return;
	}

	UCppQuestComponent* QuestComp = Interactor->FindComponentByClass<UCppQuestComponent>();
	if (!QuestComp)
	{
		UE_LOG(LogCppQuestGiver, Warning, TEXT("El Interactor no tiene UCppQuestComponent"));
		return;
	}
	QuestComp->AddQuest(QuestDefinition);
}