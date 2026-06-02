// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DecadenceEnemyCharacter.h"
#include "AI/DecadenceAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	return IEnemyInterface::TryToPetrify_Implementation();
}

bool ADecadenceEnemyCharacter::PetrifyInOrOut_Implementation(bool In)
{
	bool HitPetrifiedChance = FMath::RandRange(0.0,1.0) < PetrifyChanceOnMovement;
	if (HitPetrifiedChance)
	{
		GetComponentByClass<USkeletalMeshComponent>()->GlobalAnimRateScale = 0;
		TObjectPtr<UCharacterMovementComponent> MovementComponent = GetComponentByClass<UCharacterMovementComponent>();
		MovementComponent->MaxWalkSpeed = 0;
		MovementComponent->MaxAcceleration = 0;
		UE_LOG(LogTemp, Warning, TEXT("Petrified!"));
		return true;
	}
	
	float Target = In ? 0.0f : 1.0f;
	CurrentPetrification = FMath::FInterpTo(CurrentPetrification, Target, GetWorld()->GetDeltaSeconds(), AttributesData->GetPetrificationSpeed());
	float PetrificationBlendValue = MyBlendCurve->GetFloatValue(CurrentPetrification);
	GetComponentByClass<USkeletalMeshComponent>()->GlobalAnimRateScale = CurrentPetrification;
	TObjectPtr<UCharacterMovementComponent> MovementComponent = GetComponentByClass<UCharacterMovementComponent>();
	MovementComponent->MaxWalkSpeed = AttributesData->GetSpeed() * PetrificationBlendValue;
	MovementComponent->MaxAcceleration = AttributesData->GetAcceleration() * PetrificationBlendValue;

	UE_LOG(LogTemp, Warning, TEXT("value: %f , blended value: %f"), CurrentPetrification, PetrificationBlendValue);
	return true;
}

FVector ADecadenceEnemyCharacter::GetHitCollisionSocketLocation_Implementation()
{
	return GetComponentByClass<USkeletalMeshComponent>()->GetSocketLocation(HitCollisionSocket);
}
