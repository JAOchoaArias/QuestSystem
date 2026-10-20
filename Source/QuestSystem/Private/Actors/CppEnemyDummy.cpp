#include "Public/Actors/CppEnemyDummy.h"
#include "Public/Widgets/CppEnemyHealthBarWidget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMesh.h"

DEFINE_LOG_CATEGORY_STATIC(LogCppEnemy, Log, All);

ACppEnemyDummy::ACppEnemyDummy()
{
	ObjectiveType = ECppQuestObjectiveType::Kill;

	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	HitSphere->InitSphereRadius(60.f);
	HitSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HitSphere->SetGenerateOverlapEvents(true);
	RootComponent = HitSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CylinderMesh.Object);
		Mesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 1.2f));
	}
	
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetDrawSize(FVector2D(100.f, 12.f));
	HealthBarComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthBarComponent->SetVisibility(false); 
}

void ACppEnemyDummy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (!HealthBarWidgetClass)
	{
		UE_LOG(LogCppEnemy, Warning, TEXT("%s: HealthBarWidgetClass no asignado, no habra barra de vida"), *GetName());
		return;
	}

	HealthBarComponent->SetWidgetClass(HealthBarWidgetClass);
	if (!HealthBarComponent->GetUserWidgetObject())
	{
		HealthBarComponent->InitWidget();
	}

	HealthBarWidget = Cast<UCppEnemyHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.f);
	}
}

float ACppEnemyDummy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead || !IsQuestPlayer(DamageCauser))
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}

	CurrentHealth = FMath::Max(CurrentHealth - ActualDamage, 0.f);
	UpdateHealthBar();

	if (CurrentHealth <= 0.f)
	{
		bIsDead = true;

		if (!ReportObjective())
		{
			bIsDead = false;
			CurrentHealth = MaxHealth;
			UpdateHealthBar();
			return ActualDamage;
		}

		Destroy();
	}

	return ActualDamage;
}

void ACppEnemyDummy::UpdateHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarComponent->SetVisibility(true);
		HealthBarWidget->SetHealthPercent(CurrentHealth / MaxHealth);
	}
}