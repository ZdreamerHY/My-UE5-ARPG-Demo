// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class DEMO_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive, int32 ApplyLevel = 1) override;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="StartUpData")
	TArray<TSubclassOf<UEnemyGameplayAbility>> EnemyStartUpAbilities;
};
