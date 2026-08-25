// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DemoInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject,typename CallBackFunc>
	void BindNativeInputAction(UDataAsset_InputConfig* InputConfig,FGameplayTag InputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallBackFunc Func)
	{
		checkf(InputConfig,TEXT("InputConfig为空"));

		if (UInputAction* FoundAction =InputConfig->FindInputActionByTag(InputTag))
		{
			BindAction(FoundAction,TriggerEvent,ContextObject,Func);
		}
	}


	template<class UserObject,typename CallBackFunc>
	void BindAbilityInputAction( const UDataAsset_InputConfig* InputConfigs,UserObject* ContextObject,CallBackFunc PressedFunc,CallBackFunc ReleasedFunc)
	{
		for (const FDemoInputActionConfig& InputActionConfig:InputConfigs->AbilityInputActions)
		{
			if (!InputActionConfig.IsValid())
			{
				continue;
			}
			BindAction(InputActionConfig.InputAction,ETriggerEvent::Started,ContextObject,PressedFunc,InputActionConfig.InputTag);
			BindAction(InputActionConfig.InputAction,ETriggerEvent::Completed,ContextObject,ReleasedFunc,InputActionConfig.InputTag);
		}
	}
};
