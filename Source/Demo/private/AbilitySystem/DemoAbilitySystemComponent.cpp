// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "DemoTypes/DemoStructTypes.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/DemoGameplayAbility.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystem/DemoGameplayTags.h"


UDemoAbilitySystemComponent::UDemoAbilitySystemComponent()
{
	
}

void UDemoAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	
	//处理索敌这样的同一个按键控制开关的能力
	
	if (InputTag.MatchesTag(DemoGameplayTags::InputTag_Toggleable))
	{
		FGameplayAbilitySpec* Spec =BuildAbilitySpecFromTag(InputTag);
		if (Spec&&Spec->Ability)
		{
			if (Spec->IsActive())
			{
				CancelAbilityHandle(Spec->Handle);
			}
			else
			{
				TryActivateAbility(Spec->Handle);
			}
			
		}
		
		return;
	}
	
	//检查能力的激活条件，返回：true认为是连招开始，false认为是动作正在运行或者运行条件不足，Tag被阻塞
	if(TryActivateAbilitiesByTag(FGameplayTagContainer(InputTag)))
	{
		return;
	}


	
	//激活失败，检查当前能力是否已经在运行,自定义查找函数
	FGameplayAbilitySpec* Spec = BuildAbilitySpecFromTag(InputTag);
	if (Spec&&Spec->IsActive())
	{
		FGameplayEventData PayLoad;
		PayLoad.Target=GetAvatarActor();
		PayLoad.Instigator=GetAvatarActor();
		PayLoad.EventTag=DemoGameplayTags::Combo_Input;

		HandleGameplayEvent(DemoGameplayTags::Combo_Input,&PayLoad);
		return;
	}
	//避开Tag，直接激活能力，因为有Bug
	TryActivateAbility(Spec->Handle, true);
}

void UDemoAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	//检查能力的标签是否是需要被持续按住激活的
	if (!InputTag.IsValid() || !InputTag.MatchesTag(DemoGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	for (const FGameplayAbilitySpec& Spec:GetActivatableAbilities())
	{
		if (Spec.IsActive()&&Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			CancelAbilityHandle(Spec.Handle);
		}
	}
}

void UDemoAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FHeroAbilitySet>& AbilitiesToGrant ,int32 ApplyLevel,TArray<FGameplayAbilitySpecHandle>& OutGrantedSpecHandles)
{
	if (AbilitiesToGrant.IsEmpty())
	{
		return;
	}

	for (const FHeroAbilitySet& Ability : AbilitiesToGrant)
	{
		if (!Ability.IsValid()) continue;

		FGameplayAbilitySpec Spec(Ability.AbilityToGrant);
		Spec.SourceObject=GetAvatarActor();
		Spec.Level=ApplyLevel;
		Spec.GetDynamicSpecSourceTags().AddTag(Ability.InputTag);

		OutGrantedSpecHandles.AddUnique(GiveAbility(Spec));
	}
}

void UDemoAbilitySystemComponent::RemoveHeroWeaponAbilities(TArray<FGameplayAbilitySpecHandle> SpecHandlesToRemove)
{
	if (SpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle SpecHandle : SpecHandlesToRemove)
	{
		if (!SpecHandle.IsValid())
		{
			continue;
		}
		ClearAbility(SpecHandle);
	}

	SpecHandlesToRemove.Empty();
}

FGameplayAbilitySpec* UDemoAbilitySystemComponent::BuildAbilitySpecFromTag(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return nullptr;
	}

	//把标签放进容器便于操作
	FGameplayTagContainer TagContainer(InputTag);
	//遍历Spec然后一一比对
	for (FGameplayAbilitySpec& Spec:GetActivatableAbilities())
	{
		bool bMatch=Spec.Ability->GetAssetTags().HasAnyExact(TagContainer)||Spec.GetDynamicSpecSourceTags().HasAnyExact(TagContainer);
		if (bMatch)
		{
			return &Spec;
		}
	}

	return nullptr;
}

bool UDemoAbilitySystemComponent::TryActiveAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	if (AbilityTagToActivate.IsValid())
	{
		TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
		//获取可激活的能力
		GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(),FoundAbilitySpecs);

		if (!FoundAbilitySpecs.IsEmpty())
		{
			//随机激活其中一个能力
			const int32 RandomAbilityIndex = FMath::RandRange(0,FoundAbilitySpecs.Num()-1);
			FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];
			if (SpecToActivate)
			{
				if (!SpecToActivate->IsActive())
				{
					return  TryActivateAbility(SpecToActivate->Handle);
				}
			}
		}
	}

	return false;
}
