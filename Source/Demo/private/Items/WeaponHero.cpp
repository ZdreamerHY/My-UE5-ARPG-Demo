// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponHero.h"

void AWeaponHero::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandles)
{
	GrantedAbilitySpecHandles = InGrantedAbilitySpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWeaponHero::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
