#include "Public/Widgets/CppQuestTrackerWidget.h"
#include "Public/Components/CppQuestComponent.h"
#include "public/CppQuestDefinition.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UCppQuestTrackerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCppQuestTrackerWidget::NativeDestruct()
{
	if (UCppQuestComponent* Comp = QuestComponent.Get())
	{
		Comp->OnQuestStarted.RemoveDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);
		Comp->OnQuestProgressChanged.RemoveDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);
		Comp->OnQuestCompleted.RemoveDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);
	}

	Super::NativeDestruct();
}

void UCppQuestTrackerWidget::InitTracker(UCppQuestComponent* InQuestComponent)
{
	if (!IsValid(InQuestComponent))
	{
		return;
	}

	QuestComponent = InQuestComponent;

	InQuestComponent->OnQuestStarted.AddUniqueDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);
	InQuestComponent->OnQuestProgressChanged.AddUniqueDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);
	InQuestComponent->OnQuestCompleted.AddUniqueDynamic(this, &UCppQuestTrackerWidget::HandleQuestEvent);

	RefreshQuests();
}

void UCppQuestTrackerWidget::HandleQuestEvent(const FCppQuestRuntime& QuestData)
{
	RefreshQuests();
}

void UCppQuestTrackerWidget::RefreshQuests()
{
	if (!QuestList)
	{
		return;
	}

	QuestList->ClearChildren();

	const UCppQuestComponent* Comp = QuestComponent.Get();
	if (!Comp)
	{
		return;
	}

	for (const FCppQuestRuntime& Quest : Comp->ActiveQuests)
	{
		FString Content;

		if (Quest.QuestDefinition)
		{
			Content += Quest.QuestDefinition->QuestName.ToString() + TEXT("\n");
			Content += Quest.QuestDefinition->Description.ToString() + TEXT("\n");
		}
		else
		{
			Content += Quest.QuestID.ToString() + TEXT("\n");
		}

		for (const FCppQuestObjective& Objective : Quest.Objectives)
		{
			Content += FString::Printf(TEXT("  - %s: %d/%d\n"),
				*Objective.TargetID.ToString(), Objective.CurrentAmount, Objective.RequiredAmount);
		}

		Content += Quest.bIsCompleted ? TEXT("Estado: Completada") : TEXT("Estado: En progreso");

		UTextBlock* Entry = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		Entry->SetText(FText::FromString(Content));

		if (UVerticalBoxSlot* BoxSlot = QuestList->AddChildToVerticalBox(Entry))
		{
			BoxSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 12.f));
		}
	}
}