// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

//多托委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate , float ,NewPercent);

/**
 * 
 */
UCLASS()
class DEMO_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:

	//生命值变化委托
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentStaminaChanged;
};
