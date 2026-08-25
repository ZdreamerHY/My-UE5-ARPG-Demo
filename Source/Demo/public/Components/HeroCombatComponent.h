// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponentBase.h"
#include "HeroCombatComponent.generated.h"


class UPawnUIComponent;
class UHeroUIComponent;
class AWeaponHero;
/**
 * 
 */
UCLASS()
class DEMO_API UHeroCombatComponent : public UPawnCombatComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Combat")
	AWeaponHero* GetHeroWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintPure,Category = "Combat")
	float GetCurrentWeaponBaseDamage() ;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnPulledFromActor(AActor* InInteractedActor) override;


};
