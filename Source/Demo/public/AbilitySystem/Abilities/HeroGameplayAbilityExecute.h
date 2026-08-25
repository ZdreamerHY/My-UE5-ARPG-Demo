// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroGameplayAbility.h"
#include "HeroGameplayAbilityExecute.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UHeroGameplayAbilityExecute : public UHeroGameplayAbility
{
	GENERATED_BODY()

public:
	//Box检测一定范围内的目标，并判断是否可以处决，如果可以的话加入可处决队列
	void GetExecutableTargets();

	//从处决队列里面找到离得最近的目标
	UFUNCTION(BlueprintPure,Category="Ability")
	AActor* GetNearestTarget() ;
	
	//执行处决逻辑
	void DealExecute();

	virtual  void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	//可被处决目标队列
	TArray<AActor*> ExecutableTargets;

	//处决范围
	UPROPERTY(BlueprintReadWrite)
	float ExeDistance = 400.0f;
	UPROPERTY(BlueprintReadWrite)
	FVector ExeBoxSize = {400.0f,400.0f,400.0f};

	//检测类型
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery> > ExecuteTargetObjectTypes;
};
