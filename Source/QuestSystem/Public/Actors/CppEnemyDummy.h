#pragma once

#include "CoreMinimal.h"
#include "CppObjectiveActor.h"
#include "CppEnemyDummy.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UCppEnemyHealthBarWidget;

UCLASS()
class QUESTSYSTEM_API ACppEnemyDummy : public ACppObjectiveActor
{
	GENERATED_BODY()

public:
	ACppEnemyDummy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<USphereComponent> HitSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|UI")
	TObjectPtr<UWidgetComponent> HealthBarComponent;

	/** Clase del widget de la barra (se asigna en el editor, por instancia) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|UI")
	TSubclassOf<UCppEnemyHealthBarWidget> HealthBarWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "1"))
	float MaxHealth = 30.f;

private:
	void UpdateHealthBar();

	UPROPERTY()
	TObjectPtr<UCppEnemyHealthBarWidget> HealthBarWidget;

	float CurrentHealth = 0.f;
	bool bIsDead = false;
};