// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "GameplayAbilitySpec.h"
#include "public/AbilitySystem/Abilities/DemoGameplayAbility.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive, int32 ApplyLevel)
{
	check(AscToGive);
	GrantAbilities(ActivateOnGivenAbilities,AscToGive,ApplyLevel);
	GrantAbilities(ReactiveAbilities,AscToGive,ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect> StartUpGE:StartUpGameplayEffects)
		{
			if (!StartUpGE)
			{
				continue;
			}

			UGameplayEffect* EffectCDO= StartUpGE->GetDefaultObject<UGameplayEffect>();
			AscToGive->ApplyGameplayEffectToSelf(EffectCDO,ApplyLevel,AscToGive->MakeEffectContext());
		}
	}

}


void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UDemoGameplayAbility>>& AbilitiesToGive, UDemoAbilitySystemComponent* AscToGive, int32 ApplyLevel)
{
	if (AbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UDemoGameplayAbility>& AbilityToGive: AbilitiesToGive)
	{
		if (!AbilityToGive)
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilityToGive);
		AbilitySpec.SourceObject=AscToGive->GetAvatarActor();
		AbilitySpec.Level=ApplyLevel;

		AscToGive->GiveAbility(AbilitySpec);
	}
}
