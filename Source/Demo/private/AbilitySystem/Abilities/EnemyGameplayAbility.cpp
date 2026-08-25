// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"

#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "Characters/EnemyCharacter.h"

AEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter=Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid()?CachedEnemyCharacter.Get():nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return  GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float BaseDamage)
{
	if (!EffectClass)
	{
		return nullptr;
	}

	FGameplayEffectContextHandle EffectContextHandle = GetDemoAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle GameplayEffectSpecHandle = GetDemoAbilitySystemComponent()->MakeOutgoingSpec(EffectClass,GetAbilityLevel(),EffectContextHandle);

	GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(DemoGameplayTags::Shared_SetByCaller_BaseDamage, BaseDamage);

	return GameplayEffectSpecHandle;
	
}
