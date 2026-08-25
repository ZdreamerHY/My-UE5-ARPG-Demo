// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "DemoTypes/DemoStructTypes.h"
#include "Items/WeaponBase.h"
#include "WeaponHero.generated.h"



/**
 * 
 */
UCLASS()
class DEMO_API AWeaponHero : public AWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WeaponData")
	FHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const ;
	
private:
	//待处理的能力队列，为其设置Getter和Setter
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
