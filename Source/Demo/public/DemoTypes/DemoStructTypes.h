// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DemoStructTypes.generated.h"

class UInputMappingContext;
class UDemoGameplayAbility;
class UHeroLinkedAnimLayer;


USTRUCT(BlueprintType)
struct FHeroAbilitySet
{
	GENERATED_BODY()

	//输入标签
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;

	//标签对应的要赋予的能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDemoGameplayAbility> AbilityToGrant;

	//检查有效性
	bool IsValid() const;
	
};


USTRUCT(BlueprintType)
struct FHeroWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly )
	TSubclassOf<UHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly ,meta=(TitleProperty="InputTag"))
	TArray<FHeroAbilitySet> DefaultWeaponAbilities;


	//输入映射上下文
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly )
	UInputMappingContext* WeaponInputMappingContext;

	//武器基础伤害
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float WeaponBaseDamage;
	
};


