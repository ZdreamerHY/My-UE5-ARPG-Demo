// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DemoAbilitySystemComponent.generated.h"


struct FHeroAbilitySet;
class UDemoAttributeSet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UDemoAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDemoAbilitySystemComponent();

	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);


	UFUNCTION(BlueprintCallable,Category="Ability",meta=(AppltLevel="1"))
	void GrantHeroWeaponAbilities(const TArray<FHeroAbilitySet>& AbilitiesToGrant ,int32 ApplyLevel,TArray<FGameplayAbilitySpecHandle>& OutGrantedSpecHandles);

	UFUNCTION(BlueprintCallable,Category="Ability")
	void RemoveHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle> SpecHandlesToRemove);

	//辅助函数，通过Tag查找对应能力是否被激活
	FGameplayAbilitySpec* BuildAbilitySpecFromTag(FGameplayTag InputTag);

	//为敌人执行攻击做铺垫，通过Tag激活能力
	UFUNCTION(BlueprintCallable)
	bool TryActiveAbilityByTag(FGameplayTag AbilityTagToActivate);
};
