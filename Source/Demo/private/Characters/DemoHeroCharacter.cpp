// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DemoHeroCharacter.h"
#include "Components/UI/HeroUIComponent.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DemoInputComponent.h"
#include "Components/HeroCombatComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



void ADemoHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData =CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(DemoAbilitySystemComponent);
		}
	}
}



void ADemoHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

ADemoHeroCharacter::ADemoHeroCharacter()
{
	//胶囊体
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//设置角色不会和视角转动同步旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//弹簧臂的创建，绑定，长度，偏移，旋转，开启碰撞测试
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;

	//相机的创建，绑定，旋转
	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	//角色旋转跟随移动方向
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	//战斗组件
	HeroCombatComponent=CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	//UI组件
	HeroUIComponent=CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UPawnCombatComponentBase* ADemoHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UMotionWarpingComponent* ADemoHeroCharacter::GetMotionWarpingComponent()
{
	return MotionWarpingComponent;
}

UPawnUIComponent* ADemoHeroCharacter::GetPawnUIComponent() 
{
	return HeroUIComponent;
}

UHeroUIComponent* ADemoHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}


void ADemoHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ULocalPlayer* LocalPlayer= GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	Subsystem->AddMappingContext(InputConfig->InputMappingContext,0);
	
	UDemoInputComponent* DemoInputComponent=Cast<UDemoInputComponent>(InputComponent);
	DemoInputComponent->BindNativeInputAction(InputConfig,DemoGameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::InputMove);
	DemoInputComponent->BindNativeInputAction(InputConfig,DemoGameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::InputLook);

	DemoInputComponent->BindAbilityInputAction(InputConfig,this,&ThisClass::Input_AbilityInputPressed,&ThisClass::Input_AbilityInputReleased);
}


void ADemoHeroCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector=InputActionValue.Get<FVector2D>();
	FRotator MovementRotation(0,Controller->GetControlRotation().Yaw,0);

	FVector ForwardDirection=FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection,MovementVector.Y);
	AddMovementInput(RightDirection,MovementVector.X);
}


void ADemoHeroCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxis=InputActionValue.Get<FVector2D>();
	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(-LookAxis.Y);
}

void ADemoHeroCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	DemoAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void ADemoHeroCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	DemoAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}
