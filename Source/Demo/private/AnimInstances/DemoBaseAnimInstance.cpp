// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/DemoBaseAnimInstance.h"
#include "DemoFunctionLibrary.h"
bool UDemoBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if(APawn* OwningPawn = TryGetPawnOwner())
	{
		return UDemoFunctionLibrary::DoesActorHaveTag(OwningPawn,TagToCheck);
	}
	return false;
}
