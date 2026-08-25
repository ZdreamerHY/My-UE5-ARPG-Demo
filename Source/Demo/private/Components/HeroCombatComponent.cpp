// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/HeroCombatComponent.h"
#include "Items/WeaponHero.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/DemoGameplayTags.h"

AWeaponHero* UHeroCombatComponent::GetHeroWeaponByTag(FGameplayTag InWeaponTag) const
{
	//调用父类的方法
	return  Cast<AWeaponHero>( GetWeaponByTag(InWeaponTag));
}

float UHeroCombatComponent::GetCurrentWeaponBaseDamage() 
{
	return  Cast<AWeaponHero>( GetCurrentWeapon())->HeroWeaponData.WeaponBaseDamage;
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator=GetOwningPawn();
	Data.Target=HitActor;
	
	UE_LOG(LogTemp,Warning,TEXT("Hit"));
	//检测到碰撞以后，发送事件给GA蓝图
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		DemoGameplayTags::Shared_Event_MeleeHit,
		Data
		);
}

void UHeroCombatComponent::OnPulledFromActor(AActor* InInteractedActor)
{
	
}


