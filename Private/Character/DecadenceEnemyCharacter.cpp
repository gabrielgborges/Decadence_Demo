// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DecadenceEnemyCharacter.h"
#include "AI/DecadenceAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ADecadenceEnemyCharacter::ADecadenceEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADecadenceEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;

	ADecadenceAIController* AiController = Cast<ADecadenceAIController>(NewController);
	if (AiController)
	{
		AiController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AiController->RunBehaviorTree(BehaviorTree);
	}
}

bool ADecadenceEnemyCharacter::TryToPetrify_Implementation()
{
	return IEnemyInterface::TryToPetrify_Implementation();//TODO thread safe to stop behaviour tree
}

FVector ADecadenceEnemyCharacter::GetHitCollisionSocketLocation_Implementation()
{
	return GetComponentByClass<USkeletalMeshComponent>()->GetSocketLocation(HitCollisionSocket);
}