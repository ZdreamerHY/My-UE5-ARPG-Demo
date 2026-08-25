// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbilityExecute.h"


#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Characters/DemoHeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UHeroGameplayAbilityExecute::GetExecutableTargets()
{
	if (!GetHeroCharacterFromActorInfo())
	{
		return;
	}

	TArray<FHitResult> HitResults;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * ExeDistance,
		ExeBoxSize/2,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		ExecuteTargetObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::Persistent,
		HitResults,
		true);

	for (const FHitResult& HitResult : HitResults)
	{
		AActor* CachedActor = Cast<AActor>(HitResult.GetActor());
		if (!CachedActor)
		{
			continue;
		}
		UDemoAbilitySystemComponent* CachedAbilitySystem =  CachedActor->FindComponentByClass<UDemoAbilitySystemComponent>();
		if (HitResult.GetActor()!=GetHeroCharacterFromActorInfo() && CachedAbilitySystem && CachedAbilitySystem->HasMatchingGameplayTag(DemoGameplayTags::Shared_Status_Stun))
		{
			ExecutableTargets.AddUnique(CachedActor);
		}
	}
}

AActor* UHeroGameplayAbilityExecute::GetNearestTarget() 
{
	if (ExecutableTargets.Num() == 0||!GetHeroCharacterFromActorInfo())
	{
		return nullptr;
	}

	float Distance = 0.0f;
	return  UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(),ExecutableTargets,Distance);
}

void UHeroGameplayAbilityExecute::DealExecute()
{
	if (!GetHeroCharacterFromActorInfo())
	{
		return;
	}
	
	AActor* ExecuteTarget = GetNearestTarget();
	if (ExecuteTarget)
	{
		FGameplayEventData EventData;
		EventData.Target = ExecuteTarget;
		EventData.Instigator = GetHeroCharacterFromActorInfo();
		SendGameplayEvent(DemoGameplayTags::Player_Event_Execute, EventData);
	}
}

void UHeroGameplayAbilityExecute::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	GetExecutableTargets();
	DealExecute();
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbilityExecute::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ExecutableTargets.Empty();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
