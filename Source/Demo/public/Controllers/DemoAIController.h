// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DemoAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class DEMO_API ADemoAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoAIController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
protected:

	//AI感知组件,感知玩家位置
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAISenseConfig_Sight* EnemySenseConfig;

public:
	//目标更新时执行委托触发的回调函数
	UFUNCTION()
	virtual  void OnEnemyPerceptionUpdated(AActor* Actor,FAIStimulus Stimulus);

	//实现IGenericTeamAgentInterface接口，划分阵营
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& OtherActor) const override;
	
private:
	//设置变量，以便后期在蓝图上随时调整是否开启Detour Crowd Avoidance
	UPROPERTY(EditDefaultsOnly,Category="Detour Crowd Avoidance Config")
	bool bEnableCrowdAvoidance=true;

	//绕行质量，只有当bEnableCrowdAvoidance为真时才能调整
	UPROPERTY(EditDefaultsOnly,Category="Detour Crowd Avoidance Config",meta=(EditCondition="bEnableCrowdAvoidance",UIMin="1",UIMax="4"))
	int32 DetourCrowdAvoidanceQuality=4;

	//绕行的碰撞范围
	UPROPERTY(EditDefaultsOnly,Category="Detour Crowd Avoidance Config",meta=(EditCondition="bEnableCrowdAvoidance"))
	float CollisionRange=600.0f;
};
