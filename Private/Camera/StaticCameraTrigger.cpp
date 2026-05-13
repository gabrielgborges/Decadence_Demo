// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticCameraTrigger.h"
#include "Character/DecadentPlayerCharacter.h"
#include "Camera/CameraActor.h"
#include "Camera/StaticCameraManagerComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AStaticCameraTrigger::AStaticCameraTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;

	OverlapVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapVolume->SetGenerateOverlapEvents(true);
}

void AStaticCameraTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!Camera) return;

	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter) return;

	UActorComponent* CameraManagerComponent = PlayerCharacter->GetComponentByClass(UStaticCameraManagerComponent::StaticClass());
	if (!CameraManagerComponent) return;
	
	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());
	if (!PC) return;
	
	PC->SetViewTargetWithBlend(
		Camera,
		BlendTime,
		TargetBlendFunction
	);

	TObjectPtr<ADecadentPlayerCharacter> DecadentPlayer = Cast<ADecadentPlayerCharacter>(PlayerCharacter);
	if (DecadentPlayer)
	{
		float SnappedYaw = Camera->GetActorRotation().Yaw;
		if (RoundedRotationInputs)
		{
			SnappedYaw = FMath::RoundToInt(Camera->GetActorRotation().Yaw / 90.0f) * 90.0f;
			SnappedYaw = FRotator::ClampAxis(SnappedYaw);
			if (SnappedYaw > 180.f) SnappedYaw -= 360.f;
		}
		
		FRotator NewControlRot = DecadentPlayer->GetControlRotation();
		NewControlRot.Yaw = SnappedYaw;
		DecadentPlayer->GetController()->SetControlRotation(NewControlRot);
		
		UStaticCameraManagerComponent* CameraManager = Cast<UStaticCameraManagerComponent>(CameraManagerComponent);
		CameraManager->OpenSingleCameraUI(CameraFrame);
	}
}

void AStaticCameraTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ACharacter* PlayerCharacter = Cast<ACharacter, AActor>(OtherActor);
	if (!PlayerCharacter) return;
	
	if (!PlayerCharacter->GetController() || !PlayerCharacter->GetController()->IsA(APlayerController::StaticClass())) return;

	UE_LOG(LogTemp, Warning, TEXT("AStaticCameraTrigger::NotifyActorEndOverlap"));
	// PC->SetViewTargetWithBlend(
	// 	PlayerCharacter,
	// 	BlendOutTime,
	// 	TargetBlendFunction
	// );
}

void AStaticCameraTrigger::BeginPlay()
{
	Super::BeginPlay();
}
