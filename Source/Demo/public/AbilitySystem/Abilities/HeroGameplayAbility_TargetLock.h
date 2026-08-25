// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UDemoWidgetBase;
/**
 * 
 */
UCLASS()
class DEMO_API UHeroGameplayAbility_TargetLock : public UHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	//实现UGameplayAbilityInterface方法
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	void TryLockTarget();
	void GetAvailableActorsToLock();

	//取消能力，内部调用CancelAbility
	void CancelTargetLock();

	//能力结束时调用，清除缓存的目标
	void CleanupTargetLock();

	//可锁定的目标很多，选择最近的目标
	AActor* GetNearestTarget(const TArray<AActor*>& ActorsWaitToLock);

	//画UI
	void DrawUIWidget();

	//设置UI位置，这里命名一有点不准确，但是不好改了，实际上是每帧调用刷新逻辑，比如更新UI，更新HeroCharacter的视角
	void SetUILocation();

	//连接到Task的委托引脚，每帧刷新UI的位置
	UFUNCTION(BlueprintCallable, Category = "TargetLock")
	void TickUILocation(float DeltaTime);

	//锁定时更新Hero的移动速度
	void InitLockStatusMovement();

	//取消锁定后还原移动速度
	void ResetMovement();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	float LockDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	FVector LockBoxSize = FVector(5000.0f,5000.0f,1000.0f);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery> > TargetObjectTypes;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	TArray<AActor*> ActorsCanBeLock;
	
	UPROPERTY(BlueprintReadWrite,Category="TargetLock")
	AActor* LockedActor;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	TSubclassOf<UDemoWidgetBase> LockWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	UDemoWidgetBase* LockWidget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	FVector2D SizeBoxWidthAndHeight;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	float LockSpeed=5.0f;

	//存储Hero原本的移动速度
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	float CachedMaxWalkSpeed = 0.0f;

	//更改后的速度
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="TargetLock")
	float TargetMaxWalkSpeed = 400.0f;
};
