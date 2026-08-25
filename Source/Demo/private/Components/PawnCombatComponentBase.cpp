// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCombatComponentBase.h"

#include "Components/BoxComponent.h"
#include "Items/WeaponBase.h"

void UPawnCombatComponentBase::RegisterSpawnedWeapon(FGameplayTag GameplayTag, AWeaponBase* Weapon, bool IsEquipped)
{
	//表里没有对应Tag并且传入不为空才进行注册
	if (!CharacterCarriedWeaponsMap.Contains(GameplayTag)&&Weapon)
	{
		CharacterCarriedWeaponsMap.Emplace(GameplayTag,Weapon);
		Weapon->OnWeaponHitTarget.BindUObject(this,&ThisClass::OnHitTargetActor);
		Weapon->OnWeaponPulledFromTarget.BindUObject(this,&UPawnCombatComponentBase::OnPulledFromActor);
	}
	else
	{
		return;
	}

	//如果武器生成完就需要持有，就把当前武器Tag设为传入Tag
	if (IsEquipped)
	{		
		CurrentWeaponTag=GameplayTag;
	}
}


AWeaponBase* UPawnCombatComponentBase::GetWeaponByTag(FGameplayTag GameplayTag) const
{
	//根据Tag返回武器
	if (CharacterCarriedWeaponsMap.Contains(GameplayTag))
	{
		//返回的是二级指针要解引
		if (AWeaponBase* const* Weapon = CharacterCarriedWeaponsMap.Find(GameplayTag))
		{
			return *Weapon;
		}
	}
	return nullptr;
}

AWeaponBase* UPawnCombatComponentBase::GetCurrentWeapon()
{
	if (CurrentWeaponTag.IsValid())
	{
		return GetWeaponByTag(CurrentWeaponTag);
	}
	else
	{
		return nullptr;
	}
}

void UPawnCombatComponentBase::ToggleWeaponCollision(bool bShouldEnable, EDamageType DamageType)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello Screen!"));
	if (DamageType==EDamageType::CurrentWeapon)
	{
		AWeaponBase* WeaponToToggle=GetCurrentWeapon();
		check(WeaponToToggle);
		
		if (bShouldEnable==true)
		{
			OverlappedActors.Empty();
			WeaponToToggle->GetCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//在禁用碰撞之后销毁掉碰撞队列
			//OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponentBase::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponentBase::OnPulledFromActor(AActor* InInteractedActor)
{
	
}
