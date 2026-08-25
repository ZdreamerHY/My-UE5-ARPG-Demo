// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DemoGameplayAbility.generated.h"

/**
 * 
 */

class UDemoAbilitySystemComponent;
class UPawnCombatComponentBase;

UENUM(BlueprintType)
enum class EDemoAbilityActivationPolicy :uint8
{
	OnGiven,
	OnTriggered
};

UENUM(BlueprintType)
enum class ESuccessType :uint8
{
	Success,
	Fail
};


UCLASS()
class DEMO_API UDemoGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AbilityActivationPolicy")
	EDemoAbilityActivationPolicy ActivationPolicy=EDemoAbilityActivationPolicy::OnTriggered;


	//通过表现者的信息获取战斗组件
	UFUNCTION(BlueprintCallable,Category="Ability")
	UPawnCombatComponentBase* GetCombatComponentByActorInfo() const;

	//通过表现者的信息获取ASC
	UFUNCTION(BlueprintCallable,Category="Ability")
	UDemoAbilitySystemComponent* GetDemoAbilitySystemComponent() const;
	
public:
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilitySpec& Spec);

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	//应用能力到对应Target
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* Target,const FGameplayEffectSpecHandle& InSpecHandle);

	//蓝图版本
	UFUNCTION(BlueprintCallable,meta=(ExpandEnumAsExecs="OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* Target,const FGameplayEffectSpecHandle& InSpecHandle,ESuccessType& OutSuccessType);
};
