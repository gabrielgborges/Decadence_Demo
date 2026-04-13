// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "StaticCameraTrigger.generated.h"

class UCommonActivatableWidget;

UCLASS()
class AStaticCameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticCameraTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* OverlapVolume;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ACameraActor* Camera;
	UPROPERTY(EditAnywhere, Category="Camera UI")
	TSubclassOf<UCommonActivatableWidget> CameraFrame;
	
	UPROPERTY(EditAnywhere, Category="Camera UI")
	bool RoundedRotationInputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.75f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendOutTime = 0.75f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EViewTargetBlendFunction> TargetBlendFunction = VTBlend_Linear;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* actor) override;

	virtual void NotifyActorEndOverlap(AActor* actor) override;
};
