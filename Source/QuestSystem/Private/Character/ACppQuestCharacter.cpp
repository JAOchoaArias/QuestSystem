#include "Public/Character/ACppQuestCharacter.h"
#include "Public/Components/CppQuestComponent.h"
#include "Public/Widgets/CppQuestTrackerWidget.h"
#include "Public/Interfaces/CppInteractable.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "Public/Actors/CppEnemyDummy.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ACppQuestCharacter::ACppQuestCharacter()
{
	QuestComponent = CreateDefaultSubobject<UCppQuestComponent>(TEXT("QuestComponent"));

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(200.f);
	InteractionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	InteractionSphere->SetGenerateOverlapEvents(true);
}

void ACppQuestCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && QuestTrackerClass)
	{
		QuestTrackerWidget = CreateWidget<UCppQuestTrackerWidget>(PC, QuestTrackerClass);
		if (QuestTrackerWidget)
		{
			QuestTrackerWidget->AddToViewport();
			QuestTrackerWidget->InitTracker(QuestComponent);
		}
	}
}

void ACppQuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InteractAction)
		{
			EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &ACppQuestCharacter::TryInteract);
		}
		if (AttackAction)
		{
			EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &ACppQuestCharacter::TryAttack);
		}
	}
}

void ACppQuestCharacter::TryInteract()
{
	TArray<AActor*> OverlappingActors;
	InteractionSphere->GetOverlappingActors(OverlappingActors);

	AActor* Closest = nullptr;
	float ClosestDistSq = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		if (!IsValid(Actor) || !Actor->Implements<UCppInteractable>())
		{
			continue;
		}

		const float DistSq = FVector::DistSquared(Actor->GetActorLocation(), GetActorLocation());
		if (DistSq < ClosestDistSq)
		{
			ClosestDistSq = DistSq;
			Closest = Actor;
		}
	}

	if (Closest)
	{
		ICppInteractable::Execute_Interact(Closest, this);
	}
}
void ACppQuestCharacter::TryAttack()
{
	TArray<AActor*> NearbyEnemies;
	InteractionSphere->GetOverlappingActors(NearbyEnemies, ACppEnemyDummy::StaticClass());

	for (AActor* Enemy : NearbyEnemies)
	{
		UGameplayStatics::ApplyDamage(Enemy, AttackDamage, GetController(), this, UDamageType::StaticClass());
	}
}