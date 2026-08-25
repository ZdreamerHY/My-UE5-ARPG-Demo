// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/DemoBaseAnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class ADemoBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class DEMO_API UCharacterAnimInstance : public UDemoBaseAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	ADemoBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AnimationData")
	float GroundSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AnimationData")
	bool bHasAcceleration;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AnimationData")
	float LocomotionDirection;
};
