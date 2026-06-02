#include "ItemDataInstance.h"
#include "Item/ItemData.h"

void UItemDataInstance::Initialize(TObjectPtr<UItemData> dataAsset)
{
	Data = dataAsset;
}

