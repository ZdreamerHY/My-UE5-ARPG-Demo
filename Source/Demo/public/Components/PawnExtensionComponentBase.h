// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	template <class T>
	T* GetOwningPawn() const
	{
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		return GetOwningPawn<APawn>()->GetController<T>();
	}
	
};
