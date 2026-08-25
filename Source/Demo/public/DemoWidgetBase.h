// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoWidgetBase.generated.h"


class UEnemyUIComponent;
class UHeroUIComponent;
class UPawnUIComponent;
/**
 * 
 */
UCLASS()
class DEMO_API UDemoWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	//重写基类方法，内部调用自定义方法
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent ,meta=(DisplayName="On Owning HeroUIComponent Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* HeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent ,meta=(DisplayName="On Owning EnemyUIComponent Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent);

	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* InOwningEnemyActor);
};
