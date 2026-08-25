// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Characters/DemoBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter=Cast<ADemoBaseCharacter>( TryGetPawnOwner());
	if (OwningCharacter )
	{
		OwningMovementComponent=OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter||!OwningMovementComponent)
	{
		return;
	}

	GroundSpeed=OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration=OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.0f;

	//计算相对朝向，OwningCharacter->GetVelocity()这个是世界的绝对朝向
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(),OwningCharacter->GetActorRotation());
}
