// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DecadentPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameplayMessages.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Item/InteractableInterface.h"
#include "Kismet/GameplayStatics.h"

void ADecadentPlayerCharacter::DisposeCurrentInteractable()
{
	if (CurrentInteractable.IsValid())
	{
		IInteractableInterface::Execute_DenyInteraction(CurrentInteractable.Get());
		if (InputComponent.IsValid() && InteractActionBinding)
		{
			InputComponent->RemoveActionBindingForHandle(InteractActionBinding->GetHandle());
		}
		OnInteractionDisallowed.Broadcast();
	}
}

void ADecadentPlayerCharacter::OnInteractionInputPressed()
{
	if (CurrentInteractable.IsValid())
	{
		IInteractableInterface::Execute_Interact(CurrentInteractable.Get(), this);
		DisposeCurrentInteractable();
	}
}

void ADecadentPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADecadentPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADecadentPlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor->Implements<UInteractableInterface>())
	{
		DisposeCurrentInteractable();
		IInteractableInterface::Execute_AllowInteraction(OtherActor);
		IInteractableInterface* InteractableActorInterface = Cast<IInteractableInterface>(OtherActor);
		if (!InteractableActorInterface)
		{
			return;			
		}

		TWeakObjectPtr<UItemData> ItemData = InteractableActorInterface->GetData();
		if (ItemData.IsValid())
		{
			CurrentInteractable = OtherActor;
			OnInteractionAllowed.Broadcast(ItemData.Get()->CommonInputRowHandle);
			if (InputComponent.IsValid())
			{
				UE_LOG(LogTemp, Display, TEXT("InputComponent"));// this, &ADecadentPlayerCharacter::BeginPlay);//
				InteractActionBinding = &InputComponent->BindAction(ItemData.Get()->GetTakeItemInputAction().Get(), ETriggerEvent::Triggered, this, &ADecadentPlayerCharacter::OnInteractionInputPressed);
			}
		}
	}
}

void ADecadentPlayerCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor->Implements<UInteractableInterface>() && CurrentInteractable.IsValid() && CurrentInteractable.Get() == OtherActor)
	{
		DisposeCurrentInteractable();
	}
}

void ADecadentPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComponent = GetComponentByClass<UEnhancedInputComponent>();
	if (inputComponent)
	{
		InputComponent = inputComponent;
	}	
}

void ADecadentPlayerCharacter::UseHideSpot_Implementation(bool Enter)
{
	IsHidden = Enter;

	if (Enter)
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		FGameplayTag HideTag = FGameplayTag::RequestGameplayTag(FName("Gameplay.Player.Hide"));
		if (MessageSubsystem.IsValidLowLevelFast())
		{
			FPlayerHidedMessage Message;
			Message.HiddenActor = this;
			MessageSubsystem.BroadcastMessage<FPlayerHidedMessage>(HideTag, Message);
		}
	}
}

void ADecadentPlayerCharacter::Die_Implementation()
{
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void ADecadentPlayerCharacter::SetInputDirection(float XAxis)
{
	AddControllerYawInput(XAxis);
}
