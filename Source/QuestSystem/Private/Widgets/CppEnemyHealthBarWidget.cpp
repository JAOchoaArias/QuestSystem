#include "Public/Widgets/CppEnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UCppEnemyHealthBarWidget::SetHealthPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
	}
}