#pragma once

#include "CoreMinimal.h"
#include "ItemDataInstance.generated.h"

class UItemData;
UCLASS(DefaultToInstanced, EditInlineNew)
class DECADENCE_API UItemDataInstance : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UItemData> Data{};

public:
	void Initialize(TObjectPtr<UItemData> dataAsset);
	
	TObjectPtr<UItemData> GetInitialData () { return Data; }
};
