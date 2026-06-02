// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class DECADENCE_API IInteractableInterface
{
	GENERATED_BODY()

public:
	virtual TWeakObjectPtr<UItemData> GetData() {return nullptr;};
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void AllowInteraction();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void DenyInteraction();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* InteractionInstigator);
};
