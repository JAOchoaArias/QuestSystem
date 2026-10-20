#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CppEnemyHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class QUESTSYSTEM_API UCppEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Enemy|UI")
	void SetHealthPercent(float Percent);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
};