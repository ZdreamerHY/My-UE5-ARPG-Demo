// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "HeroControllers.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AHeroControllers : public APlayerController,public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AHeroControllers();

	//实现接口IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
	
private:
	FGenericTeamId HeroTeamId;
};
