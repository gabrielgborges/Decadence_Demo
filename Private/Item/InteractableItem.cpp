// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InteractableItem.h"

#include "Item/ItemData.h"
#include "Components/BoxComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	if (MeshComponent == nullptr)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
		RootComponent = MeshComponent;// 	SetRootComponent(MeshComponent);
		MeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		MeshComponent->SetRenderCustomDepth(false);
	}
	if (BoxCollider == nullptr)
	{
		BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
		BoxCollider->SetupAttachment(GetRootComponent());
		BoxCollider->SetBoxExtent(FVector(24.0f, 24.0f, 24.0f));
	}
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	RequestAppearanceUpdate();
}

void AInteractableItem::OnAppearanceLoaded_Implementation()
{
	
}

void AInteractableItem::RequestAppearanceUpdate()
{
	if (!AppearanceData)
	{
		// DataAsset was cleared — reset the mesh component to a safe blank state
		if (IsValid(MeshComponent))
		{
			MeshComponent->SetStaticMesh(nullptr);
			MeshComponent->SetMaterial(0, nullptr);
		}
		return;
	}

	CancelPendingLoad();

	TArray<FSoftObjectPath> AssetsToLoad =
	{
		AppearanceData->GetMesh().ToSoftObjectPath(),
		AppearanceData->GetMeshMaterial().ToSoftObjectPath()
	};

	// Snapshot the expected DataAsset name — used to detect stale callbacks
	ExpectedAssetName = AppearanceData->GetFName();

	// Capture a weak 'this' — the Actor may be destroyed before the load completes
	TWeakObjectPtr<AInteractableItem> WeakThis(this);
	FName SnapshotName = ExpectedAssetName;

	ActiveStreamHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		AssetsToLoad,
		[WeakThis, SnapshotName]()
		{
			// Callback always fires on the Game Thread — no mutex needed
			AInteractableItem* Self = WeakThis.Get();
			if (!IsValid(Self))                        return; // Actor was destroyed
			if (Self->ExpectedAssetName != SnapshotName) return; // Asset was swapped again

			Self->ApplyLoadedAppearance();
			Self->OnAppearanceLoaded();

			Self->ActiveStreamHandle.Reset();
		},
		FStreamableManager::AsyncLoadHighPriority
	);
}
#if WITH_EDITOR

void AInteractableItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	static const FName AppearanceName = GET_MEMBER_NAME_CHECKED(AInteractableItem, AppearanceData);

	if (PropertyChangedEvent.GetPropertyName() == AppearanceName
		|| PropertyChangedEvent.GetMemberPropertyName() == AppearanceName)
	{
		CancelPendingLoad();
		RequestAppearanceUpdate();
	}
}
#endif

void AInteractableItem::BeginDestroy()
{
	CancelPendingLoad();
	Super::BeginDestroy();
	
}

void AInteractableItem::ApplyLoadedAppearance()
{
	if (!AppearanceData || !IsValid(MeshComponent)) return;

	// .Get() is safe here — we're in the load callback (assets are resident)
	UStaticMesh* LoadedMesh         = AppearanceData->GetMesh().Get();
	UMaterialInterface* LoadedMat   = AppearanceData->GetMeshMaterial().Get();

	MeshComponent->SetStaticMesh(LoadedMesh);

	if (LoadedMat)
	{
		MeshComponent->SetMaterial(0, LoadedMat);
	}
}

void AInteractableItem::CancelPendingLoad()
{
	if (ActiveStreamHandle.IsValid())
	{
		ActiveStreamHandle->CancelHandle();
		ActiveStreamHandle.Reset();
	}
}

void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (AppearanceData)
	{
		const TSoftObjectPtr<UStaticMesh>& SoftMesh = AppearanceData->GetMesh();
		const TSoftObjectPtr<UMaterialInterface>& SoftMat = AppearanceData->GetMeshMaterial();

		if (SoftMesh.IsValid() && SoftMat.IsValid())
		{
			ApplyLoadedAppearance();
		}
	}
}

void AInteractableItem::ClearComponents()
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Component : Components)
	{
		// Never destroy components created via CreateDefaultSubobject
		// (i.e. your MeshComponent root) — only dynamic ones
		if (Component && !Component->IsCreatedByConstructionScript())
		{
			Component->DestroyComponent();
		}
	}
}

void AInteractableItem::AllowInteraction_Implementation()
{
	MeshComponent->SetRenderCustomDepth(true);
	MeshComponent->SetCustomDepthStencilValue(250);

	UE_LOG(LogTemp, Log, TEXT("%s allowed interaction."), *GetName());

}

void AInteractableItem::DenyInteraction_Implementation()
{
	MeshComponent->SetRenderCustomDepth(false);
	MeshComponent->SetCustomDepthStencilValue(0);

	UE_LOG(LogTemp, Log, TEXT("%s denied interaction."), *GetName());
}

void AInteractableItem::Interact_Implementation(AActor* InteractionInstigator)
{
	UE_LOG(LogTemp, Log, TEXT("%s did interact with %s."), *InteractionInstigator->GetName(), *GetName());
}