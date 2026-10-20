#pragma once

#include "CoreMinimal.h"
#include "CppObjectiveActor.h"
#include "CppCollectibleItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class QUESTSYSTEM_API ACppCollectibleItem : public ACppObjectiveActor
{
	GENERATED_BODY()

public:
	ACppCollectibleItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<USphereComponent> PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UStaticMeshComponent> Mesh;

private:
	bool bCollected = false;
};