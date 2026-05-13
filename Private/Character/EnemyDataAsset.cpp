// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyDataAsset.h"

FPrimaryAssetId UEnemyDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("EnemyData", GetFName());
}