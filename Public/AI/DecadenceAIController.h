// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "DecadenceAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;

UCLASS()
class DECADENCE_API ADecadenceAIController : public AAIController
{
	GENERATED_BODY()
	
	ADecadenceAIController();
public:
 	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTree;
};
