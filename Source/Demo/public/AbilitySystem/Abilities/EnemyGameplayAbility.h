// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DemoGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API UEnemyGameplayAbility : public UDemoGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category="Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure,Category="Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure,Category="Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,float BaseDamage);

private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;
};
