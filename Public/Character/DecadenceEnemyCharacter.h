// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecadentCharacterBase.h"
#include "EnemyDataAsset.h"
#include "EnemyInterface.h"
#include "DecadenceEnemyCharacter.generated.h"

class UEnemyDataAsset;
class UBehaviorTree;
class UBlackboardData;

UCLASS()
class DECADENCE_API ADecadenceEnemyCharacter : public ADecadentCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADecadenceEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBlackboardData> BlackboardData;
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TObjectPtr<UEnemyDataAsset> AttributesData;
	UPROPERTY(EditAnywhere, Category="Gameplay")
	FName HitCollisionSocket;
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TObjectPtr<UCurveFloat> MyBlendCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay")
	float CurrentPetrification = 0;
	UPROPERTY(EditAnywhere, meta=(ClampMin = 0,ClampMax = 1), Category = "Gameplay")
	float PetrifyChanceOnMovement = 0.5;
	
	virtual bool TryToPetrify_Implementation() override;

	virtual bool PetrifyInOrOut_Implementation(bool In) override;
	
	virtual FVector GetHitCollisionSocketLocation_Implementation() override;

	virtual const UEnemyDataAsset* GetData_Implementation() override {return AttributesData;}
};
