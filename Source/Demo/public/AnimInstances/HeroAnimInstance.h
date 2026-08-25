// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "HeroAnimInstance.generated.h"

class ADemoHeroCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API UHeroAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Reference")
	ADemoHeroCharacter* OwningHeroCharacter;
};
