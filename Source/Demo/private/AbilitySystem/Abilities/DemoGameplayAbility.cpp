// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DemoGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/PawnCombatComponentBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoGameplayTags.h"

void UDemoGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	//
	if (ActivationPolicy==EDemoAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo&&!Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
	
}

void UDemoGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//
	if (ActivationPolicy==EDemoAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

FActiveGameplayEffectHandle UDemoGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	//先根据Target Actor获取对应ASC
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

	if (!TargetASC || !InSpecHandle.IsValid())
	{
		return FActiveGameplayEffectHandle();
	}
	
	return GetDemoAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data,TargetASC);
	
}

FActiveGameplayEffectHandle UDemoGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* Target,
	const FGameplayEffectSpecHandle& InSpecHandle, ESuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(Target, InSpecHandle);

	OutSuccessType= ActiveGameplayEffectHandle.WasSuccessfullyApplied()? ESuccessType::Success : ESuccessType::Fail;

	return ActiveGameplayEffectHandle;
}

UPawnCombatComponentBase* UDemoGameplayAbility::GetCombatComponentByActorInfo() const
{
	//遍历AvatarActor所拥有的组件，返回第一个战斗组件
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponentBase>();
}

UDemoAbilitySystemComponent* UDemoGameplayAbility::GetDemoAbilitySystemComponent() const
{
	return  Cast<UDemoAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
