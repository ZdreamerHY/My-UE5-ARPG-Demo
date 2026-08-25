// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoTypes/DemoStructTypes.h"
#include "AbilitySystem/Abilities/DemoGameplayAbility.h"

bool FHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid()&&AbilityToGrant;
}
