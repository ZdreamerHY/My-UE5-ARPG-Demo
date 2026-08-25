// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteOnTick.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate ,float,DeltaTime);
/**
 * 
 */
UCLASS()
class DEMO_API UAbilityTask_ExecuteOnTick : public UAbilityTask
{
	GENERATED_BODY()

public:

	UAbilityTask_ExecuteOnTick();
	
	//创建任务
	UFUNCTION(BlueprintCallable, Category = "AbilityTask",meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true"))
	static UAbilityTask_ExecuteOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	//继承GameplayTask的方法
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "AbilityTask")
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
};
