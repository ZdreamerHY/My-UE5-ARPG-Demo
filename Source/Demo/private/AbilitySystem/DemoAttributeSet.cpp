// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/AbilitySystem/DemoAttributeSet.h"

#include "DemoFunctionLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "Components/UI/PawnUIComponent.h"
#include "Interfaces/UIInterface.h"
#include "Kismet/KismetSystemLibrary.h"


UDemoAttributeSet::UDemoAttributeSet()
{
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
	InitCurrentHealth(1.0f);
	InitCurrentStamina(1.0f);
	InitMaxHealth(1.0f);
	InitMaxStamina(1.0f);
}

void UDemoAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	//提取UI组件
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IUIInterface>(Data.Target.GetAvatarActor());
	}
	
	UPawnUIComponent* PawnUIComponent=CachedPawnUIInterface->GetPawnUIComponent();
	
	if (Data.EvaluatedData.Attribute==GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth=FMath::Clamp(GetCurrentHealth(),0.0f,GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		//广播
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
		//打印验证一下
		//GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, FString::Printf(TEXT("Ratio: %f"), GetCurrentHealth()/GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute==GetCurrentStaminaAttribute())
	{
		const float NewCurrentStamina=FMath::Clamp(GetCurrentStamina(),0.0f,GetMaxStamina());
		SetCurrentStamina(NewCurrentStamina);
	}

	if (Data.EvaluatedData.Attribute==GetDamageTakenAttribute())
	{
		const float OldHealth=GetCurrentHealth();
		const float DamageDone=GetDamageTaken();

		const float NewHealth=FMath::Clamp(OldHealth-DamageDone,0.0f,GetMaxHealth());
		SetCurrentHealth(NewHealth);
		
		UE_LOG(LogTemp, Warning, TEXT("CurrentHealth : %f"),GetCurrentHealth());
	
	}

	//血量变化广播给UI组件
	PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	PawnUIComponent->OnCurrentStaminaChanged.Broadcast(GetCurrentStamina()/GetMaxStamina());
	
	//血量归零时给角色添加死亡tag
	if (GetCurrentHealth() ==0)
	{
		UDemoFunctionLibrary::AddTagToActorIfNone(Data.Target.GetAvatarActor(),DemoGameplayTags::Shared_Status_Dead);
	}

	//耐力归零进入眩晕状态，给角色添加状态标签然后触发对应GA
	if (GetCurrentStamina()==0)
	{
		UDemoFunctionLibrary::AddTagToActorIfNone(Data.Target.GetAvatarActor(),DemoGameplayTags::Shared_Status_Stun);
	}
	//但如果施加完体力相关的GE，检测体力不为0，就要取消眩晕Tag
	else if (GetCurrentStamina()!=0)
	{
		UDemoFunctionLibrary::RemoveGameplayFromActorIfFound(Data.Target.GetAvatarActor(),DemoGameplayTags::Shared_Status_Stun);
	}
}
