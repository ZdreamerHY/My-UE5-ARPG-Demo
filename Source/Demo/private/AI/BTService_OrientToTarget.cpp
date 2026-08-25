// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_OrientToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTarget::UBTService_OrientToTarget()
{
	//初始化节点名称、事件通知的设置
	NodeName=TEXT("Native Orient to Target Actor");
	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	//初始化旋转速率，调用间隔，随机偏移量，实际上的间隔为Interval+-RandomDeviation
	RotateInterpSpeed=5.0f;
	Interval=0.0f;
	RandomDeviation=0.0f;

	//初始化目标的黑板键，蓝图下拉菜单里只出现AActor及其子类
	TargetActorKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(ThisClass,TargetActorKey),AActor::StaticClass());
	
}

void UBTService_OrientToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset= GetBlackboardAsset())
	{
		//在对应的黑板资产里找目标键
		TargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTService_OrientToTarget::GetStaticDescription() const
{
	const  FString Description =TargetActorKey.SelectedKeyName.ToString();
	return  FString::Printf(TEXT("Orient to %s key %s"),*Description,*GetStaticServiceDescription());
}

void UBTService_OrientToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//先要获取目标和自身
	UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(Object);
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwningPawn&&TargetActor)
	{
		//先获取要调整到的旋转，再调整角度
		const FRotator LookAtRot=UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(),TargetActor->GetActorLocation());
		const FRotator TargetRpt=FMath::RInterpTo(OwningPawn->GetActorRotation(),LookAtRot,DeltaSeconds,RotateInterpSpeed);
		OwningPawn->SetActorRotation(TargetRpt);
	}
}
