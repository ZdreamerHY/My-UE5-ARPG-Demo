// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"

#include "PawnCombatComponentBase.generated.h"

class AWeaponBase;

UENUM(BlueprintType)
enum EDamageType
{
	CurrentWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class DEMO_API UPawnCombatComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:

	//注册生成的武器
	UFUNCTION(BlueprintCallable,Category="Combat")
	void RegisterSpawnedWeapon(FGameplayTag GameplayTag,AWeaponBase* Weapon,bool IsEquipped);

	//通过Tag找到对应武器
	UFUNCTION(BlueprintPure,Category="Combat")
	AWeaponBase* GetWeaponByTag(FGameplayTag GameplayTag) const ;

	//当前持有的武器Tag
	UPROPERTY(BlueprintReadWrite,Category="Combat")
	FGameplayTag CurrentWeaponTag;

	//获取角色当前持有的武器
	UFUNCTION(BlueprintPure,Category="Combat")
	AWeaponBase* GetCurrentWeapon();

	//调整武器的碰撞设置
	UFUNCTION(BlueprintCallable,Category="Combat")
	void ToggleWeaponCollision(bool ShouldEnable,EDamageType DamageType=EDamageType::CurrentWeapon);

	//碰撞之后的处理逻辑
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnPulledFromActor(AActor* InInteractedActor);

protected:
	//维护一个单次攻击命中目标防止多次结算伤害
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag,AWeaponBase*> CharacterCarriedWeaponsMap;
};
