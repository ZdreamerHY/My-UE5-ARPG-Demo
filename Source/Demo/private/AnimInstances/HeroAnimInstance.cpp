// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/HeroAnimInstance.h"

#include "Characters/DemoHeroCharacter.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningHeroCharacter=Cast<ADemoHeroCharacter>(TryGetPawnOwner());
}

void UHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
