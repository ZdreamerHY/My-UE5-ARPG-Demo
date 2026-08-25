// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_HeroStartUpData.h"
#include "DemoTypes/DemoStructTypes.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/DemoGameplayAbility.h"




void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(AscToGive, ApplyLevel);

	for (const FHeroAbilitySet& Ability:HeroStartUpAbilitySets)
	{
		if (!Ability.IsValid())
		{
			continue;
		}

		//根据技能创建Spec,获取来源对象，等级，动态标签添加
		FGameplayAbilitySpec AbilitySpec(Ability.AbilityToGrant);
		AbilitySpec.SourceObject = AscToGive->GetAvatarActor();
		AbilitySpec.Level=ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(Ability.InputTag);
		AscToGive->GiveAbility(AbilitySpec);
	}
}
