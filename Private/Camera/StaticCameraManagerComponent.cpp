// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/StaticCameraManagerComponent.h"

// Sets default values for this component's properties
UStaticCameraManagerComponent::UStaticCameraManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UStaticCameraManagerComponent::OpenCameraUI(TSubclassOf<UCommonActivatableWidget> Widget)
{
	OnOpenCameraUI.Broadcast(Widget);
}

void UStaticCameraManagerComponent::OpenSingleCameraUI(TSubclassOf<UCommonActivatableWidget> Widget)
{
	OnOpenSingleCameraUI.Broadcast(Widget);
}

// Called when the game starts
void UStaticCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStaticCameraManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

