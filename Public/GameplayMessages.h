// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayMessages.generated.h"

/**
 * 
 */
class DECADENCE_API GameplayMessages
{
public:
	GameplayMessages();
	~GameplayMessages();
};

USTRUCT(BlueprintType)
struct DECADENCE_API FPlayerHidedMessage
{
	GENERATED_BODY()

	public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> HiddenActor = nullptr;
}; 