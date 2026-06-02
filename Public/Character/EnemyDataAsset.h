// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DECADENCE_API UEnemyDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UMaterialInterface> MeshMaterial;
	UPROPERTY(EditDefaultsOnly)
	int Damage;
	UPROPERTY(EditDefaultsOnly)
	float AttackRange;
	UPROPERTY(EditDefaultsOnly)
	float Speed;
	UPROPERTY(EditDefaultsOnly)
	float Acceleration;
	UPROPERTY(EditDefaultsOnly)
	float StunTime;
	UPROPERTY(EditDefaultsOnly)
	float PetrificationSpeed;
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0, ClampMax = 100))
	float SightCapability;
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0, ClampMax = 360))
	float AngleSightCapability;
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0, ClampMax = 100))
	float HearingCapability;
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0, ClampMax = 1))
	bool TouchCapability;

public:
	
	TArray<FSoftObjectPath> GetAssetPaths() const
	{
		return { Mesh.ToSoftObjectPath(), MeshMaterial.ToSoftObjectPath() };
	}

	UFUNCTION()
	TSoftObjectPtr<UStaticMesh> GetMesh() { return Mesh; }
	UFUNCTION()
	TSoftObjectPtr<UMaterialInterface> GetMeshMaterial() { return MeshMaterial; }
	
	UFUNCTION(BlueprintCallable)
	int GetDamage() { return Damage; }
	UFUNCTION(BlueprintCallable)
	float GetAttackRange() { return AttackRange; }
	UFUNCTION(BlueprintCallable)
	int GetSpeed() { return Speed; }
	UFUNCTION(BlueprintCallable)
	int GetAcceleration() { return Acceleration; }
	UFUNCTION(BlueprintCallable)
	float GetStunTime() { return StunTime; }
	UFUNCTION(BlueprintCallable)
	float GetPetrificationSpeed() { return StunTime; }
	UFUNCTION(BlueprintCallable)
	float GetSightCapability() { return SightCapability; }
	UFUNCTION(BlueprintCallable)
	float GetAngleSightCapability() { return AngleSightCapability; }
	UFUNCTION(BlueprintCallable)
	float GetHearingCapability() { return HearingCapability; }
	UFUNCTION(BlueprintCallable)
	bool GetTouchCapability() { return TouchCapability; }

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
