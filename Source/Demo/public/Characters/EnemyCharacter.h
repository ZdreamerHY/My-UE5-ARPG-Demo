// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DemoBaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class DEMO_API AEnemyCharacter : public ADemoBaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	//使敌人放置在场景里也可以初始化
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;;

	void InitializeStartUpData();

	//实现父类方法，提供战斗组件
	virtual  UPawnCombatComponentBase* GetPawnCombatComponent() const override;

	//实现父类方法，提供UI组件
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	
	UFUNCTION(BlueprintPure, Category = "Combat")
	UEnemyCombatComponent* GetEnemyCombatComponent() const
	{
		return EnemyCombatComponent;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	//敌人的血条需要挂在到实体上而不是直接画在屏幕上
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

public:
	
};
