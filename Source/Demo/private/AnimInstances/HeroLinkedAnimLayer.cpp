// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/HeroLinkedAnimLayer.h"

#include "AnimInstances/HeroAnimInstance.h"

UHeroAnimInstance* UHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return  Cast<UHeroAnimInstance>(GetOwningComponent()->GetAnimInstance()) ;
}
