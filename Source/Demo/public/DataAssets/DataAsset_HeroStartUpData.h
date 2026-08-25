// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 
 */


struct FHeroAbilitySet;

UCLASS()
class DEMO_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	//重写基类方法，把能力传给ASC
	virtual void GiveToAbilitySystemComponent(UDemoAbilitySystemComponent* AscToGive,int32 ApplyLevel=1) override;

private:
	UPROPERTY(EditDefaultsOnly,Category="StartUpData")
	TArray<FHeroAbilitySet> HeroStartUpAbilitySets;
};
