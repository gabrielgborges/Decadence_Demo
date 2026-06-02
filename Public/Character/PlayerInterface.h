// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideEvent);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DECADENCE_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsHidden() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetLife() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UseHideSpot(bool Enter);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TakeHit(int Damage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Die();
};
