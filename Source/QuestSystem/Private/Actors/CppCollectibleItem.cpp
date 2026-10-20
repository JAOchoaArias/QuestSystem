#include "Public/Actors/CppCollectibleItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

ACppCollectibleItem::ACppCollectibleItem()
{
	ObjectiveType = ECppQuestObjectiveType::Collect;

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->InitSphereRadius(60.f);
	PickupSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	PickupSphere->SetGenerateOverlapEvents(true);
	RootComponent = PickupSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
		Mesh->SetRelativeScale3D(FVector(0.4f));
	}
}

void ACppCollectibleItem::BeginPlay()
{
	Super::BeginPlay();
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &ACppCollectibleItem::OnPickupOverlap);
}

void ACppCollectibleItem::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCollected || !IsQuestPlayerBody(OtherActor, OtherComp))
	{
		return;
	}
	
	bCollected = true;

	if (!ReportObjective())
	{
		bCollected = false;
		return;
	}

	Destroy();
}