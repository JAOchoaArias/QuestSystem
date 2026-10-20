#include "Public/Actors/CppReachLocationTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

ACppReachLocationTrigger::ACppReachLocationTrigger()
{
	ObjectiveType = ECppQuestObjectiveType::ReachLocation;

	ZoneBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBox"));
	ZoneBox->InitBoxExtent(FVector(150.f, 150.f, 100.f));
	ZoneBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ZoneBox->SetGenerateOverlapEvents(true);
	RootComponent = ZoneBox;

	Marker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker"));
	Marker->SetupAttachment(RootComponent);
	Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		Marker->SetStaticMesh(CylinderMesh.Object);
		Marker->SetRelativeScale3D(FVector(3.f, 3.f, 0.05f));
	}
}

void ACppReachLocationTrigger::BeginPlay()
{
	Super::BeginPlay();
	ZoneBox->OnComponentBeginOverlap.AddDynamic(this, &ACppReachLocationTrigger::OnZoneOverlap);
}

void ACppReachLocationTrigger::OnZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((bTriggerOnce && bTriggered) || !IsQuestPlayerBody(OtherActor, OtherComp))
	{
		return;
	}

	if (ReportObjective())
	{
		bTriggered = true;
	}
}