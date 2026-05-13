// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecadentCharacterBase.h"
#include "PlayerInterface.h"
#include "DecadentPlayerCharacter.generated.h"

struct FEnhancedInputActionEventBinding;
class IInteractableInterface;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionAllowed, FDataTableRowHandle, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionDisallowed);

UCLASS()
class DECADENCE_API ADecadentPlayerCharacter : public ADecadentCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
private:
	TWeakObjectPtr<UEnhancedInputComponent> InputComponent;
	TWeakObjectPtr<AActor> CurrentInteractable;
	TObjectPtr<FEnhancedInputActionEventBinding> InteractActionBinding;
	//UPROPERTY(EditDefaultsOnly, Category="Data")
	//TObjectPtr<U> InteractActionBinding;
	int LifePoints = 50; //TODO create a data asset for the player
	void DisposeCurrentInteractable();

	void OnInteractionInputPressed();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnInteractionAllowed OnInteractionAllowed;
	UPROPERTY(BlueprintAssignable)
	FOnInteractionDisallowed OnInteractionDisallowed;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetLife_Implementation() const override { return LifePoints; };
	
	virtual void TakeHit_Implementation(int Damage) override { LifePoints -= Damage; };
	
	virtual void Die_Implementation() override;//TODO restart level
 
	UFUNCTION()
	void SetInputDirection(float XAxis);
};
