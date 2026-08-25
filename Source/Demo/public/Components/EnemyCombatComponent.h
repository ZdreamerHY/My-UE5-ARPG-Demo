// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponentBase.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UEnemyCombatComponent : public UPawnCombatComponentBase
{
	GENERATED_BODY()

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

	UFUNCTION(BlueprintPure)
	float GetWeaponBaseDamage();
};
