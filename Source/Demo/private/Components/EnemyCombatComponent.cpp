// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyCombatComponent.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DemoFunctionLibrary.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	const bool IsTargetBlocking = UDemoFunctionLibrary::DoesActorHaveTag(HitActor , DemoGameplayTags::Player_Status_Blocking);
	const bool IsTargetInvincible = UDemoFunctionLibrary::DoesActorHaveTag(HitActor , DemoGameplayTags::Player_Status_Invincible);
	const bool IsBlockValid=UDemoFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);
	
	FGameplayEventData Payload;
	Payload.Instigator = GetOwningPawn();
	Payload.Target = HitActor;
	//攻击可被阻挡且防御者正在阻挡时
	if (IsBlockValid&&IsTargetBlocking)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,DemoGameplayTags::Player_Event_SuccessfulBlock,Payload);
	}
	else if (!IsTargetInvincible)
	{

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),DemoGameplayTags::Shared_Event_MeleeHit,Payload);
	}
	

}

float UEnemyCombatComponent::GetWeaponBaseDamage()
{
	return  0;
}
