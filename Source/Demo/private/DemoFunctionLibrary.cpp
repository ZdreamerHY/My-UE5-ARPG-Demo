// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoFunctionLibrary.h"
#include "AbilitySystemGlobals.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Characters/DemoBaseCharacter.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "Chaos/Utilities.h"
#include "Interfaces/PawnCombatInterface.h"

UPawnCombatComponentBase* UDemoFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	if (!InActor)
	{
		return nullptr;
	}

	IPawnCombatInterface* CombatInterface = Cast<IPawnCombatInterface>(InActor);
	if (!CombatInterface)
	{
		return nullptr;   
	}

	return CombatInterface->GetPawnCombatComponent();
}

UPawnCombatComponentBase* UDemoFunctionLibrary::BP_GetUPawnCombatComponentFromActor(AActor* InActor,
	EDemoValidType& OutValidType)
{
	UPawnCombatComponentBase* PawnCombatComponent= NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType= PawnCombatComponent? EDemoValidType::Valid:EDemoValidType::InValid;
	return PawnCombatComponent;
}

void UDemoFunctionLibrary::AddTagToActorIfNone(AActor* TargetActor, FGameplayTag TagToAdd)
{
	UAbilitySystemComponent* ASC=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

	if (ASC)
	{
		if (ASC->HasMatchingGameplayTag(TagToAdd))
		{
			return;
		}
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UDemoFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* TargetActor, FGameplayTag TagToRemove)
{
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (ASC)
	{
		if (!ASC->HasMatchingGameplayTag(TagToRemove))
		{
			return;
		}
		else
		{
			ASC->RemoveLooseGameplayTag(TagToRemove);
		}
	}
}

bool UDemoFunctionLibrary::DoesActorHaveTag(AActor*Actor , FGameplayTag TagToCheck)
{
	UAbilitySystemComponent* ASC=UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
	if (ASC)
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}
		return false;
}

bool UDemoFunctionLibrary::IsTargetPawnHostile(APawn* SelfPawn, APawn* TargetPawn) 
{
	if (SelfPawn && TargetPawn)
	{
		IGenericTeamAgentInterface* SelfAgent = Cast<IGenericTeamAgentInterface>(SelfPawn->GetController());
		IGenericTeamAgentInterface* TargetAgent =  Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

		if (SelfAgent && TargetAgent)
		{
			return SelfAgent->GetGenericTeamId()!=TargetAgent->GetGenericTeamId();
		}
	}

	return false;
}

bool UDemoFunctionLibrary::IsValidBlock(AActor* AttackActor, AActor* DefenderActor)
{
	if (AttackActor&&DefenderActor)
	{
		const float DotProductResult = FVector::DotProduct(AttackActor->GetActorForwardVector(), DefenderActor->GetActorForwardVector()) ;
		return DotProductResult < 0.0f;
	}
	return false;
}
