// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "DemoWidgetBase.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Components/EnemyCombatComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	//敌人AI控制器的生成时机：放置或动态生成
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation=false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,180.f,0.0f);
	GetCharacterMovement()->MaxWalkSpeed=300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking=1000.0f;

	EnemyCombatComponent=CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent=CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	//初始化血条之后还要绑定在Mesh
	EnemyHealthWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DemoAbilitySystemComponent&&!DemoAbilitySystemComponent->GetAvatarActor())
	{
		DemoAbilitySystemComponent->InitAbilityActorInfo(this,this);
		InitializeStartUpData();
	}

	//初始化EnemyHealthWidgetComponent的时候调用WidgetBase里的函数
	if(UDemoWidgetBase* HealthWidget = Cast<UDemoWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
	
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeStartUpData();
}


//异步方式加载资源
void AEnemyCharacter::InitializeStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
		{
			if(UDataAsset_StartUpDataBase* LoadedData= CharacterStartUpData.Get())
			{
				LoadedData->GiveToAbilitySystemComponent(DemoAbilitySystemComponent);
			}
		})
		);
}

UPawnCombatComponentBase* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent()
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}
