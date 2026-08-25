// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoWidgetBase.h"

#include "Components/UI/EnemyUIComponent.h"
#include "Interfaces/UIInterface.h"

void UDemoWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//获取UI接口
	if(IUIInterface* UIInterface = Cast<IUIInterface>(GetOwningPlayerPawn()))
	{
		//获取UI组件
		if(UHeroUIComponent* HeroUIComponent = UIInterface->GetHeroUIComponent())
		{
			//调用自定义方法
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UDemoWidgetBase::InitEnemyCreatedWidget(AActor* InOwningEnemyActor)
{
	if(IUIInterface* UIInterface = Cast<IUIInterface>(InOwningEnemyActor))
	{
		if (UEnemyUIComponent* EnemyUIComponent=UIInterface->GetEnemyUIComponent())
		{
			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}
