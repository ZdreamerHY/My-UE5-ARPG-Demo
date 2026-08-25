// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility.h"

#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Characters/DemoHeroCharacter.h"
#include "Controllers/HeroControllers.h"


ADemoHeroCharacter* UHeroGameplayAbility::GetHeroCharacterFromActorInfo() 
{
	//弱指针调用前要显式检查有效性
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter= Cast<ADemoHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedHeroCharacter.IsValid()?CachedHeroCharacter.Get():nullptr;
}

AHeroControllers* UHeroGameplayAbility::GetHeroControllerFromActorInfo() 
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController=Cast<AHeroControllers>(CurrentActorInfo->PlayerController);
	}
	return CachedHeroController.IsValid()?CachedHeroController.Get():nullptr;
}

UHeroCombatComponent* UHeroGameplayAbility::GetHeroCombatComponentFromActorInfo() 
{
	return  GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	float BaseDamage, FGameplayTag WeaponAttackTypeTag)
{
	if (!EffectClass)
	{
		return nullptr;
	}

	FGameplayEffectContextHandle EffectContextHandle=GetDemoAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle SpecHandle = GetDemoAbilitySystemComponent()->MakeOutgoingSpec(EffectClass,GetAbilityLevel(),EffectContextHandle);

	SpecHandle.Data->SetSetByCallerMagnitude(DemoGameplayTags::Shared_SetByCaller_BaseDamage, BaseDamage);

	if (WeaponAttackTypeTag.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(WeaponAttackTypeTag, BaseDamage);
	}
	return SpecHandle;
}




