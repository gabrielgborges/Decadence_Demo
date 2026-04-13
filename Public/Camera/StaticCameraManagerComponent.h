// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "StaticCameraManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenCameraUI, TSubclassOf<UCommonActivatableWidget>, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenSingleCameraUI, TSubclassOf<UCommonActivatableWidget>, Widget);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DECADENCE_API UStaticCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaticCameraManagerComponent();

	UPROPERTY(BlueprintAssignable, Category="UIManagerEvents")
	FOnOpenCameraUI OnOpenCameraUI;
	UPROPERTY(BlueprintAssignable, Category="UIManagerEvents")
	FOnOpenSingleCameraUI OnOpenSingleCameraUI;
	
	UFUNCTION(BlueprintCallable)
	void OpenCameraUI(TSubclassOf<UCommonActivatableWidget> Widget);
	
	UFUNCTION(BlueprintCallable)
	void OpenSingleCameraUI(TSubclassOf<UCommonActivatableWidget> Widget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
