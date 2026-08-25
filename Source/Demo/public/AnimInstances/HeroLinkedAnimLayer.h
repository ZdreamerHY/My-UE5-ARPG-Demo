// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/DemoBaseAnimInstance.h"
#include "HeroLinkedAnimLayer.generated.h"

class UHeroAnimInstance;
/**
 * 
 */
UCLASS()
class DEMO_API UHeroLinkedAnimLayer : public UDemoBaseAnimInstance
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure,meta=(BlueprintThreadSafe))
	UHeroAnimInstance* GetHeroAnimInstance() const;
};
