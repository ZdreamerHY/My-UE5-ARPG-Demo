// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DemoBaseCharacter.h"

#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoAttributeSet.h"


// Sets default values
ADemoBaseCharacter::ADemoBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;

	DemoAbilitySystemComponent = CreateDefaultSubobject<UDemoAbilitySystemComponent>(TEXT("DemoAbilitySystemComponent"));
	DemoAttributeSet=CreateDefaultSubobject<UDemoAttributeSet>(TEXT("DemoAttributeSet"));
	MotionWarpingComponent=CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UPawnCombatComponentBase* ADemoBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* ADemoBaseCharacter::GetPawnUIComponent()
{
	return nullptr;
}

void ADemoBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (DemoAbilitySystemComponent)
	{
		DemoAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
}
UAbilitySystemComponent* ADemoBaseCharacter:: GetAbilitySystemComponent() const
{
	return GetDemoAbilitySystemComponent();
}

