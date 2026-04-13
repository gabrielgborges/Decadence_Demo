// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UBoxComponent;
struct FStreamableHandle;

UCLASS()
class DECADENCE_API AInteractableItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (ExposeOnSpawn = true))
	TObjectPtr<UItemData> AppearanceData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> BoxCollider;
	// Called once async load completes — safe to call from Game Thread only
	UFUNCTION(BlueprintNativeEvent, Category = "Appearance")
	void OnAppearanceLoaded();
	virtual void OnAppearanceLoaded_Implementation();

	void RequestAppearanceUpdate();
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void BeginDestroy() override;
	
private:
	//TSharedPtr<FStreamableHandle> StreamableHandle;
	TSharedPtr<FStreamableHandle> ActiveStreamHandle;

	// Guards against applying stale loads after the asset ref was swapped
	FName ExpectedAssetName;

	void ApplyLoadedAppearance();
	void CancelPendingLoad();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	void ClearComponents();;

	virtual TWeakObjectPtr<UItemData> GetData() override
	{
		if (AppearanceData && !AppearanceData->CommonInputRowHandle.IsNull())
		{
			return TWeakObjectPtr<UItemData>(AppearanceData);
		}
		return nullptr;
	} 
	
	virtual void AllowInteraction_Implementation() override;

	virtual void DenyInteraction_Implementation() override;

	virtual void Interact_Implementation() override;

	
};
