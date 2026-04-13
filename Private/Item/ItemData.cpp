// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemData.h"

FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("ItemData", GetFName());
}
