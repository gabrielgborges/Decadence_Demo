// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DecadentCharacterBase.generated.h"

UCLASS(Abstract)
class DECADENCE_API ADecadentCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADecadentCharacterBase();

protected:
	virtual void BeginPlay() override;
};
