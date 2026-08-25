// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "MotionWarpingComponent.h"
#include "Interfaces/UIInterface.h"
#include "DemoBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UDemoAttributeSet;
class UDemoAbilitySystemComponent;

UCLASS()
class DEMO_API ADemoBaseCharacter : public ACharacter,public IAbilitySystemInterface,public IPawnCombatInterface,public IUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoBaseCharacter();

	//实现接口IPawnCombatInterface
	virtual UPawnCombatComponentBase* GetPawnCombatComponent() const override;

	//实现接口IUIInterface,具体实现交给子类
	virtual UPawnUIComponent* GetPawnUIComponent() override;
protected:
	
	// 控制器控制时进行初始化/
	virtual void PossessedBy(AController* NewController) override;						

	//获取ASC
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere,Category="AbilitySystemComponent")
	UDemoAbilitySystemComponent* DemoAbilitySystemComponent;

	UPROPERTY(EditAnywhere,Category="AttributeSet")
	UDemoAttributeSet* DemoAttributeSet;

	UPROPERTY(EditAnywhere,Category="Abilities")
	UMotionWarpingComponent* MotionWarpingComponent; 
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UDemoAbilitySystemComponent* GetDemoAbilitySystemComponent() const { return DemoAbilitySystemComponent; }
	FORCEINLINE UDemoAttributeSet* GetDemoAttributeSet() const { return DemoAttributeSet; }
};
