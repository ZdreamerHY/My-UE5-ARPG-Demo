// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DemoBaseCharacter.h"
#include "DemoHeroCharacter.generated.h"

class UHeroUIComponent;
struct FGameplayTag;
class UHeroCombatComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoHeroCharacter : public ADemoBaseCharacter
{
	GENERATED_BODY()

protected:

	virtual void PossessedBy(AController* NewController) override;
	
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay() override;
	
	ADemoHeroCharacter();

	//实现父类方法，提供战斗组件
	virtual  UPawnCombatComponentBase* GetPawnCombatComponent() const override;

	UFUNCTION(BlueprintPure)
	virtual UMotionWarpingComponent* GetMotionWarpingComponent();
	
	//实现父类方法，提供UI组件
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	//继承UI接口
	virtual UHeroUIComponent* GetHeroUIComponent() const override;

#pragma region Components

	UPROPERTY(EditAnywhere,Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere,Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Combat")
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "UI")
	UHeroUIComponent* HeroUIComponent;
#pragma endregion

#pragma region Inputs
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "CharacterData")
	UDataAsset_InputConfig* InputConfig;

	void InputMove(const FInputActionValue& InputActionValue);
	void InputLook(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);
	
#pragma endregion


public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
