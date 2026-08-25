// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTarget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UBTService_OrientToTarget : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_OrientToTarget();

	//继承UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;	
	virtual FString GetStaticDescription() const override;				//设置说明

	//继承UBTService
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	//设置变量，目标的黑板键
	UPROPERTY(EditAnywhere,Category="Target")
	FBlackboardKeySelector TargetActorKey;

	//设置旋转速率
	UPROPERTY(EditAnywhere,Category="Target")
	float RotateInterpSpeed;
};
