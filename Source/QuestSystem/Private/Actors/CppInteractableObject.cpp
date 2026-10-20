#include "Public/Actors/CppInteractableObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

ACppInteractableObject::ACppInteractableObject()
{
	ObjectiveType = ECppQuestObjectiveType::Interact;

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
		Mesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.8f));
	}
}

void ACppInteractableObject::Interact_Implementation(AActor* Interactor)
{
	if (!IsQuestPlayer(Interactor))
	{
		return;
	}

	if (ReportObjective() && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan,
			FString::Printf(TEXT("Interactuaste con %s"), *TargetID.ToString()));
	}
}