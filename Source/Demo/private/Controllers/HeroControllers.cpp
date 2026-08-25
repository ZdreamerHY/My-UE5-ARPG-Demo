// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/HeroControllers.h"

AHeroControllers::AHeroControllers()
{
	HeroTeamId = FGenericTeamId(0);
	SetGenericTeamId(HeroTeamId);
}

FGenericTeamId AHeroControllers::GetGenericTeamId() const
{
	return HeroTeamId;
}
