// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGameplayEffect;
class UDemoAbilitySystemComponent;
class UDemoGameplayAbility;
/**
 * 
 */
UCLASS()
class DEMO_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()


public:
	virtual void GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive,int32 ApplyLevel=1);
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="StartUpData")
	TArray<TSubclassOf<UDemoGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly,Category="StartUpData")
	TArray<TSubclassOf<UDemoGameplayAbility>> ReactiveAbilities; 

	UPROPERTY(EditDefaultsOnly,Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
	
	void GrantAbilities(const TArray<TSubclassOf<UDemoGameplayAbility>>& AbilitiesToGive,UDemoAbilitySystemComponent* AscToGive,int32 ApplyLevel=1);
};
