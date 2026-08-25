// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "DemoFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/DemoHeroCharacter.h"
#include "DemoWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Controllers/HeroControllers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	TryLockTarget();
	InitLockStatusMovement();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetMovement();
	CleanupTargetLock();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_TargetLock::TryLockTarget()
{
	GetAvailableActorsToLock();

	if (ActorsCanBeLock.IsEmpty())
	{
		CancelTargetLock();
	}

	LockedActor = GetNearestTarget(ActorsCanBeLock);

	if (LockedActor)
	{
		DrawUIWidget();
		SetUILocation();
	}
	else
	{
		CancelTargetLock();
	}
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	ADemoHeroCharacter* CachedHero = GetHeroCharacterFromActorInfo();
	TArray<FHitResult> BoxTraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		CachedHero,
		CachedHero->GetActorLocation(),
		CachedHero->GetActorLocation()+CachedHero->GetActorForwardVector()*LockDistance,
		LockBoxSize/2,
		CachedHero->GetActorForwardVector().ToOrientationRotator(),
		TargetObjectTypes,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape?EDrawDebugTrace::Persistent:EDrawDebugTrace::None,
		BoxTraceHits,
		true
		);

	for (const FHitResult& BoxTraceHit : BoxTraceHits)
	{
		if (BoxTraceHit.GetActor()&&BoxTraceHit.GetActor()!=CachedHero)
		{
			ActorsCanBeLock.AddUnique(BoxTraceHit.GetActor());
		}
	}
}

void UHeroGameplayAbility_TargetLock::CancelTargetLock()
{
	CancelAbility(CurrentSpecHandle,GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
}

void UHeroGameplayAbility_TargetLock::CleanupTargetLock()
{
	ActorsCanBeLock.Empty();
	LockedActor = nullptr;
	if (LockWidget)
	{
		LockWidget->RemoveFromParent();
	}

	LockWidget = nullptr;
	SizeBoxWidthAndHeight=FVector2D::ZeroVector;
	CachedMaxWalkSpeed = 0.0f;
}

AActor* UHeroGameplayAbility_TargetLock::GetNearestTarget(const TArray<AActor*>& ActorsWaitToLock)
{
	float Distance = 0.0f;
	return  UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(),ActorsWaitToLock,Distance);
}

void UHeroGameplayAbility_TargetLock::DrawUIWidget()
{
	if (!LockWidget)
	{
		if (LockWidgetClass)
		{
			LockWidget = CreateWidget<UDemoWidgetBase>(GetHeroControllerFromActorInfo(),LockWidgetClass);
        
			if (LockWidget)
			{
				LockWidget->AddToViewport();
			}
		}
	}
}

void UHeroGameplayAbility_TargetLock::SetUILocation()
{
	if (!LockWidget||!LockedActor)
	{
		CancelTargetLock();
		return;
	}

	FVector2D ScreenLocation;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetHeroControllerFromActorInfo(),LockedActor->GetActorLocation(),ScreenLocation,true);

	//有偏移要消除，x减掉宽的一半，y减掉高的一半
	LockWidget->WidgetTree->ForEachWidget(
		[this](UWidget* FoundWidget)
		{
			if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
			{
				SizeBoxWidthAndHeight.X = FoundSizeBox->GetWidthOverride();
				SizeBoxWidthAndHeight.Y = FoundSizeBox->GetHeightOverride();
			}
		}
		);
	ScreenLocation-=SizeBoxWidthAndHeight/2.f;
	LockWidget->SetPositionInViewport(ScreenLocation,false);
}

void UHeroGameplayAbility_TargetLock::TickUILocation(float DeltaTime)
{
	//判空
	ADemoHeroCharacter* Hero = GetHeroCharacterFromActorInfo();
	APlayerController* PC = GetHeroControllerFromActorInfo();
	if (!Hero || !PC || !LockedActor)
	{
		return;   
	}

	
	if (!LockedActor || UDemoFunctionLibrary::DoesActorHaveTag(LockedActor,DemoGameplayTags::Shared_Status_Dead) || UDemoFunctionLibrary::DoesActorHaveTag(GetHeroCharacterFromActorInfo(),DemoGameplayTags::Shared_Status_Dead))
	{
		CancelTargetLock();
		return;
	}

	SetUILocation();

	//血的教训，角色处于翻滚状态时，不能执行改变朝向的逻辑
	if (UDemoFunctionLibrary::DoesActorHaveTag(GetHeroCharacterFromActorInfo(),DemoGameplayTags::Player_Status_Rolling))
	{
		return;
	}
	FVector TargetLocation = LockedActor->GetActorLocation();
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetHeroCharacterFromActorInfo()->GetActorLocation(),FVector(TargetLocation.X,TargetLocation.Y,TargetLocation.Z-100));
	FRotator CurrentRot = GetHeroControllerFromActorInfo()->GetControlRotation();
	FRotator Rotator = FMath::RInterpTo(CurrentRot,LookAtRot,DeltaTime,LockSpeed);	//平滑设置
	//FRotator Rotator = LookAtRot;
	GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(Rotator.Pitch,Rotator.Yaw,0));
	GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0,Rotator.Yaw,0));
}

void UHeroGameplayAbility_TargetLock::InitLockStatusMovement()
{
	CachedMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetMaxWalkSpeed;
}

void UHeroGameplayAbility_TargetLock::ResetMovement()
{
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedMaxWalkSpeed;
}
