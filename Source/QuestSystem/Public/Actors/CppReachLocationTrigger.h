#pragma once

#include "CoreMinimal.h"
#include "CppObjectiveActor.h"
#include "CppReachLocationTrigger.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class QUESTSYSTEM_API ACppReachLocationTrigger : public ACppObjectiveActor
{
	GENERATED_BODY()

public:
	ACppReachLocationTrigger();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UBoxComponent> ZoneBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UStaticMeshComponent> Marker;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Objective")
	bool bTriggerOnce = false;

private:
	bool bTriggered = false;
};