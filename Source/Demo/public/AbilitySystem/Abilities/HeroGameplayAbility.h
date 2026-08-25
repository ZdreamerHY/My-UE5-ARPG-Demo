// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "AbilitySystem/Abilities/DemoGameplayAbility.h"
#include "HeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AHeroControllers;
class ADemoHeroCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API UHeroGameplayAbility : public UDemoGameplayAbility
{
	GENERATED_BODY()

public:
	//通过表现者信息获取角色
	UFUNCTION(BlueprintPure,Category="Ability")
	ADemoHeroCharacter* GetHeroCharacterFromActorInfo() ;

	//获取控制器
	UFUNCTION(BlueprintPure,Category="Ability")
	AHeroControllers* GetHeroControllerFromActorInfo()  ;

	//获取战斗组件
	UFUNCTION(BlueprintPure,Category="Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo()  ;

	UFUNCTION(BlueprintPure,Category="Ability")
	FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,float BaseDamage,FGameplayTag WeaponAttackTypeTag);

private:
	TWeakObjectPtr<ADemoHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AHeroControllers> CachedHeroController;
	
};
