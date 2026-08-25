// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DemoAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


class IUIInterface;

UCLASS()
class DEMO_API UDemoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UDemoAttributeSet();
	
	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,CurrentHealth)				//自动生成Get，Set，Init

	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,MaxHealth)

	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Stamina")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,CurrentStamina)

	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,MaxStamina)

	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,AttackPower)

	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,DefensePower)

	//修改伤害的占位符
	UPROPERTY(BLueprintReadOnly, VisibleAnywhere, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet,DamageTaken)


	//重写基类函数，将GE实际运算出的值作用给AttributeSet
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

private:
	//缓存UI接口类
	TWeakInterfacePtr<IUIInterface> CachedPawnUIInterface;
};
