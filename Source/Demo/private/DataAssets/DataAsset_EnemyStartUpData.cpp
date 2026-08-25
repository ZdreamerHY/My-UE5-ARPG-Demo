// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(AscToGive, ApplyLevel);

	if (!EnemyStartUpAbilities.IsEmpty())
	{
		for (const TSubclassOf<UEnemyGameplayAbility>& Ability:EnemyStartUpAbilities )
		{
			if (!Ability)
			{
				continue;
			}

			FGameplayAbilitySpec Spec(Ability);
			Spec.SourceObject=AscToGive->GetAvatarActor();
			Spec.Level=ApplyLevel;
			AscToGive->GiveAbility(Spec);
		}
	}
}
