// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemDataPayload
{
	GENERATED_BODY()
	
};

UCLASS()
class DECADENCE_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UMaterialInterface> MeshMaterial;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UInputAction> TakeItemInputAction;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle CommonInputRowHandle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName InputDisplayName;
	
	TArray<FSoftObjectPath> GetAssetPaths() const
	{
		return { Mesh.ToSoftObjectPath(), MeshMaterial.ToSoftObjectPath(), TakeItemInputAction.ToSoftObjectPath() };
	}

	UFUNCTION()
	TSoftObjectPtr<UStaticMesh> GetMesh() { return Mesh; }
	UFUNCTION()
	TSoftObjectPtr<UMaterialInterface> GetMeshMaterial() { return MeshMaterial; }
	UFUNCTION()
	TSoftObjectPtr<UInputAction> GetTakeItemInputAction() { return TakeItemInputAction; }

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
