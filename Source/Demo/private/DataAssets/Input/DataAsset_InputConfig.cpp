// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindInputActionByTag(const FGameplayTag& InputTag)
{
	for (const FDemoInputActionConfig& InputActionConfig:NativeInputActions)
	{
		if (InputActionConfig.InputTag == InputTag&&InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}


