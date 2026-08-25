// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponBase.h"

#include "DemoFunctionLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values

AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//设置静态网格体组件
	WeaponMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	//初始化碰撞箱，绑定在根组件上
	CollisionBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetRelativeLocation(FVector(10.0f, 10.0f, 10.0f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//将回调函数绑定到一个多播委托上，但在绑定之前会先检查，确保同一个函数没有被重复绑定
	//碰撞的检测放到武器类执行，碰撞后一系列的处理交给CombatComponent
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxEndOverlap);
}

void AWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APawn* WeaponOwningPawn= GetInstigator<APawn>();
	
	if (!WeaponOwningPawn)
	{
		return;
	}

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UDemoFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn,HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn= GetInstigator<APawn>();

	if (!WeaponOwningPawn)
	{
		return;
	}

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UDemoFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn,HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}





